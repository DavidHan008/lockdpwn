#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>

using namespace std;
using namespace ros;

std_msgs::Int32 servo;

void ultraData(const std_msgs::Int32& ultra){
	ROS_INFO("Ultra Data is : [%d]", ultra.data);

	servo.data = ultra.data;
	if(ultra.data > 175) 
		servo.data = 175;
}

int main(int argc, char **argv){
	init(argc, argv, "arduino_test_subscriber_node");
	NodeHandle nh;

	Publisher servo_pub = nh.advertise<std_msgs::Int32>("setServoData", 1000);
//	spinOnce();
	Rate loop_rate(10);

	Subscriber ultra_pub = nh.subscribe("getUltrasonicData", 1000, ultraData);
	spinOnce();

	while(ok()){
		servo_pub.publish(servo);		
		loop_rate.sleep();
		spinOnce();
	}
	return 0;
}

