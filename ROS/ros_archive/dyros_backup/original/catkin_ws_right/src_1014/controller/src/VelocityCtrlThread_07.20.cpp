#include "../inc/VelocityCtrlThread.h"

VelocityCtrlThread::VelocityCtrlThread(int argc, char** argv, Ui::MainWindow* ui)
		:m_bThreadStop(false)
		, init_argc(argc), init_argv(argv), _ui(ui)
{
	ros::init(init_argc, init_argv, "VelocityCtrlThread");
	ros::NodeHandle n;

	m_currentVel = 0;
	m_targetVel = 0;
	m_bVelTopicUpdated = false;

	m_auto_brake = 18.0;
	m_accel_max = 30.0;
	m_accel_min = 25.0;
	m_brake_max = 18.0;
	m_brake_min = 0.0;

	m_brakingCtrlVal = 5.0*0.278;

	m_limit_vel_low_error = 1.0;
	//m_limit_vel_up_error = 5.0;

	m_accel_pgain = 0.1;
	m_brake_pgain = -0.1;

	//possub = n.subscribe("LocalizationData", 100, &VelocityCtrlThread::LocalizationTopicProcess, this);
        possub = n.subscribe("my_pose2", 10, &VelocityCtrlThread::LocalizationTopicProcess, this);
	//drcsub = n.subscribe("drc_vehicle", 10, &VelocityCtrlThread::DrcTopicProcess, this);
        drcsub = n.subscribe("ControlData", 10, &VelocityCtrlThread::ControlDataTopicProcess, this);

	// publish data
	//msgpub = n.advertise<MotionPlanner::VelocityCtrlData>("VelocityCtrlData", 100);
	msgpub = n.advertise<std_msgs::Float32MultiArray>("VelocityCtrlData", 1);

	_ui->label_tarvel->setText(QString::number(0));
        _ui->label_curvel->setText(QString::number(0));
	
	
}

void VelocityCtrlThread::LocalizationTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
	if(!m_bVelTopicUpdated) 
	{
		//qDebug()<<"Thread::PosTopicProcess x:"<<msg->data.at(3);
		m_currentVel = msg->data.at(3);
		
		m_bVelTopicUpdated = true;


	}

}

void VelocityCtrlThread::ControlDataTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
	{
		QMutexLocker locker(&m_mutex);
		if( _ui->checkBox_Vel->isChecked() )
		{
		TargetVelUpdate(msg->data.at(6));
		printf("%lf\n",msg->data.at(6));
		}
		else
		{
		TargetVelUpdate(0);
		}
	}
}

void VelocityCtrlThread::TargetVelUpdate(float targetVel)
{
	m_targetVel = targetVel;	
}


void VelocityCtrlThread::TargetVelUpdate()
{
	//m_currentVel = rand()%20;
	//m_targetVel = rand()%20;	
}


void VelocityCtrlThread::stop()
{
	//qDebug()<<"Thread::stop called from main thread:"<<currentThreadId();
	QMutexLocker locker(&m_mutex);
	m_bThreadStop = true;
	_ui->label_tarvel->setText("---");
        _ui->label_curvel->setText("---");
}

void VelocityCtrlThread::run()
{
	int cnt = 0;
	ros::Rate loop_rate(10);
	while(1)
	{
		{
			QMutexLocker locker(&m_mutex);
			if(m_bThreadStop) break;

			if(m_bVelTopicUpdated)
			{
				cnt++;
				if( cnt == 50 )
				{
					_ui->label_tarvel->setText(QString::number(m_targetVel));
					_ui->label_curvel->setText(QString::number(m_currentVel));
					cnt =0;
				}
				//TargetVelUpdate();

				//TargetVelUpdate(15.0);

				float vel_error = m_targetVel - m_currentVel;
				if (fabs(vel_error) < fabs(m_limit_vel_low_error))
				{
					if(m_targetVel == 0)
					{
					     m_brake = m_auto_brake;
					}
				}
				else
				{
					if(m_targetVel > 0 && m_targetVel <= m_brakingCtrlVal) // velocity control using brake pedal
					{
					 if(vel_error > 0.0 )
					{
						m_accel = 0.0;
						m_brake = m_brake + m_brake_pgain*1.0 * vel_error;
						//printf("%lf\n",m_brake);
						if(m_brake <= m_brake_min)
							m_brake = m_brake_min;
						else if(m_brake >= m_brake_max)
							m_brake = m_brake_max;
					}
					else
					{
						m_accel = 0.0;
						m_brake = m_brake - m_brake_pgain*1.0 * vel_error;
						if(m_brake <= m_brake_min)
							m_brake = m_brake_min;
						else if(m_brake >= m_brake_max)
							m_brake = m_brake_max;
					}
					}
					else
					{ 
					if(vel_error > 0.0 )
					{
						m_accel = m_accel +m_accel_pgain * vel_error;
						if(m_accel >= m_accel_max)
							m_accel = m_accel_max;
						else if(m_accel <= m_accel_min)
							m_accel = m_accel_min;

						m_brake = 0.0;
						
					}
					else
					{
						m_brake = m_brake + m_brake_pgain * vel_error;
						m_accel = 0.0;
						if(m_brake <= m_brake_min)
							m_brake = m_brake_min;
						else if(m_brake >= m_brake_max)
							m_brake = m_brake_max;
					}
					}
				}
				// publish msg
				std_msgs::Float32MultiArray msg;
				msg.data.push_back(m_accel);
				msg.data.push_back(m_brake);
				//MotionPlanner::VelocityCtrlData data;
				//data.acc = m_accel;
				//data.brk = m_brake;
				msgpub.publish(msg);
				m_bVelTopicUpdated = false;
			}
		}
		ros::spinOnce();
		loop_rate.sleep();

	}
}

