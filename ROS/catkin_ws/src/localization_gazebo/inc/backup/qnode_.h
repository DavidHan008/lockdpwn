#include <ros/ros.h>
#include <string>
#include <QtGui/QMainWindow>
#include <QThread>
#include <QStringListModel>
#include "../../../build/localization/ui_localization_gui.h"

#include "Filter.h"

#include <localization/GpsReceiverData.h>
#include <localization/CarCanData.h>
#include <localization/LocalizationData.h>

#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Pose2D.h>
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

private:
	int init_argc;
	char** init_argv;
	bool threadStop;
	Ui::MainWindow* _ui;
	Filter* _ins;
	float m_obdVel1;
	bool m_bSubTopicUpdated;
	QMutex m_gps_mutex;
	QMutex m_imu_mutex;
	bool m_init_cantopic;
	bool m_init_gpstopic;
	struct timeval timePrev;
	struct timeval timeCur;
};



