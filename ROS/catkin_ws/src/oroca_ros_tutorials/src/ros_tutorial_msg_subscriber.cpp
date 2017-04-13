/*
 * c++ ==> ROS, ros 서브스크라이버 코드를 작성해 본 예제 코드
 */
#include <ros/ros.h>
#include "oroca_ros_tutorials/msgTutorial.h"

// 메세지 콜백함수 ros_tutorial_sub 구독자에 해당하는 메세지를 수신했을 때 작동하는 함수
void msgCallback(const oroca_ros_tutorials::msgTutorial::ConstPtr& msg){
	ROS_INFO("receive msg : %d", msg->data);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "ros_tutorial_msg_subscriber");
	ros::NodeHandle nh;

	// subscriber 선언 토픽명은 ros_tutorial_sub 이며 큐 사이즈는 100이고 msgCallback 함수를 실행한다
	ros::Subscriber ros_tutorial_sub = nh.subscribe("ros_tutorial_msg", 100, msgCallback);

	// 콜백함수 호출을 위한 함수로 메세지가 수신되면 콜백함수를 실행한다
	ros::spin();

	return 0;
}

