#include <QtGui/QMainWindow>
#include <QtCore>
#include <ros/ros.h>
#include <Eigen/Core>
#include <std_msgs/Float32MultiArray.h>


using namespace Eigen;

class VelocityCtrlThread : public QThread{
  Q_OBJECT;

private :
  int init_argc;
  char** init_argv;

  ros::Subscriber possub;
  ros::Subscriber drcsub;
  ros::Publisher msgpub;

  bool m_bThreadStop;
  bool m_bVelTopicUpdated;
  QMutex m_mutex;
	
  float m_currentVel;
  float m_targetVel;
  float m_accel;
  float m_brake;
  float m_brake_pgain;
  float m_accel_pgain;
  float m_auto_brake;
  float m_accel_max;
  float m_accel_min;
  float m_brake_max;
  float m_brake_min;
  float m_limit_vel_low_error;
  float m_limit_vel_up_error;

public :
  void DrcTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg);
  void LocalizationTopicProcess(const std_msgs::Float32MultiArray::ConstPtr& msg);
  void TargetVelUpdate();
  void TargetVelUpdate(float targetVel);
  VelocityCtrlThread(int argc, char** argv);


  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
      public slots:
      void stop();
private:
      void run();
};
