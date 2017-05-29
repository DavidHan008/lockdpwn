/*
 * c++ ==> ROS, IMU 센서
 */
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Float64.h>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
using namespace ros;

const double alpha = 0.5;
double fXg_old =0;
double Xg, Yg, Zg;
double aX, aY, aZ;
double accSumVector;
double fXg = 0;
double fYg = 0;
double fZg = 0;
double faX = 0;
double faY = 0;
double faZ = 0;

void getImuData(const sensor_msgs::Imu& imu){
	// ROS_INFO("x : [%lf]", imu.orientation.x);
	// ROS_INFO("y : [%lf]", imu.orientation.y);
	// ROS_INFO("z : [%lf]", imu.orientation.z);

	//ROS_INFO("orientation_cov : [%lf, %lf, %lf]",imu.orientation_covariance[0], imu.orientation_covariance[1], imu.orientation_covariance[2]);

//	ROS_INFO("angular vel x : [%lf]", imu.angular_velocity.x);
//	ROS_INFO("angular vel y : [%lf]", imu.angular_velocity.y);
//	ROS_INFO("angular vel z : [%lf]", imu.angular_velocity.z);

	//ROS_INFO("linear acc x : [%lf]", imu.linear_acceleration.x);
	//ROS_INFO("linear acc y : [%lf]", imu.linear_acceleration.y);
	//ROS_INFO("linear acc z : [%lf]", imu.linear_acceleration.z);

	// 현재 시간을 출력하는 코드 
	//Time time = Time::now();
	//ROS_INFO("%ld.%ld" ,time.sec, time.nsec);
	
	aX = imu.angular_velocity.x;
	aY = imu.angular_velocity.y;
	aZ = imu.angular_velocity.z;

	faX = aX * alpha + (faX * (1.0 - alpha));
	faY = aY * alpha + (faY * (1.0 - alpha));
	faZ = aZ * alpha + (faZ * (1.0 - alpha));

//	Xg = imu.linear_acceleration.x;
//	Yg = imu.linear_acceleration.y;
//	Zg = imu.linear_acceleration.z;

//	fXg = Xg * alpha + (fXg * (1.0 - alpha));
//	fYg = Yg * alpha + (fYg * (1.0 - alpha));
//	fZg = Zg * alpha + (fZg * (1.0 - alpha));

//	accSumVector = sqrt(pow(fXg,2) + pow(fYg,2) + pow(fZg,2));

	// 소수점 자리를 2자리수로 고정시킨다
	cout << fixed;
	cout.precision(2);
	cout << "ang vel : [" << faX << " " << faY << " " << faZ << "] " << endl;
}

void getYawData(const std_msgs::Float64 yaw){
	cout << "                                      Yaw : " << yaw.data << endl;
}


int main(int argc, char **argv){
	init(argc, argv, "imu_test_node");
	NodeHandle nh;

	Subscriber imudata = nh.subscribe("imu/data", 1, getImuData);
	Subscriber imuYaw = nh.subscribe("imu/yaw_ed", 1, getYawData);

	spin();
	return 0;
}

