/*
 * c++ ==> ROS, IMU 센서에서 데이터를 얻어와 위치, 속도, 가속도 정보를 얻어오는 코드
 */
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

using namespace std;
using namespace ros;

void getImuData(const sensor_msgs::Imu& imu){
// ROS_INFO("x : [%lf]", imu.orientation.x);
// ROS_INFO("y : [%lf]", imu.orientation.y);
// ROS_INFO("z : [%lf]", imu.orientation.z);

//ROS_INFO("orientation_cov : [%lf, %lf, %lf]",imu.orientation_covariance[0], imu.orientation_covariance[1], imu.orientation_covariance[2]);

ROS_INFO("angular vel x : [%lf]", imu.angular_velocity.x);
ROS_INFO("angular vel y : [%lf]", imu.angular_velocity.y);
ROS_INFO("angular vel z : [%lf]", imu.angular_velocity.z);

//ROS_INFO("linear acc x : [%lf]", imu.linear_acceleration.x);
//ROS_INFO("linear acc y : [%lf]", imu.linear_acceleration.y);
//ROS_INFO("linear acc z : [%lf]", imu.linear_acceleration.z);
}

int main(int argc, char **argv){
	init(argc, argv, "imu_test_node");
	NodeHandle nh;

	Subscriber imudata = nh.subscribe("imu/data", 1000, getImuData);
	spin();

	return 0;
}










