/*
 * c++ ==> ROS, 아두이노와 오드로이드를 ROS로 연동해본 코드
 * 				아두이노에서 초음파센서 값을 읽어서 오드로이돌 보내주고
 * 				이를 오드로이드에서 다시 아두이노 서보모터에 값으로 전달해 
 * 				서보모터를 조정하는 코드
 */
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>

using namespace std;
using namespace ros;

// 서보모터 값을 퍼블리시해줄 전역변수 설정
std_msgs::Int32 servo;

// 아두이노로부터 초음파센서 값을 Subscribe하는 함수
void ultraData(const std_msgs::Int32& ultra){

	// 값을 출력하면서 servo.data에 각도 값을 저장한다
	ROS_INFO("Ultra Data is : [%d]", ultra.data);
	servo.data = ultra.data;
	if(ultra.data > 175) 
		servo.data = 175;
}

int main(int argc, char **argv){
	init(argc, argv, "arduino_test_subscriber_node");
	NodeHandle nh;

	// 서보모터값을 아두이노에 전달하는 퍼블리셔 선언
	Publisher servo_pub = nh.advertise<std_msgs::Int32>("setServoData", 1000);
	Rate loop_rate(10);  // 10 Hz

	// 초음파센서 값을 받는 서브스크라이버 선언
	Subscriber ultra_pub = nh.subscribe("getUltrasonicData", 1000, ultraData);
	spinOnce();


	while(ok()){
		// 무한루프를 돌면서 servo 변수의 값을 서보모터로 퍼블리시한다
		servo_pub.publish(servo);		
		loop_rate.sleep();
		spinOnce();
	}
	return 0;
}

