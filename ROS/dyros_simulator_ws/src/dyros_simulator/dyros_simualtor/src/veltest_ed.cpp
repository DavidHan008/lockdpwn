/*
  c++ ==> ROS, mkz차량이 가제보상에서 움직이는지 cmd_vel등 여러 토픽을 사용해 테스트해 본 코드
 */
#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <dbw_mkz_msgs/TwistCmd.h>
#include <dbw_mkz_msgs/GearCmd.h>

using namespace std;
using namespace ros;

int main(int argc, char *argv[]) {
  init(argc, argv, "cmd_vel_test_ed");
  NodeHandle nh;

  Publisher pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/dyros/cmd_vel", 1);
  Publisher pub_gear_cmd = nh.advertise<dbw_mkz_msgs::GearCmd>("/dyros/gear_cmd", 1);

  Rate loop_rate(50);
  geometry_msgs::Twist tw;
  dbw_mkz_msgs::GearCmd gc;

  tw.linear.x = 2;
  tw.angular.z = 0.0;
  gc.cmd.gear = 2;


  while(ok()){
    pub_cmd_vel.publish(tw);
    pub_gear_cmd.publish(gc);

    loop_rate.sleep();
  }


  return 0;
}
