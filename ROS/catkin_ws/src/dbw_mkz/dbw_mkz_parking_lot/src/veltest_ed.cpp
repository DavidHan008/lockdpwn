#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <dbw_mkz_msgs/TwistCmd.h>

using namespace std;
using namespace ros;

int main(int argc, char *argv[]) {

init(argc, argv, "cmd_vel_test_ed");
NodeHandle nh;

Publisher pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/dyros/cmd_vel", 1);

Rate loop_rate(50);
geometry_msgs::Twist tw;

tw.linear.x = 15;
tw.angular.z = 0.0;



while(ok()){
pub_cmd_vel.publish(tw);

loop_rate.sleep();
}


return 0;
}
