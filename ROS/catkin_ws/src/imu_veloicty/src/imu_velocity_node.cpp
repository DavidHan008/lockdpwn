/*
 * c++ ==> ROS, IMU 
 */
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <iostream>
#include <cmath>

using namespace std;
using namespace ros;

double acceleration_x = 0;
double acceleration_xold = 0;
double velocity_x = 0;
double velocity_xold = 0;

double roll;
double pitch;

const double alpha = 0.5;
double fXg_old =0;
double Xg, Yg, Zg;
double fXg = 0;
double fYg = 0;
double fZg = 0;
double accSumVector;
double accSumVector_old = 0;
double dt = 0.01;  // 100Hz로 토픽을 전송하므로

// Subscriber 호출 함수
void getImuData(const sensor_msgs::Imu& imu){
	// ROS_INFO("x : [%lf]", imu.orientation.x);
	// ROS_INFO("y : [%lf]", imu.orientation.y);
	// ROS_INFO("z : [%lf]", imu.orientation.z);

	//ROS_INFO("orientation_cov : [%lf, %lf, %lf]",imu.orientation_covariance[0], imu.orientation_covariance[1], imu.orientation_covariance[2]);

	//ROS_INFO("angular vel x : [%lf]", imu.angular_velocity.x);
	//ROS_INFO("angular vel y : [%lf]", imu.angular_velocity.y);
	//ROS_INFO("angular vel z : [%lf]", imu.angular_velocity.z);

	//ROS_INFO("linear acc x : [%lf]", imu.linear_acceleration.x);
	//ROS_INFO("linear acc y : [%lf]", imu.linear_acceleration.y);
	//ROS_INFO("linear acc z : [%lf]", imu.linear_acceleration.z);

//	ROS_INFO("linear acc : [%5.3lf %5.3lf %5.3lf]",imu.linear_acceleration.x, imu.linear_acceleration.y , imu.linear_acceleration.z);

	// 현재 시간을 출력하는 코드 
	//Time time = Time::now();
	//ROS_INFO("%ld.%ld" ,time.sec, time.nsec);

	Xg = imu.linear_acceleration.x;
	Yg = imu.linear_acceleration.y;
	Zg = imu.linear_acceleration.z;

	fXg = Xg * alpha + (fXg * (1.0 - alpha));
	fYg = Yg * alpha + (fYg * (1.0 - alpha));
	fZg = Zg * alpha + (fZg * (1.0 - alpha));

	roll = (atan2(-fYg, fZg) * 180.0) / M_PI;
	pitch = (atan2(fXg, sqrt(fYg * fYg + fZg* fZg)) * 180.0) / M_PI;

	acceleration_x = (fXg + 9.81 * sin(pitch)) * cos(pitch);

	// acc_x,y,z의 합벡터의 크기를 구하는 코드
	accSumVector = sqrt(pow(fXg,2) + pow(fYg,2) + pow(fZg,2));

	accSumVector -= 9.65;

//velocity_x = velocity_xold + (acceleration_xold + acceleration_x)/2*dt;
	velocity_x = velocity_xold + (accSumVector_old + accSumVector)/2*dt;
	velocity_xold = velocity_x;
	accSumVector_old = accSumVector;
//acceleration_xold = acceleration_x;

	// 소수점 자리를 2자리로 고정시키는 코드
	cout << fixed;
	cout.precision(2);
	cout << "vel_x : " << velocity_x << "   [m/s], acc_x : "  << accSumVector <<  "   [m/s^2]" << endl;
}

int main(int argc, char **argv){
	init(argc, argv, "imu_velocity_node");
	NodeHandle nh;

	Subscriber imudata = nh.subscribe("imu/data", 1000, getImuData);
	spin();
	return 0;
}

