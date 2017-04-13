/*
 * c++ ==> ROS, ros 퍼블리셔 코드를 작성해 send msg = %d를 계속 출력하는 코드
 */
#include <ros/ros.h>
#include "oroca_ros_tutorials/msgTutorial.h"

int main(int argc,char **argv)
{
	// 노드명 초기화
	ros::init(argc, argv, "ros_tutorial_msg_publisher");
	// ROS 시스템과 통신을 위한 핸들러 초기화
	ros::NodeHandle nh;

	// 퍼블리셔 선언 msgTutorial을 이용한 ros_tutorial_pub를 작성한다. 토픽명은 ros_tutorial_msg 이며 퍼블리셔의 큐 사이즈는 100개로 설정한다 
	ros::Publisher ros_tutorial_pub = nh.advertise<oroca_ros_tutorials::msgTutorial>("ros_tutorial_msg", 100);

	// 루프 주기를 설정한다 0.1초 간격으로 실행된다
	ros::Rate loop_rate(10);

	int count = 0;

	while(ros::ok()){
		// msgTutorial이라는 파일형식으로 msg 선언
		oroca_ros_tutorials::msgTutorial msg;
		// 메세지 값을 카운터 값으로 정한다
		msg.data = count;
		// printf처럼 특정 구문을 출력한다
		ROS_INFO("send msg = %d", count);
		// 메세지를 발행한다 (0.1초 간격)
		ros_tutorial_pub.publish(msg);
		loop_rate.sleep();
		++count;
	}
	return 0;
}

