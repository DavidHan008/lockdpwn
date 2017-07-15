#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "sinVelToLeader";

// For Block sinVelToLeader/Publish for Leader Vel
SimulinkPublisher<geometry_msgs::Twist, SL_Bus_sinVelToLeader_geometry_msgs_Twist> Pub_sinVelToLeader_27;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

