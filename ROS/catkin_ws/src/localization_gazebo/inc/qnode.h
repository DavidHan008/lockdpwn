#include <ros/ros.h>
#include <string>
#include <QtGui/QMainWindow>
#include <QThread>
#include <QStringListModel>
#include "../../../build/localization/ui_localization_gui.h"

#include "Filter.h"

#include <localization/GpsReceiverData.h>
#include <localization/CarCanData.h>

#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Wrench.h>
#include <std_msgs/Float32MultiArray.h>
#include <QMutex>

class QNode : public QThread {
	Q_OBJECT
public:
	QNode(int argc, char** argv, Ui::MainWindow* ui, Filter* ins, QObject *parent = 0);

	void run();
	void stop();

	void GpsTopicProcess(const localization::GpsReceiverData::ConstPtr& msg);
	void CanTopicProcess(const localization::CarCanData::ConstPtr& msg);
	void SubTopicProcess(const geometry_msgs::Pose2D::ConstPtr& msg);
	void imuHandler(const sensor_msgs::Imu::ConstPtr& imuIn);

	void getVelFromGazebo(const geometry_msgs::Twist::ConstPtr& msg); // ed: 함수 추가 가제보용
	void getSteerFromGazebo(const geometry_msgs::Wrench::ConstPtr& msg); // ed: 함수 추가 가제보용

	ros::Subscriber gpssub;
	ros::Subscriber exsub;
	ros::Subscriber exsub2;
	ros::Publisher logpub;
	ros::Publisher logpub2;

	ros::Subscriber sub_gazebo_vel;  // ed: 섭스크라이버 추가
	ros::Subscriber sub_gazebo_steer;  // ed: 섭스크라이버 추가
	ros::Publisher logpub_gazebo;

private:
	int init_argc;
	char** init_argv;
	bool threadStop;
	Ui::MainWindow* _ui;
	Filter* _ins;
	float m_obdVel1;
	QMutex m_gps_mutex;
	bool m_bSubTopicUpdated;
	bool ssFlag; // subscriber, subscriber Flag
	bool spFlag; // subscriber, publisher Flag

	float gazebo_vel;  // ed: 가제보 속도변수 추가
	float gazebo_steer;  // ed: 가제보 각도변수 추가
};


