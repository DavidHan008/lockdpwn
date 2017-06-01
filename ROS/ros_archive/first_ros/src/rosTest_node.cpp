/*
  c++ ==> ROS, ros를 처음으로 사용해본 예제 코드
               hello world 를 계속 반복한다
               $ rospack profile
               $ catkin_make
               $ source devel/setup.bash
               $ rosrun my_first_ros_pkg rosTest_node
*/
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

using namespace std;
using namespace ros;

int main(int argc, char *argv[]){
  init(argc, argv, "rosTest_node");
  NodeHandle nh;
  Publisher chatter_pub = nh.advertise<std_msgs::String>("say_hello_world", 1000);

  Rate loop_rate(10);
  int count = 0;

  while(ok()){
    std_msgs::String msg;
    stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    spinOnce();
    loop_rate.sleep();
    ++count;
  }

  return 0;
}
