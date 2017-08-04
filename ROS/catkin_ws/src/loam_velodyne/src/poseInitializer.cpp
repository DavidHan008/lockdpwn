#include <ros/ros.h>
#include <pcl/io/pcd_io.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/conversions.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/gicp.h>
#include <tf/tf.h>
#include <tf2/utils.h>
#include <tf/transform_broadcaster.h>

#include <eigen3/Eigen/Dense>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/PointCloud2.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>

// load before map data
// collect start map data
// gicp
// print out output data

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;


class PoseInitializer{
 public:
  // ed: PoseInitializer 생성자
  PoseInitializer() : nh_("~"), recordStart_(false), isRecordFinished_(false),
                      previousMap_(new PointCloud), currentMap_(new PointCloud),
                      currentMapFiltered_(new PointCloud), alignedMap_(new PointCloud),
                      transformedMap_ (new PointCloud) {

    nh_.param<bool>("enable_init_map", enable_init_map, false);
    nh_.param<std::string>("map_file", map_file, "init.pcd");
    nh_.param<double>("init_map_record_time", init_map_record_time, 1.0);
    nh_.param<bool>("file_debug", file_debug, false);

    loadPrevMap();

    subLaser_ = nh_.subscribe< PointCloud >("/velodyne_points", 2, &PoseInitializer::laserCloudCallback, this);
    pubPose_ = nh_.advertise<std_msgs::Float32MultiArray>("/init_pose", 1);
    pubPose2D_ = nh_.advertise<geometry_msgs::Pose2D>("/my_pose", 5);
  }

 private:  // VARIABLE
  ros::NodeHandle nh_;

  // nh.param
  bool enable_init_map;
  bool file_debug;
  double init_map_record_time;
  std::string map_file;

  ros::Subscriber subLaser_;
  ros::Subscriber subOriginalMap_;
  ros::Subscriber subOriginalOdometry_;

  ros::Publisher pubPose_;  // DEPRECATE
  ros::Publisher pubAdjustedMap_;
  ros::Publisher pubAdjustedOdometry_;
  ros::Publisher pubPose2D_;

  PointCloud::Ptr previousMap_;
  PointCloud::Ptr currentMap_;
  PointCloud::Ptr currentMapFiltered_;
  PointCloud::Ptr alignedMap_;

  Eigen::Matrix4f initTf_;
  Eigen::Matrix4f initTfInv_;

  // Repeater
  PointCloud::Ptr transformedMap_;  ///< A sum of init map and newer map
  tf::Transform initTfROS_;
  tf::TransformBroadcaster tfBroadcaster3;
  tf::StampedTransform odomTrans3_;
  nav_msgs::Odometry odomMsg_;

  geometry_msgs::Pose2D pose2DMsg_;

  // lidar record
  bool recordStart_;
  bool isRecordFinished_;
  ros::Time recordEndTime_;

  // METHOD
  void loadPrevMap() {
    int error = pcl::io::loadPCDFile(map_file, *previousMap_);

    if (error < 0)
      ROS_ERROR("PCD File load failed. \n filename = %s",map_file.c_str());
  }

  void filter() {
    ROS_INFO("Filtering Start");
    pcl::VoxelGrid<pcl::PointXYZ> downSizeFilter;
    downSizeFilter.setInputCloud(currentMap_);
    downSizeFilter.setLeafSize(0.1, 0.1, 0.1);
    downSizeFilter.filter(*currentMapFiltered_);
  }

  void match() {
    ROS_INFO("Matching Start");

    pcl::GeneralizedIterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> gicp;

    gicp.setInputSource(currentMapFiltered_);
    gicp.setInputTarget(previousMap_);
    //gicp.setInputSource(previousMap_);
    //gicp.setInputTarget(currentMapFiltered_);
    gicp.align(*alignedMap_);

    std::cout << "has converged:" << gicp.hasConverged() << " score: " << gicp.getFitnessScore() << std::endl;

    initTf_ = gicp.getFinalTransformation();

    std::cout << initTf_ << std::endl;

    initTfROS_.setBasis(tf::Matrix3x3(initTf_(0,0), initTf_(0,1), initTf_(0,2),
                                      initTf_(1,0), initTf_(1,1), initTf_(1,2),
                                      initTf_(2,0), initTf_(2,1), initTf_(2,2)));
    initTfROS_.setOrigin(tf::Vector3(initTf_(0,3), initTf_(1,3), initTf_(3,3)));

    Eigen::Matrix3f mRot;
    Eigen::Vector3f vOri;
    mRot = initTf_.block<3,3>(0,0);
    vOri = initTf_.col(3).head<3>();
    Eigen::Matrix3f mRotT = mRot.transpose();
    Eigen::Vector3f vOriInv =  -mRotT * vOri;
    initTfInv_.topLeftCorner(3,3) = mRotT;
    initTfInv_.col(3).head(3) = vOriInv;
    initTfInv_(3,0) = 0;
    initTfInv_(3,1) = 0;
    initTfInv_(3,2) = 0;
    initTfInv_(3,3) = 1;

    if (file_debug) {
      pcl::io::savePCDFile("source.pcd",*previousMap_);
      pcl::io::savePCDFile("target.pcd",*currentMapFiltered_);
      pcl::io::savePCDFile("aligned.pcd",*alignedMap_);
    }
    /*
      tf::Matrix3x3 tfMat(eigTfMat(0,0), eigTfMat(0,1), eigTfMat(0,2),
      eigTfMat(1,0), eigTfMat(1,1), eigTfMat(1,2),
      eigTfMat(2,0), eigTfMat(2,1), eigTfMat(2,2));

      Eigen::Vector3d ypr;
      tfMat.getEulerYPR(ypr(0),ypr(1),ypr(2));
      ROS_INFO("Matrix T' = %lf \t%lf \t%lf \t%lf \t%lf \t %lf",
      eigTfMat(0,3),eigTfMat(1,3),eigTfMat(2,3),
      ypr(2),ypr(1),ypr(0));

      std_msgs::Float32MultiArray msg;
      msg.data.push_back(eigTfMat(0,3));
      msg.data.push_back(eigTfMat(1,3));
      msg.data.push_back(eigTfMat(2,3));
      msg.data.push_back(ypr(2));
      msg.data.push_back(ypr(1));
      msg.data.push_back(ypr(0));

      pubPose_.publish(msg);
    */
  }

  void initMessageHandlerStart() {
    odomMsg_.header.frame_id = "/camera_init_global";
    odomMsg_.child_frame_id = "/camera";
    odomTrans3_.frame_id_ = "/camera_init_global";
    odomTrans3_.child_frame_id_ = "/camera";

    pubAdjustedOdometry_ = nh_.advertise<nav_msgs::Odometry>("/cam_to_global_init", 5);
    pubAdjustedMap_ = nh_.advertise< PointCloud >("/laser_cloud_surround_with_init", 1);
    subOriginalMap_ = nh_.subscribe< PointCloud >("/laser_cloud_surround", 1, &PoseInitializer::mapCallback, this);
    subOriginalOdometry_ = nh_.subscribe("/integrated_to_init", 5, &PoseInitializer::odometryCallback, this);

  }



 private:  // CALLBACK

  // ed: /velodyne_points를 섭스크라이브하는 콜백함수
  void laserCloudCallback(const PointCloud::ConstPtr& msg)  {
    if(!recordStart_) {
      ROS_INFO("Recording starts.");
      recordStart_ = true;
      ros::Duration recordDuration(init_map_record_time);
      recordEndTime_ = ros::Time::now() + recordDuration;
    }

    if(isRecordFinished_)
      return;

    *currentMap_ = *currentMap_ + *msg;

    if(ros::Time::now() >= recordEndTime_) {
      // finish
      isRecordFinished_ = true;
      // Do a conversion
      ROS_INFO("Recording is done.");
      filter();
      match();
      initMessageHandlerStart();
      subLaser_.shutdown();

    }
  }

  // ed: /laser_cloud_surround를 섭스크라이브하는 콜백함수
  void mapCallback(const PointCloud::ConstPtr& msg) {
    PointCloud totalPoint;
    PointCloud::Ptr transformedPoint (new PointCloud);

    transformedPoint->header.frame_id = "/camera_init_global";

    //pcl::transformPointCloud(*msg,*transformedPoint, initTf_);
    pcl::transformPointCloud(*msg, *transformedPoint, initTf_);

    totalPoint = *transformedPoint + *previousMap_;
    totalPoint.header.frame_id = "/camera_init_global";
    //totalPoint = *transformedPoint + *previousMap_;

    pubAdjustedMap_.publish(totalPoint);
  }


  // ed: /integrated_to_init을 섭스크라이브하는 콜백함수
  void odometryCallback(const nav_msgs::Odometry::ConstPtr& msg)  {
    tf::Transform g;
    tf::Transform h;

    g = initTfROS_;

    h.setRotation(tf::Quaternion(msg->pose.pose.orientation.x,
                                 msg->pose.pose.orientation.y,
                                 msg->pose.pose.orientation.z,
                                 msg->pose.pose.orientation.w));
    h.setOrigin(tf::Vector3(msg->pose.pose.position.x,
                            msg->pose.pose.position.y,
                            msg->pose.pose.position.z));
    tf::Transform gh;
    gh = g * h;

    odomMsg_.header.stamp = msg->header.stamp;
    odomMsg_.pose.pose.orientation.x = gh.getRotation().getX();
    odomMsg_.pose.pose.orientation.y = gh.getRotation().getY();
    odomMsg_.pose.pose.orientation.z = gh.getRotation().getZ();
    odomMsg_.pose.pose.orientation.w = gh.getRotation().getW();

    odomMsg_.pose.pose.position.x = gh.getOrigin().m_floats[0];
    odomMsg_.pose.pose.position.y = gh.getOrigin().m_floats[1];
    odomMsg_.pose.pose.position.z = gh.getOrigin().m_floats[2];
    pubAdjustedOdometry_.publish(odomMsg_);

    odomTrans3_.stamp_ = msg->header.stamp;
    odomTrans3_.setBasis(gh.getBasis());
    odomTrans3_.setOrigin(gh.getOrigin());
    tfBroadcaster3.sendTransform(odomTrans3_);


    /*********** sh X jh **********************************/
    double yaw, pitch, roll;
    gh.getBasis().getEulerYPR(yaw,pitch,roll);


    // ed: 코드를 원래대로 수정했다
    // pose2DMsg_.x = -odomMsg_.pose.pose.position.y;
    // pose2DMsg_.y = odomMsg_.pose.pose.position.x;
    pose2DMsg_.x = odomMsg_.pose.pose.position.x;
    pose2DMsg_.y = odomMsg_.pose.pose.position.y;
    pose2DMsg_.theta = yaw;  //Mypose.theta = tf::getYaw(geoQuat);

<<<<<<< HEAD
    if(yaw<0) {
=======
    if(yaw<0)
>>>>>>> 229670762023e3db3a0715b11baf6e4c9341fe24
      pose2DMsg_.theta += 2.0 * M_PI;
    else {
      //Mypose.theta += 0.5 * PI;
    }

    pubPose2D_.publish(pose2DMsg_);

    //printf("%f %f \n",Mypose.x, Mypose.y);

  }
};


int main(int argc, char** argv){
  ros::init(argc, argv, "poseInitializer");

  PoseInitializer pi;
  ros::spin();

  return 0;
}
