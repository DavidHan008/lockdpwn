#include <ros/ros.h>
#include <string>
#include <QtGui/QMainWindow>
#include <QThread>
#include <QStringListModel>
#include "../../../build/localization/ui_localization_gui.h"

#include "Filter.h"

#include <localization/GpsReceiverData.h>
#include <localization/CarCanData.h>

#include <std_msgs/Float32MultiArray.h>
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
	ros::Subscriber gpssub;
	ros::Subscriber exsub;
	ros::Subscriber exsub2;
	ros::Publisher logpub;
	ros::Publisher logpub2;

	// ed: gazebo용 섭스크라이버 추가
	ros::Subscriber sub_gazebo_vel;
	ros::Subscriber sub_gazebo_steer;


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

	// ed: 가제보에서 속도값을 서브스크라이브하는 콜백함수
	void getVelFromGazebo(const geometry_msgs::Twist::ConstPtr& msg);
	// ed: 가제보에서 스티어링 값을 섭스크라이브하는 콜백함수
	void getSteerFromGazebo(const geometry_msgs::Wrench::ConstPtr& msg);
	double gazebo_vel;
	double gazebo_steer;
	bool gazeboFlag;
};
