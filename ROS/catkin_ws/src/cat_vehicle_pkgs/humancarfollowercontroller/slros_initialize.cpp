#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "humanCarFollowerController";

// For Block humanCarFollowerController/Follower's positions
SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_humanCarFollowerController_nav_msgs_Odometry> Sub_humanCarFollowerController_43;

// For Block humanCarFollowerController/Leader's Position
SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_humanCarFollowerController_nav_msgs_Odometry> Sub_humanCarFollowerController_40;

// For Block humanCarFollowerController/Leader's Velocity
SimulinkSubscriber<geometry_msgs::Twist, SL_Bus_humanCarFollowerController_geometry_msgs_Twist> Sub_humanCarFollowerController_38;

// For Block humanCarFollowerController/Publish for follower vel
SimulinkPublisher<geometry_msgs::Twist, SL_Bus_humanCarFollowerController_geometry_msgs_Twist> Pub_humanCarFollowerController_21;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

