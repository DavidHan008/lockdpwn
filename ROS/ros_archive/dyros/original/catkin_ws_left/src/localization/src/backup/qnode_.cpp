#include <ros/ros.h>
#include <ros/network.h>
#include <string>

#include <sstream>
#include "../inc/qnode.h"

/*
// 토픽에 대한 함수들.
void QNode::GpsTopicProcess(const localization::GpsReceiverData::ConstPtr& msg)
{
	//printf("test0\n");
	if(!ssFlag && !spFlag)
	{
		// 데이터 할당 시작.
		//printf("test\n");
		_ins->m_gps.t = msg->t;
		_ins->m_gps.utc = msg->utc;
		_ins->m_gps.gps_quality = msg->gps_quality;
		_ins->m_gps.no_sats = msg->no_sats;
		_ins->m_gps.hdop = msg->hdop;
		_ins->m_gps.latitude = msg->latitude;
		_ins->m_gps.longitude = msg->longitude;
		_ins->m_gps.altitude = msg->altitude;
		_ins->m_gps.heading = msg->heading;
		_ins->m_gps.velocity = msg->velocity;

		_ins->m_tm_x = msg->tm_x;
		_ins->m_tm_y = msg->tm_y;
	

		// 데이터 할당 끝.

		ssFlag = true;
	}
}

void QNode::imuHandler(const sensor_msgs::Imu::ConstPtr& imuIn)
{

  if(ssFlag && !spFlag)
  {
  _ins->m_canimu.accl[0] = imuIn->linear_acceleration.x;
  _ins->m_canimu.accl[1] = imuIn->linear_acceleration.y;
  _ins->m_canimu.accl[2] = imuIn->linear_acceleration.z;

  _ins->m_canimu.gyro[0] = imuIn->angular_velocity.x;
  _ins->m_canimu.gyro[1] = imuIn->angular_velocity.y;
  _ins->m_canimu.gyro[2] = imuIn->angular_velocity.z;
  ssFlag = false;
  spFlag = true;
m_bSubTopicUpdated =false;
  }

}
*/

void QNode::SubTopicProcess(const geometry_msgs::Pose2D::ConstPtr& msg)
{

	//std::cout << "gps - out" << std::endl;
    	
	if( m_init_gpstopic && m_init_cantopic )
	{
		m_gps_mutex.lock();

		_ins->m_tm_x = msg->x;
       		_ins->m_tm_y = msg->y;
		_ins->m_tm_z = 0.0;
        	_ins->m_theta = msg->theta;
		_ins->DoGPS();

		m_gps_mutex.unlock();
	}
	
	if( m_init_gpstopic == false )
	{
		m_init_gpstopic = true;
	}
	//std::cout << "gps - in" << std::endl;
	
}


void QNode::CanTopicProcess(const localization::CarCanData::ConstPtr& msg)
{
	//std::cout << "can - in" << std::endl;
	if( m_init_cantopic == false )
	{
		gettimeofday(&timePrev, NULL);
	}
	gettimeofday(&timeCur, NULL);

	double dt = (double)(timeCur.tv_sec) + (double)(timeCur.tv_usec)/1000000.0 - (double)(timePrev.tv_sec) - (double)(timePrev.tv_usec)/1000000.0;
	
	if( m_init_gpstopic && m_init_cantopic )
	{
		m_gps_mutex.lock();

		for(int i = 0 ; i < 3 ; i++)
		{
			_ins->m_canimu.gyro[i] = msg->gyro[i];
			_ins->m_canimu.accl[i] = msg->accl[i];
			_ins->m_canimu.magnet[i] = msg->magnet[i];
		}
		m_obdVel1 = msg->obdVel1* 0.278;
		_ins->m_canimu.obdVel = m_obdVel1;
		_ins->DoIMU(dt);

		m_gps_mutex.unlock();
	}
	
	timePrev = timeCur;
	if( m_init_cantopic == false )
	{
		m_init_cantopic = true;
	}
	//std::cout << "can - out" << std::endl;
}


QNode::QNode(int argc, char** argv, Ui::MainWindow* ui, Filter* ins, QObject *parent)
	: QThread(parent)
	, init_argc(argc), init_argv(argv), _ui(ui), _ins(ins)
{
	threadStop = false;
	m_init_cantopic = false;
	m_init_gpstopic = false;
	ros::init(init_argc, init_argv, "localization");
	ros::NodeHandle n;

	// receive topic
	// topicName, queue size
	//printf("init Qnode\n");
	//gpssub = n.subscribe("GpsReceiverData", 10, &QNode::GpsTopicProcess, this);
	 gpssub = n.subscribe("my_pose", 10, &QNode::SubTopicProcess, this);
    	//exsub2 = n.subscribe("/imu/data", 10, &QNode::imuHandler, this);
	exsub = n.subscribe("CarCanData", 10, &QNode::CanTopicProcess, this);

	// send topic
	// topicName, queue size
	logpub = n.advertise<localization::LocalizationData>("LocalizationData", 10);
	//logpub2 = n.advertise<geometry_msgs::Pose2D>("my_pose2", 10);
	logpub2 = n.advertise<std_msgs::Float32MultiArray>("my_pose3", 10);

	m_obdVel1 = 0.;

	
}


void QNode::stop()
{
	threadStop = true;
	
}

void QNode::run()
{
	// set loop rate 10 = 10Hz = 1/10 sec.
	// "1" is 1Hz, 1 second.

	ros::Rate loop_rate(100);

	qDebug("qnode Thread Start");
	float x,y,theta,v;
	while ( !threadStop )
	{
		m_gps_mutex.lock();
		
		x = _ins->m_p[0];
		y = _ins->m_p[1];
		theta = _ins->m_heading;
		v = m_obdVel1;
		
		m_gps_mutex.unlock();
		
		/////////////////////////////////////////////////////////
		localization::LocalizationData data;
		data.heading = theta;
		data.x = x;
		data.y = y;
		data.v = v;
		logpub.publish( data ); 

		/////////////////////////////////////////////////////////
		std_msgs::Float32MultiArray msg;
		double tmpTheta = theta + _DEG2RAD *(90.0);
		if( tmpTheta >= _DEG2RAD*360.0 )
		{
			tmpTheta -= _DEG2RAD*360.0;
		}
		msg.data.push_back(x);
		msg.data.push_back(y);
		msg.data.push_back(tmpTheta);
		msg.data.push_back(v);
		logpub2.publish( msg ); 
               // std::cout<<_ins->m_p[0]<<" "<<_ins->m_p[1]<<std::endl;

		

		ros::spinOnce();
		loop_rate.sleep();
	}
	qDebug("qnode Thread end");
}



