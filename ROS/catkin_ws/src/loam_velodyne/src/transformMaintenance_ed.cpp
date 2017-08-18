#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>

#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud2.h>

#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <geometry_msgs/Pose2D.h>//jh

const double PI = 3.1415926;
const double rad2deg = 180 / PI;
const double deg2rad = PI / 180;

float transformSum[6] = {0};
float transformIncre[6] = {0};
float transformMapped[6] = {0};
float transformBefMapped[6] = {0};
float transformAftMapped[6] = {0};

geometry_msgs::Pose2D Mypose;  //jh
geometry_msgs::Pose2D Mypose1;  //jh
//geometry_msgs::PoseStamped Mypos;//jh
bool in_offset = true;  
double transformoffset[6] = {0};

bool myPoseEnabled = true; // Suhan Park

ros::Publisher *pubLaserMypose1 = NULL;//jh
ros::Publisher *pubLaserMypose = NULL;//jh
ros::Publisher *pubLaserOdometry2Pointer = NULL;
tf::TransformBroadcaster *tfBroadcaster2Pointer = NULL;
nav_msgs::Odometry laserOdometry2;
tf::StampedTransform laserOdometryTrans2;


// ed: laserOdometryHandler에 의해 호출되는 함수
//      transformMapped[6]과 transformIncre[6]의 값을 변경시키는 함수
void transformAssociateToMap(){
  float x1 = cos(transformSum[1]) * (transformBefMapped[3] - transformSum[3]) 
             - sin(transformSum[1]) * (transformBefMapped[5] - transformSum[5]);
  float y1 = transformBefMapped[4] - transformSum[4];
  float z1 = sin(transformSum[1]) * (transformBefMapped[3] - transformSum[3]) 
             + cos(transformSum[1]) * (transformBefMapped[5] - transformSum[5]);

  float x2 = x1;
  float y2 = cos(transformSum[0]) * y1 + sin(transformSum[0]) * z1;
  float z2 = -sin(transformSum[0]) * y1 + cos(transformSum[0]) * z1;

  transformIncre[3] = cos(transformSum[2]) * x2 + sin(transformSum[2]) * y2;
  transformIncre[4] = -sin(transformSum[2]) * x2 + cos(transformSum[2]) * y2;
  transformIncre[5] = z2;

  float sbcx = sin(transformSum[0]);
  float cbcx = cos(transformSum[0]);
  float sbcy = sin(transformSum[1]);
  float cbcy = cos(transformSum[1]);
  float sbcz = sin(transformSum[2]);
  float cbcz = cos(transformSum[2]);

  float sblx = sin(transformBefMapped[0]);
  float cblx = cos(transformBefMapped[0]);
  float sbly = sin(transformBefMapped[1]);
  float cbly = cos(transformBefMapped[1]);
  float sblz = sin(transformBefMapped[2]);
  float cblz = cos(transformBefMapped[2]);

  float salx = sin(transformAftMapped[0]);
  float calx = cos(transformAftMapped[0]);
  float saly = sin(transformAftMapped[1]);
  float caly = cos(transformAftMapped[1]);
  float salz = sin(transformAftMapped[2]);
  float calz = cos(transformAftMapped[2]);

  float srx = -sbcx*(salx*sblx + calx*caly*cblx*cbly + calx*cblx*saly*sbly) 
              - cbcx*cbcz*(calx*saly*(cbly*sblz - cblz*sblx*sbly)
                           - calx*caly*(sbly*sblz + cbly*cblz*sblx) + cblx*cblz*salx)
              - cbcx*sbcz*(calx*caly*(cblz*sbly - cbly*sblx*sblz)
                           - calx*saly*(cbly*cblz + sblx*sbly*sblz) + cblx*salx*sblz);
  transformMapped[0] = -asin(srx);

  float srycrx = (cbcy*sbcz - cbcz*sbcx*sbcy)*(calx*saly*(cbly*sblz - cblz*sblx*sbly) 
                                               - calx*caly*(sbly*sblz + cbly*cblz*sblx) + cblx*cblz*salx)
                 - (cbcy*cbcz + sbcx*sbcy*sbcz)*(calx*caly*(cblz*sbly - cbly*sblx*sblz)
                                                 - calx*saly*(cbly*cblz + sblx*sbly*sblz) + cblx*salx*sblz)
                 + cbcx*sbcy*(salx*sblx + calx*caly*cblx*cbly + calx*cblx*saly*sbly);
  float crycrx = (cbcz*sbcy - cbcy*sbcx*sbcz)*(calx*caly*(cblz*sbly - cbly*sblx*sblz) 
                                               - calx*saly*(cbly*cblz + sblx*sbly*sblz) + cblx*salx*sblz)
                 - (sbcy*sbcz + cbcy*cbcz*sbcx)*(calx*saly*(cbly*sblz - cblz*sblx*sbly)
                                                 - calx*caly*(sbly*sblz + cbly*cblz*sblx) + cblx*cblz*salx)
                 + cbcx*cbcy*(salx*sblx + calx*caly*cblx*cbly + calx*cblx*saly*sbly);
  transformMapped[1] = atan2(srycrx / cos(transformMapped[0]), crycrx / cos(transformMapped[0]));
  
  float srzcrx = sbcx*(cblx*cbly*(calz*saly - caly*salx*salz) 
                       - cblx*sbly*(caly*calz + salx*saly*salz) + calx*salz*sblx)
                 - cbcx*cbcz*((caly*calz + salx*saly*salz)*(cbly*sblz - cblz*sblx*sbly)
                              + (calz*saly - caly*salx*salz)*(sbly*sblz + cbly*cblz*sblx)
                              - calx*cblx*cblz*salz) + cbcx*sbcz*((caly*calz + salx*saly*salz)*(cbly*cblz
                                                                                                + sblx*sbly*sblz) + (calz*saly - caly*salx*salz)*(cblz*sbly - cbly*sblx*sblz)
                                                                  + calx*cblx*salz*sblz);
  float crzcrx = sbcx*(cblx*sbly*(caly*salz - calz*salx*saly) 
                       - cblx*cbly*(saly*salz + caly*calz*salx) + calx*calz*sblx)
                 + cbcx*cbcz*((saly*salz + caly*calz*salx)*(sbly*sblz + cbly*cblz*sblx)
                              + (caly*salz - calz*salx*saly)*(cbly*sblz - cblz*sblx*sbly)
                              + calx*calz*cblx*cblz) - cbcx*sbcz*((saly*salz + caly*calz*salx)*(cblz*sbly
                                                                                                - cbly*sblx*sblz) + (caly*salz - calz*salx*saly)*(cbly*cblz + sblx*sbly*sblz)
                                                                  - calx*calz*cblx*sblz);
  transformMapped[2] = atan2(srzcrx / cos(transformMapped[0]), crzcrx / cos(transformMapped[0]));

  x1 = cos(transformMapped[2]) * transformIncre[3] - sin(transformMapped[2]) * transformIncre[4];
  y1 = sin(transformMapped[2]) * transformIncre[3] + cos(transformMapped[2]) * transformIncre[4];
  z1 = transformIncre[5];

  x2 = x1;
  y2 = cos(transformMapped[0]) * y1 - sin(transformMapped[0]) * z1;
  z2 = sin(transformMapped[0]) * y1 + cos(transformMapped[0]) * z1;

  transformMapped[3] = transformAftMapped[3] 
                       - (cos(transformMapped[1]) * x2 + sin(transformMapped[1]) * z2);
  transformMapped[4] = transformAftMapped[4] - y2;
  transformMapped[5] = transformAftMapped[5] 
                       - (-sin(transformMapped[1]) * x2 + cos(transformMapped[1]) * z2);
}

// ed: /laser_odom_to_init 토픽을 섭스크라이브하는 콜백함수
void laserOdometryHandler(const nav_msgs::Odometry::ConstPtr& laserOdometry){
  double roll, pitch, yaw;
  geometry_msgs::Quaternion geoQuat = laserOdometry->pose.pose.orientation;
  tf::Matrix3x3(tf::Quaternion(geoQuat.x, geoQuat.y, geoQuat.z, geoQuat.w)).getRPY(roll, pitch, yaw);

  transformSum[0] = roll;
  transformSum[1] = pitch;
  transformSum[2] = yaw;
  transformSum[3] = laserOdometry->pose.pose.position.x;
  transformSum[4] = laserOdometry->pose.pose.position.y;
  transformSum[5] = laserOdometry->pose.pose.position.z;

  transformAssociateToMap();

  if(in_offset)  {
    for(int i=0; i<6; i++  )
      // ed: /odom_Offset으로부터 transformoffset[i]값을 업데이트한 다음 transformMapped안에 더한다
      transformMapped[i] += transformoffset[i];
      // in_offset = false;
  }

  // ed: Euler각 --> 쿼터니안으로 변환 후 getQuat에 저장한다
  geoQuat = tf::createQuaternionMsgFromRollPitchYaw
            (transformMapped[0], transformMapped[1], transformMapped[2]);


  laserOdometry2.header.stamp = laserOdometry->header.stamp;

  laserOdometry2.pose.pose.orientation.x = geoQuat.x;
  laserOdometry2.pose.pose.orientation.y = geoQuat.y;
  laserOdometry2.pose.pose.orientation.z = geoQuat.z;
  laserOdometry2.pose.pose.orientation.w = geoQuat.w;

  laserOdometry2.pose.pose.position.x = transformMapped[3];   // ed: transformMapped[3] : x
  laserOdometry2.pose.pose.position.y = transformMapped[4];   //     transformMapped[4] : y
  laserOdometry2.pose.pose.position.z = transformMapped[5];   //     transformMapped[5] : z

  // ed: /integrated_to_init 토픽으로 퍼블리시한다
  pubLaserOdometry2Pointer->publish(laserOdometry2);

  laserOdometryTrans2.stamp_ = laserOdometry->header.stamp;

  // ed: roll, pitch를 없애기 위해 아래처럼 설정한다.
  //laserOdometryTrans2.setRotation(tf::Quaternion(geoQuat.x, geoQuat.y, geoQuat.z, geoQuat.w));
  laserOdometryTrans2.setRotation(tf::Quaternion(0, 0, geoQuat.z, geoQuat.w));
  laserOdometryTrans2.setOrigin(tf::Vector3(transformMapped[3], transformMapped[4], transformMapped[5]));

  // ed: /dyros/base_footprint tf를 broadcast한다
  tfBroadcaster2Pointer->sendTransform(laserOdometryTrans2);

  if(myPoseEnabled){
    // ed: laserOdometry2 ==> /my_pose, /test 토픽으로 좌표를 변환하는 코드
    /***********jh**********************************/
    Mypose.x = -laserOdometry2.pose.pose.position.y;
    Mypose.y = laserOdometry2.pose.pose.position.x;
    Mypose.theta = transformMapped[2];

    //Mypose.x = laserOdometry2.pose.pose.position.x;
    //Mypose.y = laserOdometry2.pose.pose.position.y;
    //Mypose.theta = tf::getYaw(geoQuat);

    if(transformMapped[2]<0)
      Mypose.theta += 2.0 * PI;
    else {
      //Mypose.theta += 0.5 * PI;
    }

    // ed: /my_pose 토픽으로 퍼블리시한다
    pubLaserMypose->publish(Mypose);

    Mypose1 = Mypose;
    Mypose1.theta += 0.5 * PI;

    if(Mypose1.theta > 2.0 * PI) {
      Mypose1.theta -= 2.0 * PI;
    }
    //printf("%f \n",Mypose.theta);

    // ed: /test 토픽으로 퍼블리시한다 (not used)
    pubLaserMypose1->publish(Mypose1);  //jh test
    //printf("%f %f \n",Mypose.x, Mypose.y);
  }
}

// ed: /aft_mapped_to_init을 섭스크라이브하는 콜백함수
void odomAftMappedHandler(const nav_msgs::Odometry::ConstPtr& odomAftMapped){
  double roll, pitch, yaw;
  geometry_msgs::Quaternion geoQuat = odomAftMapped->pose.pose.orientation;
  tf::Matrix3x3(tf::Quaternion(geoQuat.x, geoQuat.y, geoQuat.z, geoQuat.w)).getRPY(roll, pitch, yaw);

  transformAftMapped[0] = roll;
  transformAftMapped[1] = pitch;
  transformAftMapped[2] = yaw;

  transformAftMapped[3] = odomAftMapped->pose.pose.position.x;
  transformAftMapped[4] = odomAftMapped->pose.pose.position.y;
  transformAftMapped[5] = odomAftMapped->pose.pose.position.z;

  transformBefMapped[0] = odomAftMapped->twist.twist.angular.x;
  transformBefMapped[1] = odomAftMapped->twist.twist.angular.y;
  transformBefMapped[2] = odomAftMapped->twist.twist.angular.z;

  transformBefMapped[3] = odomAftMapped->twist.twist.linear.x;
  transformBefMapped[4] = odomAftMapped->twist.twist.linear.y;
  transformBefMapped[5] = odomAftMapped->twist.twist.linear.z;
}

// ed: /odom_Offset을 섭스크라이브하는 콜백함수 (not used)
void setOdomOffsetHandler(const geometry_msgs::Pose2D::ConstPtr& offset){
  in_offset = true;  
  transformoffset[0] += 0;
  transformoffset[1] += 0;
  transformoffset[2] += offset->theta;
  transformoffset[3] += offset->y; 
  transformoffset[4] -= offset->x;
  transformoffset[5] += 0;
}


int main(int argc, char** argv){
  ros::init(argc, argv, "transformMaintenance");
  ros::NodeHandle nh("~");
  nh.param<bool>("my_pose_enable", myPoseEnabled, true);

  ros::Subscriber subLaserOdometry = nh.subscribe<nav_msgs::Odometry>("/laser_odom_to_init", 5, laserOdometryHandler);
  ros::Subscriber subOdomAftMapped = nh.subscribe<nav_msgs::Odometry>("/aft_mapped_to_init", 5, odomAftMappedHandler);  //jh
  ros::Subscriber subOdomOffset = nh.subscribe<geometry_msgs::Pose2D>("/odom_Offset", 5, setOdomOffsetHandler);

  ros::Publisher pubLaserOdometry2 = nh.advertise<nav_msgs::Odometry>("/integrated_to_init", 5);

  pubLaserOdometry2Pointer = &pubLaserOdometry2;
  laserOdometry2.header.frame_id = "/camera_init";
  laserOdometry2.child_frame_id = "/dyros/base_footprint"; //jh

  ros::Publisher pubPose;
  ros::Publisher pubPose1;


  // ed: poseInitializer를 사용하는 경우 myPoseEnabled가 False가 된다
  if(myPoseEnabled) {
    ROS_INFO("Use Original 2D Pose");
    pubPose = nh.advertise<geometry_msgs::Pose2D> ("/my_pose", 5);
    pubLaserMypose = &pubPose;

    pubPose1 = nh.advertise<geometry_msgs::Pose2D> ("/test", 5);
    pubLaserMypose1 = &pubPose1;
  }
  else{
    ROS_INFO("Use Global 2D Pose with Previous Map");
  }

  tf::TransformBroadcaster tfBroadcaster2;
  tfBroadcaster2Pointer = &tfBroadcaster2;
  laserOdometryTrans2.frame_id_ = "/camera_init";
  laserOdometryTrans2.child_frame_id_ = "/dyros/base_footprint";

  ros::spin();

  return 0;
}
