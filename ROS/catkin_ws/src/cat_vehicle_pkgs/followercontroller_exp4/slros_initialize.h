#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block followerController_exp4/Follower's positions
extern SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_followerController_exp4_nav_msgs_Odometry> Sub_followerController_exp4_43;

// For Block followerController_exp4/Leader's Position
extern SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_followerController_exp4_nav_msgs_Odometry> Sub_followerController_exp4_40;

// For Block followerController_exp4/Leader's Velocity
extern SimulinkSubscriber<geometry_msgs::Twist, SL_Bus_followerController_exp4_geometry_msgs_Twist> Sub_followerController_exp4_38;

// For Block followerController_exp4/Publish for follower vel
extern SimulinkPublisher<geometry_msgs::Twist, SL_Bus_followerController_exp4_geometry_msgs_Twist> Pub_followerController_exp4_21;

// For Block followerController_exp4/Publish for headway distance experienced by follower
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_followerController_exp4_std_msgs_Float64> Pub_followerController_exp4_61;

void slros_node_init(int argc, char** argv);

#endif
