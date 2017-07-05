#include "../inc/PurePursuitThread.h"
#include <QDebug>
#include <std_msgs/Float32MultiArray.h>

#define _RAD2DEG	(180./M_PI)
#define _DEG2RAD	(M_PI/180.)

void PurePursuitThread::SubscribeTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
        //qDebug()<<"Thread::LocalizationTopicProcess x:"<<msg->x<<" y:"<<msg->y;
        m_lookX =msg->data.at(0);
        m_lookY = msg->data.at(1);
        m_resdist =msg->data.at(2);

        m_pos[0] = msg->data.at(3);
        m_pos[1] = msg->data.at(4);


        m_heading = msg->data.at(5)*_RAD2DEG;

	Compute();
	/*
        if( msg->data.at(5)*_RAD2DEG < 0 )
        {
            m_heading = 360.0 + msg->data.at(5)*_RAD2DEG;
        }
        else
        {
            m_heading = msg->data.at(5)*_RAD2DEG;
        }

        m_heading += 90.0;
        if( m_heading > 360.0)
        {
            m_heading = m_heading - 360.0;
        }
	*/
        //m_heading = m_heading ;
        //std::cout << "heading " << m_heading << " " << msg->data.at(5)<<std::endl;
       

}
PurePursuitThread::PurePursuitThread(int argc, char** argv, Ui::MainWindow* ui)
    :m_bThreadStop(false)
    , init_argc(argc), init_argv(argv), _ui(ui)
{

    ros::init(init_argc, init_argv, "PurePursuitThread");
    ros::NodeHandle n;

    _cnt =0;
    m_lookX = 0.0;
    m_lookY = 0.0;
    m_resdist = -1.0;

    // receive topic
    // topicName, queue size
    m_len_c2r = 1.10;
    m_len_f2r = 2.845;
    m_ratio_s2w = 18.6;
    m_limit_steerAngle = 540.0;
    m_bPosTopicUpdated = false;

    possub = n.subscribe("ControlData", 10, &PurePursuitThread::SubscribeTopicProcess, this);

    // publish data
    msgpub = n.advertise<std_msgs::Float32MultiArray>("SteerAngleData", 10);

    //_ui->label_sas->setText(QString::number(0));
    _ui->label_sas->setText(QString::number(m_steerAngle));
}


void PurePursuitThread::stop()
{
    qDebug()<<"Thread::stop called from main thread:"<<currentThreadId();
    QMutexLocker locker(&m_mutex);
    m_bThreadStop = true;
    _ui->label_sas->setText("---");
}

void PurePursuitThread::Compute()
{
	if( _ui->checkBox_Manual->isChecked() )
	    {
		std_msgs::Float32MultiArray msg;
		msg.data.push_back(_ui->lcdNumber->value());
		msgpub.publish(msg);
	    }
	    else
	    {
			if( m_resdist == -1.0)
			{
			    m_steerAngle = 0;
			}
			else
			{
			    m_lookAheadPos[0] = m_lookX;
			    m_lookAheadPos[1] = m_lookY;

			    // Pure Pursuit Algorithm
			    m_pos[0] = m_pos[0] - m_len_c2r*cos(m_heading*_DEG2RAD);
			    m_pos[1] = m_pos[1] - m_len_c2r*sin(m_heading*_DEG2RAD);
			    Vector2d L = m_lookAheadPos-m_pos;
			    Vector2d Yv(-sin(m_heading*_DEG2RAD),cos(m_heading*_DEG2RAD));
			    Vector2d YL(L[0]*Yv[0],L[1]*Yv[1]);


			    float YLtemp = YL[0]+YL[1];


			    if( YLtemp != 0 )
			    {
				m_lookAheadLength = L.norm();

				m_steerAngle = (m_ratio_s2w*m_len_f2r*2.0*YLtemp)/(m_lookAheadLength*m_lookAheadLength);
				m_steerAngle *= _RAD2DEG;
				m_steerAngle *= -1.0;
				if(m_steerAngle>m_limit_steerAngle)
				{
				    m_steerAngle=m_limit_steerAngle;
				}
				else if(m_steerAngle<-m_limit_steerAngle)
				{
				    m_steerAngle=-m_limit_steerAngle;
				}
				//printf("Pos:(%f,%f) LookPos:(%f,%f) lookLength:%f(%f) steer:%f steer(before):%f heading:%f(%f)\n",m_pos[0], m_pos[1], m_lookAheadPos[0], m_lookAheadPos[1],m_lookAheadLength,resdist,m_steerAngle,tmpSteer,m_heading,m_heading_ori);
				//printf("Pos:(%f,%f) LookPos:(%f,%f) L:(%f,%f) Yv:(%f,%f) YL:(%f,%f) YLtemp:%f lookLength:%f(%f) steer:%f steer(before):%f heading:%f\n",m_pos[0], m_pos[1], m_lookAheadPos[0], m_lookAheadPos[1],L[0],L[1],Yv[0],Yv[1],YL[0],YL[1],YLtemp,m_lookAheadLength,resdist,m_steerAngle,tmpSteer,m_heading);

			    }
			    else
			    {
				m_steerAngle = 0;
			    }
			}
			_cnt++;
			if( _cnt == 50 )
			{
			  _ui->label_sas->setText(QString::number(m_steerAngle));
			  qDebug()<<"steerAngle : "<<m_steerAngle ;
			_cnt =0;
			}

			//printf("Steer : %lf\n",m_steerAngle);
			std_msgs::Float32MultiArray msg;
			msg.data.push_back(m_steerAngle);
			msgpub.publish(msg);
	}

}
void PurePursuitThread::run()
{
    
    ros::Rate loop_rate(100);
    while(1)
    {
        
        {
            QMutexLocker locker(&m_mutex);
            if(m_bThreadStop) break;
        }
        ros::spinOnce();
        loop_rate.sleep();

    }
}
