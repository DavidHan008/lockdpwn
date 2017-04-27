#include <ros/ros.h>
#include <oroca_ros_tutorials/srvTutorial.h>

// 서비스 요청이 있을 경우 아래 코드를 실행한다
// 서비스 요청은 req, 응답은 res로 설정했다
bool calculation(oroca_ros_tutorials::srvTutorial::Request &req, oroca_ros_tutorials::srvTutorial::Response &res){
	// 서비스 요청 시 받은 a와 b값을 더하여 서비스 응답값에 저장한다
	res.result = req.a + req.b;
	
	// 서비스 요청에 사용된 a,b 값의 표시 및 서비스 응답에 해당되는 result 값을 출력한다
	ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
	ROS_INFO("sending back response: [%ld]", (long int)res.result;

	return true;
}

int main(int argc, const char *argv[])
{
	ros::init(argc, argv, "ros_tutorial_srv_server"); // 노드명 초기화
	ros::NodeHandle nh;

	ros::ServiceServer ros_tutorial_service_server =
		nh.advertiseService("ros_tutorial_srv", calculation);
	
	ROS_INFO("ready srv server!");
	ros::spin(); // 서비스 요청 대기

	return 0;
}








