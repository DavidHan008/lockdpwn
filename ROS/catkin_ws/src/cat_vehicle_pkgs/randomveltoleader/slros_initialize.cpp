#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "randomVelToLeader";

// For Block randomVelToLeader/Publish for Leader Vel
SimulinkPublisher<geometry_msgs::Twist, SL_Bus_randomVelToLeader_geometry_msgs_Twist> Pub_randomVelToLeader_27;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

