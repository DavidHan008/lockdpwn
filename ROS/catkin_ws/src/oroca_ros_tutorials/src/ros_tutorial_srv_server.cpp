/*
 * c++ ==> ROS, rosrun을 사용해 서버를 구동시키고
 * 				rosparam, rosservice 명령어로 사칙연산을 간단하게 해보는 코드 
 *
 *			    $ rosrun oroca_ros_tutorials ros_tutorial_service_server
 *				$ rosparam set /calculation_method 3 
 *				$ rosservice call /ros_tutorial_srv 10 5 
 */
#include <ros/ros.h>
#include <oroca_ros_tutorials/srvTutorial.h>

#define PLUS 1
#define MINUS 2
#define MULTIPLICATION 3
#define DIVISION 4

int g_operator = PLUS;

// 서비스 요청이 있을 경우 아래 코드를 실행한다
// 서비스 요청은 req, 응답은 res로 설정했다
bool calculation(oroca_ros_tutorials::srvTutorial::Request &req, oroca_ros_tutorials::srvTutorial::Response &res){

	// 서비스 요청 시 받은 a와 b값을 g_operator에 따라 다르게 연산하는 코드  
	switch(g_operator){
		case PLUS:
			res.result = req.a + req.b; 
			break;
		case MINUS:
			res.result = req.a - req.b; 
			break;
		case MULTIPLICATION:
			res.result = req.a * req.b; 
			break;
		case DIVISION:
			if(req.b == 0){
				res.result = 0;
				break;
			}
			else{
				res.result = req.a / req.b; 
				break;
			}
	}

	// 서비스 요청에 사용된 a,b 값의 표시 및 서비스 응답에 해당되는 result 값을 출력한다
	ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
	ROS_INFO("sending back response: [%ld]", (long int)res.result);

	return true;
}

int main(int argc,  char **argv){
	ros::init(argc, argv, "ros_tutorial_srv_server"); // 노드명 초기화
	ros::NodeHandle nh;
	// 매개변수 초기설정
	nh.setParam("calculation_method", PLUS); 

	ros::ServiceServer ros_tutorial_service_server =
		nh.advertiseService("ros_tutorial_srv", calculation);

	ROS_INFO("ready srv server!");
	ros::Rate r(10); // 10hz 

	while(1){
		// 연산자를 매개변수로부터 받은 값으로 변경한다.
		nh.getParam("calculation_method", g_operator);
		// 콜백함수 처리루틴
		ros::spinOnce();
		// 루틴 반복을 위한 sleep 처리
		r.sleep();
	}
	return 0;
}


