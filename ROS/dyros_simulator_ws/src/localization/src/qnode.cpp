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
  gazeboFlag = true;
}

// ed: 가제보에서 스티어링 값을 섭스크라이브하는 콜백함수
void QNode::getSteerFromGazebo(const geometry_msgs::Wrench::ConstPtr& msg){
  gazebo_steer = msg->torque.z;
  gazeboFlag = true;
}


// 토픽에 대한 함수들.
void QNode::GpsTopicProcess(const localization::GpsReceiverData::ConstPtr& msg){
  //printf("test0\n");
  if(!ssFlag && !spFlag){
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
	
    ssFlag = true;
  }
}

void QNode::imuHandler(const sensor_msgs::Imu::ConstPtr& imuIn){
  if(ssFlag && !spFlag)  {
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

void QNode::CanTopicProcess(const localization::CarCanData::ConstPtr& msg){
  /*
   if(m_bSubTopicUpdated == false)
   {
   _ins->m_canimu.obdVel = msg->obdVel1;
   m_obdVel1 = msg->obdVel1;
   m_bSubTopicUpdated =true;
   }*/
  if(ssFlag && !spFlag){
    ///printf("test\n");
    char text[1024];

    for(int i = 0 ; i < 3 ; i++) {
      _ins->m_canimu.gyro[i] = msg->gyro[i];
      _ins->m_canimu.accl[i] = msg->accl[i];
      _ins->m_canimu.magnet[i] = msg->magnet[i];
      _ins->m_canimu.obdVel = msg->obdVel1;
    }
    m_obdVel1 = msg->obdVel1;

    ssFlag = false;
    spFlag = true;
  }
}


QNode::QNode(int argc, char** argv, Ui::MainWindow* ui, Filter* ins, QObject *parent)
    : QThread(parent)
    , init_argc(argc), init_argv(argv), _ui(ui), _ins(ins)
{
  m_bSubTopicUpdated =false;
  threadStop = false;
  ssFlag = false;
  spFlag = false;

  ros::init(init_argc, init_argv, "localization");
  ros::NodeHandle n;

  // receive topic
  // topicName, queue size
  //printf("init Qnode\n");
  //gpssub = n.subscribe("GpsReceiverData", 10, &QNode::GpsTopicProcess, this);
  gpssub = n.subscribe("my_pose", 10, &QNode::SubTopicProcess, this); // from velodyne-loam
  //exsub2 = n.subscribe("/imu/data", 10, &QNode::imuHandler, this);
  exsub = n.subscribe("CarCanData", 10, &QNode::CanTopicProcess, this);

  // send topic
  // topicName, queue size
  //logpub = n.advertise<localization::LocalizationData>("LocalizationData", 10);
  //logpub2 = n.advertise<geometry_msgs::Pose2D>("my_pose2", 10);
  logpub2 = n.advertise<std_msgs::Float32MultiArray>("LocalizationData", 10);


  // ed: 코드 추가했다. 가제보의 차량을 제어하기 위한 코드
  sub_gazebo_vel = n.subscribe("all_in_one/vel", 10, &QNode::getVelFromGazebo, this);
  sub_gazebo_steer = n.subscribe("all_in_one/steer", 10, &QNode::getSteerFromGazebo, this);
  gazeboFlag = false;

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
	
  while ( !threadStop )  {
    struct timeval timeCur;
    //localization::LocalizationData data;
    //geometry_msgs::Pose2D data2;

    gettimeofday(&timeCur, NULL);

    double dt = (double)(timeCur.tv_sec) + (double)(timeCur.tv_usec)/1000000.0 - (double)(timePrev.tv_sec) - (double)(timePrev.tv_usec)/1000000.0;


    //printf("while flag :%d\n", flag);
    if( spFlag ) {
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

    double tmpTheta = _ins->m_heading + _DEG2RAD *(90.0);

    if( tmpTheta >= _DEG2RAD*360.0 )    {
      tmpTheta -= _DEG2RAD*360.0;
    }
    std_msgs::Float32MultiArray msg_pub;

    // ed: gazebo를 사용하지 않는경우
    if(!gazeboFlag){
      msg_pub.data.push_back(_ins->m_p[0]);
      msg_pub.data.push_back(_ins->m_p[1]);
      msg_pub.data.push_back(tmpTheta);
      msg_pub.data.push_back(m_obdVel1*0.278);

      // ed: LocalizationData 퍼블리시한다
      logpub2.publish( msg_pub );
    }
    // ed: gazebo를 사용하는 경우
    else{
      msg_pub.data.push_back(0);
      msg_pub.data.push_back(0);
      msg_pub.data.push_back(0);
      msg_pub.data.push_back(gazebo_vel);

      // ed: LocalizationData 퍼블리시한다
      logpub2.publish( msg_pub );
    }


    timePrev = timeCur;

    ros::spinOnce();
    loop_rate.sleep();
  }
  qDebug("qnode Thread end");
}



