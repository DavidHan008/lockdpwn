/*
 * c++ ==> ROS, IMU 센서에서 데이터를 얻어와 위치, 속도, 가속도 정보를 얻어오는 코드
 */
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
using namespace ros;

<<<<<<< HEAD
const double alpha = 0.5;
double fXg_old =0;
double Xg, Yg, Zg;
double accSumVector;
double fXg = 0;
double fYg = 0;
double fZg = 0;

void getImuData(const sensor_msgs::Imu& imu){
	// ROS_INFO("x : [%lf]", imu.orientation.x);
	// ROS_INFO("y : [%lf]", imu.orientation.y);
	// ROS_INFO("z : [%lf]", imu.orientation.z);

	//ROS_INFO("orientation_cov : [%lf, %lf, %lf]",imu.orientation_covariance[0], imu.orientation_covariance[1], imu.orientation_covariance[2]);

	//ROS_INFO("angular vel x : [%lf]", imu.angular_velocity.x);
	//ROS_INFO("angular vel y : [%lf]", imu.angular_velocity.y);
	//ROS_INFO("angular vel z : [%lf]", imu.angular_velocity.z);
=======
// IMU 센서에서 데이터를 서브스크리브 하는 함수
void getImuData(const sensor_msgs::Imu& imu){
	// ROS_INFO("x : [%lf]", imu.orientation.x);
	// ROS_INFO("y : [%lf]", imu.orientation.y);
	// ROS_INFO("z : [%lf]", imu.orientation.z);

	//ROS_INFO("orientation_cov : [%lf, %lf, %lf]",imu.orientation_covariance[0], imu.orientation_covariance[1], imu.orientation_covariance[2]);

	ROS_INFO("angular vel x : [%lf]", imu.angular_velocity.x);
	ROS_INFO("angular vel y : [%lf]", imu.angular_velocity.y);
	ROS_INFO("angular vel z : [%lf]", imu.angular_velocity.z);
>>>>>>> 66322ec3bea54a0e38d73c43d964b026548dbb59

	//ROS_INFO("linear acc x : [%lf]", imu.linear_acceleration.x);
	//ROS_INFO("linear acc y : [%lf]", imu.linear_acceleration.y);
	//ROS_INFO("linear acc z : [%lf]", imu.linear_acceleration.z);
<<<<<<< HEAD

	// 현재 시간을 출력하는 코드 
	//Time time = Time::now();
	//ROS_INFO("%ld.%ld" ,time.sec, time.nsec);
	
	Xg = imu.linear_acceleration.x;
	Yg = imu.linear_acceleration.y;
	Zg = imu.linear_acceleration.z;

	fXg = Xg * alpha + (fXg * (1.0 - alpha));
	fYg = Yg * alpha + (fYg * (1.0 - alpha));
	fZg = Zg * alpha + (fZg * (1.0 - alpha));
	
	accSumVector = sqrt(pow(fXg,2) + pow(fYg,2) + pow(fZg,2));

	// 소수점 자리를 2자리수로 고정시킨다
	cout << fixed;
	cout.precision(2);
	cout << "linear acc : [" << fXg << " " << fYg << " " << fZg << "], accSumVector : [ "  << accSumVector << " ]" <<endl;
=======
>>>>>>> 66322ec3bea54a0e38d73c43d964b026548dbb59
}

int main(int argc, char **argv){
	init(argc, argv, "imu_test_node");
	NodeHandle nh;

	Subscriber imudata = nh.subscribe("imu/data", 1000, getImuData);
	spin();
	return 0;
}

