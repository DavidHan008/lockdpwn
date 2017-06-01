#include "ros/ros.h"
#include <oroca_ros_tutorials/srvTutorial.h>
#include <cstdlib>

int main(int argc, char **argv){
	ros::init(argc, argv, "ros_tutorial_srv_client");

	if (argc != 3) {
		ROS_INFO("cmd : rosrun ros_tutorial ros_tutorial_service_client arg0 arg1");
		ROS_INFO("arg0: double number, arg1: double number");
		return 1;
	}

	ros::NodeHandle nh;

	ros::ServiceClient ros_tutorial_service_client = nh.serviceClient<oroca_ros_tutorials::srvTutorial>("ros_tutorial_srv");
	oroca_ros_tutorials::srvTutorial srv;

	srv.request.a = atoll(argv[1]);
	srv.request.b = atoll(argv[2]);

	if(ros_tutorial_service_client.call(srv)){
		ROS_INFO("send srv, srv.Request.a and b: %ld %ld", (long int)srv.request.a, (long int)srv.request.b);
		ROS_INFO("recieve srv, srv.Response.result: %ld", (long int)srv.response.result);
	}
	else{
		ROS_ERROR("Failed to call service ros_tutorial_srv");
		return 1;
	}


	return 0;
}














