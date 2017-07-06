#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../inc/qnode.h"

/*
void QNode::PurePursuitTopicProcess(const mcu_can::PurePursuitData::ConstPtr& msg)
{
	if(m_purePursuitMsgUpdated == false)
	{
		m_sas = msg->sas;
		m_purePursuitMsgUpdated = true;
		//printf("sas %f\n",m_sas);
	}
}
void QNode::VelocityCtrlTopicProcess(const mcu_can::VelocityCtrlData::ConstPtr& msg)
{
	if(m_velocityCtrlMsgUpdated == false)
	{
		m_acc = msg->acc;
		m_brk = msg->brk;
		m_velocityCtrlMsgUpdated = true;
	}
}

*/

void QNode::PurePursuitTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
	//printf("sas %f\n",m_sas);
	if(m_purePursuitMsgUpdated == false)
	{
		//m_sas = msg->sas;
		m_sas = msg->data.at(0);
		m_purePursuitMsgUpdated = true;
		//printf("sas %f\n",m_sas);
	}
}	
void QNode::VelocityCtrlTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
	if(m_velocityCtrlMsgUpdated == false)
	{
		m_acc =  msg->data.at(0);
		m_brk =  msg->data.at(1);
		m_velocityCtrlMsgUpdated = true;
	}
}

QNode::QNode(int argc, char** argv, Ui::MainWindow* ui,CAN_MCU* _pCanMCU, QObject *parent)
	: QThread(parent)
	, init_argc(argc), init_argv(argv),m_pCanMCU(_pCanMCU), _ui(ui)
{
	m_autonomousMode = false;
	m_velocityCtrlMsgUpdated = false;
	m_purePursuitMsgUpdated = false;

	threadStop = false;
	ros::init(init_argc,init_argv, "CAN_MCU");

	ros::NodeHandle n;

	purePursuitSub = n.subscribe("SteerAngleData", 10, &QNode::PurePursuitTopicProcess, this);
	velocityCtrlSub = n.subscribe("VelocityCtrlData", 10, &QNode::VelocityCtrlTopicProcess, this);

	//mcuData_publisher = n.advertise<mcu_can::McuData>("McuData", 10);
}


void QNode::stop()
{
	threadStop = true;
}

void QNode::VelModeTransmit(int mode, float brkAng, float accAng)
{
	if( m_pCanMCU )
		{
		uint8_t CanDataBuf[8];
		uint8_t* pCanData = CanDataBuf;
	
		// Acc/Brake
		UINT8 Temp0_8 = 0;
		int8_t Temp1_8 = 0;
		UINT8 Temp2_8 = 0;

		if( mode == 1 ) // auto
		{
			Temp0_8 = 4;
			Temp1_8 = brkAng;
			Temp2_8 = accAng;
		
		}

		else if( mode == 3 ) // driver
		{	
			Temp0_8 = 0;
			Temp1_8 = 0;
			Temp2_8 = 0;
		}

		if( Temp1_8 > 100 ) 
		{
			Temp1_8 = 100;
		}
		else if( Temp1_8 < -100 ) 
		{
			Temp1_8 = -100;
		}

		if( Temp2_8 > 100 ) 
		{
			Temp2_8 = 100;
		}
		else if( Temp2_8 <= 0 ) 
		{
			Temp2_8 = 0;
		}
	
	
	
		//SAS	
		pCanData[0] = Temp0_8;
		pCanData[1] = Temp1_8;
		pCanData[2] = Temp2_8;
		pCanData[3] = 0;
		pCanData[4] = 0;
		pCanData[5] = 0;
		pCanData[6] = 0;
		pCanData[7] = 0;

		m_pCanMCU->_canport->TransmitCanMsg(pCanData,0x105);
	}
}


void QNode::SteerModeTransmit(int mode, float steerAng)
{
static int count;
	if( m_pCanMCU )
	{
		uint8_t CanDataBuf[8];
		uint8_t* pCanData = CanDataBuf;

		UINT16 Temp_16 = 0;
		if( mode == 4 )
		{
			pCanData[0] = 1;
			Temp_16 = steerAng*10.0;
			//printf("desired Steer: %lf\n",steerAng);
		}
		
		else if( mode == 6 )
		{	
			pCanData[0] = 0;
			Temp_16 = 0;
		}
	
		//SAS	
		pCanData[1] = Temp_16 & 0xFF;
		pCanData[2] = (Temp_16>>8) & 0xFF;
		pCanData[3] = 0;
		pCanData[4] = 0;
		pCanData[5] = 0;
		pCanData[6] = 0;
		pCanData[7] = 0;

		m_pCanMCU->_canport->TransmitCanMsg(pCanData,0x101);
	}

}
void QNode::run() {
	ros::Rate loop_rate(100);
	while ( ros::ok() )
	{
		if(threadStop == true)
			break;
		if(m_autonomousMode)
		{
			//printf("automode\n");
			if(m_velocityCtrlMsgUpdated)
			{			
				VelModeTransmit(m_velMode,m_brk,m_acc);
				m_velocityCtrlMsgUpdated = false;
			}
			if(m_purePursuitMsgUpdated)
			{
				SteerModeTransmit(m_steerMode,m_sas);
				m_purePursuitMsgUpdated = false;
			}
		}

		//mcu_can::McuData mcuData;
		//mcuData.sas = m_pCanMCU->_mcuSAS.SteeringAngle;
		//mcuData_publisher.publish( mcuData );

		ros::spinOnce();
		loop_rate.sleep();
		
	}
	qDebug("qnode Thread End");
}


