#include <ros/ros.h>
#include <ros/network.h>
#include <string>

#include <sstream>
#include "../inc/qnode.h"
 
//#define SIM
void QNode::SubTopicProcess(const geometry_msgs::Pose2D::ConstPtr& msg){
  if(!ssFlag && !spFlag) {
    _ins->m_tm_x = msg->x;
    _ins->m_tm_y = msg->y;
    _ins->m_gps.heading = msg->theta;
    ssFlag = true;
    // std::cout << "heading " <<  msg->theta<<std::endl;
  }
}

// ed: 가제보에서 속도값을 서브스크라이브하는 콜백함수
void QNode::getVelFromGazebo(const geometry_msgs::Twist::ConstPtr& msg){
  gazebo_vel = msg->linear.x;
}

// ed: 가제보에서 스티어링 값을 섭스크라이브하는 콜백함수
void QNode::getSteerFromGazebo(const geometry_msgs::Wrench::ConstPtr& msg){
  gazebo_steer = msg->torque.z;
}


QNode::QNode(int argc, char** argv, Ui::MainWindow* ui, Filter* ins, QObject *parent)
    : QThread(parent)
    , init_argc(argc), init_argv(argv), _ui(ui), _ins(ins){
  m_bSubTopicUpdated =false;
  threadStop = false;
  ssFlag = false;
  spFlag = false;

  ros::init(init_argc, init_argv, "localization_gazebo");
  ros::NodeHandle n;

  // receive topic
  // topicName, queue size
  gpssub = n.subscribe("my_pose", 10, &QNode::SubTopicProcess, this); // from velodyne-loam

  // ed: 코드 추가했다. 가제보의 차량을 제어하기 위한 코드
  logpub_gazebo = n.advertise<std_msgs::Float32MultiArray>("LocalizationData_gazebo", 10);
  sub_gazebo_vel = n.subscribe("all_in_one/vel", 10, &QNode::getVelFromGazebo, this);
  sub_gazebo_steer = n.subscribe("all_in_one/steer", 10, &QNode::getSteerFromGazebo, this);

  m_obdVel1 = 0.;
}


void QNode::stop(){
  threadStop = true;
  ssFlag = false;
  spFlag = false;
}

void QNode::run(){
  struct timeval timePrev;
  gettimeofday(&timePrev, NULL);

  // set loop rate 10 = 10Hz = 1/10 sec.
  // "1" is 1Hz, 1 second.

  ros::Rate loop_rate(100);

  qDebug("qnode Thread Start");
	
  while ( !threadStop ){
    struct timeval timeCur;
    //localization::LocalizationData data;
    //geometry_msgs::Pose2D data2;

    gettimeofday(&timeCur, NULL);

    double dt = (double)(timeCur.tv_sec) + (double)(timeCur.tv_usec)/1000000.0 - (double)(timePrev.tv_sec) - (double)(timePrev.tv_usec)/1000000.0;


    //printf("while flag :%d\n", flag);
    if( spFlag )
    {
      //printf("계산 : %f %f \n", _ins->m_p[0],_ins->m_p[1]);

      _ins->DoCal(dt);
      spFlag = false;
      //puts("----------------------------------------------");
    }

    //data.heading = _ins->m_heading;
    //data.x = _ins->m_p[0];
    //data.y = _ins->m_p[1];
    //data.v = m_obdVel1;
    //logpub.publish( data );

    // ed: 코드 추가 가제보용
    std_msgs::Float32MultiArray msg_gazebo;

    msg_gazebo.data.push_back(0);
    msg_gazebo.data.push_back(0);
    msg_gazebo.data.push_back(0);
    msg_gazebo.data.push_back(gazebo_vel);

    // ed: 데이터 형식을 맞추기 위해 위에 의미없는 값 '0' 3개를 추가한 후 퍼블리시~
    logpub_gazebo.publish(msg_gazebo);


		
    timePrev = timeCur;

    ros::spinOnce();
    loop_rate.sleep();
  }
  qDebug("qnode Thread end");
}



