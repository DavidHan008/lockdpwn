#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "constantVelToLeader";

// For Block constantVelToLeader/Publish for Leader Vel
SimulinkPublisher<geometry_msgs::Twist, SL_Bus_constantVelToLeader_geometry_msgs_Twist> Pub_constantVelToLeader_27;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

