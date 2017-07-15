#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block humanCarFollowerController/Follower's positions
extern SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_humanCarFollowerController_nav_msgs_Odometry> Sub_humanCarFollowerController_43;

// For Block humanCarFollowerController/Leader's Position
extern SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_humanCarFollowerController_nav_msgs_Odometry> Sub_humanCarFollowerController_40;

// For Block humanCarFollowerController/Leader's Velocity
extern SimulinkSubscriber<geometry_msgs::Twist, SL_Bus_humanCarFollowerController_geometry_msgs_Twist> Sub_humanCarFollowerController_38;

// For Block humanCarFollowerController/Publish for follower vel
extern SimulinkPublisher<geometry_msgs::Twist, SL_Bus_humanCarFollowerController_geometry_msgs_Twist> Pub_humanCarFollowerController_21;

void slros_node_init(int argc, char** argv);

#endif
