#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "sin_str0_leaderVel_exp4";

// For Block sin_str0_leaderVel_exp4/Publish for Leader Vel
SimulinkPublisher<geometry_msgs::Twist, SL_Bus_sin_str0_leaderVel_exp4_geometry_msgs_Twist> Pub_sin_str0_leaderVel_exp4_27;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

