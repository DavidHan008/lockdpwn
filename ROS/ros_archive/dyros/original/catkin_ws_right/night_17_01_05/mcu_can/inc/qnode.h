#include <ros/ros.h>
#include <string>
#include <QtGui/QMainWindow>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/Float32MultiArray.h>
#include "../../../build/mcu_can/ui_mcu_can_gui.h"
#include "CAN_MCU.h"


class QNode : public QThread {
	Q_OBJECT
public:
	QNode(int argc, char** argv, Ui::MainWindow* ui, CAN_MCU* _pCanMCU, QObject *parent = 0);

	void run();
	void stop();
	void GetMotionMsg(float& sas, float& acc, float& brk);
	ros::Subscriber purePursuitSub;
	ros::Subscriber velocityCtrlSub;
	//ros::Publisher mcuData_publisher;

	void VelModeTransmit(int mode, float brkAng, float accAng);
	void SteerModeTransmit(int mode, float steerAng);
	void PurePursuitTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg);
	void VelocityCtrlTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg);
private:
	int init_argc;
	char** init_argv;
	bool threadStop;
	Ui::MainWindow* _ui;

	bool m_purePursuitMsgUpdated;
	bool m_velocityCtrlMsgUpdated;
	
	float m_acc;
	float m_brk;
	float m_sas;



	CAN_MCU* m_pCanMCU;
public:
	int m_steerMode;
	int m_velMode;	
	bool m_autonomousMode;
};


