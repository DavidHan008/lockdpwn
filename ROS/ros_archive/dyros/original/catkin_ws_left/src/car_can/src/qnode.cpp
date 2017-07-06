#include <ros/ros.h>
#include <ros/network.h>
#include <string>


#include "../inc/qnode.h"
#include "stdlib.h"
#include "time.h"

	
QNode::QNode(int argc, char** argv, Ui::MainWindow* ui, CAN_OBD2* pCarCan, QObject *parent)
	: QThread(parent)
	, init_argc(argc), init_argv(argv), _ui(ui), m_pCarCan(pCarCan)
{
	threadStop = false;
	ros::init(init_argc,init_argv,"car_can");

	ros::NodeHandle n;

	// Add your ros communications here.

	carData_publisher = n.advertise<car_can::CarCanData>("CarCanData", 10);
}


void QNode::stop()
{
	threadStop = true;
}

void QNode::run() {

	qDebug("qnode thread start");
	// 루프 주기를 설정한다. "10" 이라는 것은 10Hz(1/10 sec)를 말하는 것으로 0.1초 간격으로 반복된다
	// "1" is 1Hz, 1 second.
	ros::Rate loop_rate(50);

	srand ( time(NULL) );

	while ( ros::ok() )
	{
		if(threadStop == true)
			break;

		car_can::CarCanData canData;
		
		// topic receive data
		for(int i = 0 ; i < 3 ; i++)
		{
			canData.gyro[i] = m_pCarCan->m_gyro[i];
			canData.accl[i] = m_pCarCan->m_accl[i];
			canData.magnet[i] = m_pCarCan->m_magnet[i];
		}
		canData.sas = m_pCarCan->m_steeringAngle;
		canData.obdVel1 = m_pCarCan->m_speed1;
		canData.obdVel2 = m_pCarCan->m_speed2;
		carData_publisher.publish( canData );

		ros::spinOnce();
		loop_rate.sleep();
	}
	qDebug("qnode thread end");
}


