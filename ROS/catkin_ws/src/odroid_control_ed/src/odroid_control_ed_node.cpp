/*
 * c++ ==> ROS, 
 *								
 */
#include <iostream>
#include <string>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include "pid.h"

#define TARGET_VAL 1530
#define ARRAYNUM 5

using namespace std;
using namespace ros;

int cnt = 0;

double ult = 0;

double P = 13;
double I = 3;
double D = 1;

double P2 = 50;
double I2 = 25;
double D2 = 0;

double v_x = 0;
double Ww_Reff = 0;
double slip_ratio = 0;
double err = 0;
double u = 0;
double uu[ARRAYNUM] = {0};
double dt = 100;
double threshold = 0;
double desired_slip_ratio = 0.04;

double err_angvel_z = 0;
double v = 0;
double vfinal = 0;
double vv[ARRAYNUM] = {0};

double aZ;
double faZ;
double alpha = 0.5;

// servo & dc 모터 퍼블리셔에 전달할 변수 선언
std_msgs::Int32 servo;
std_msgs::Int32 dc_motor;

int mappingDCMotor(int a){
	if(a == 6) return 10;

	else if (a == 7) return 20;

	else if (a > 7 && a < 11) return 35;

	else if (a == 12) return 50;

	else if( a > 12) return 60;
}

// 배열을 받아 배열 안에 있는 모든 수의 평균을 반환하는 함수
double getMean(double dist[]) {
  double sum = 0;
  for(int k = 0 ; k < ARRAYNUM ; k++)
  {
    sum += dist[k];
  }

  return sum / ARRAYNUM;
}

// 아두이노로부터 초음파센서 값을 Subscribe하는 함수
void ultra_dist(const std_msgs::Float32& ultra){
	ult = ultra.data;
}

// FR 홀센서 값을 받아 처리하는 콜백함수
void hall_front(const std_msgs::Float32& h_front){
	//cout << "                hall_front is : " << h_front.data << endl;
	
	v_x = mappingDCMotor(h_front.data);
}

// RR 홀센서 값을 받아 처리하는 콜백함수 
void hall_rear(const std_msgs::Float32& h_rear){
	//cout << "                                   hall_rear is : " << h_rear.data << endl;

	Ww_Reff = mappingDCMotor(h_rear.data);
}

void getAngleVel_z(const sensor_msgs::Imu& imu){
	aZ = imu.angular_velocity.z;
	faZ = aZ * alpha + (faZ * (1.0 - alpha));
	
//	Yaw = imu.yaw;
//	fYaw = Yaw * alpha + (fYaw * (1.0 - alpha));
}


int main(int argc, char **argv){
	init(argc, argv, "odroid_control_ed_node");
	NodeHandle nh;

	// servo & motor 값을 처리하는 퍼블리셔 선언
	Publisher servo_pub = nh.advertise<std_msgs::Int32>("angle_msg", 1);
	Publisher motor_pub = nh.advertise<std_msgs::Int32>("motor_speed", 1);
	Rate loop_rate(10);  // 10 Hz

	// 초음파 & 홀센서 2개 값을 처리하는 섭스크라이버 선언
	Subscriber ultra_sub = nh.subscribe("dist", 1, ultra_dist);
	Subscriber hall_front_sub = nh.subscribe("Rps_front", 1, hall_front);
	Subscriber hall_rear_sub = nh.subscribe("Rps_rear", 1, hall_rear);

	Subscriber imudata = nh.subscribe("imu/data", 1, getAngleVel_z);

	PID pid_dcmotor(P , I , D);
	PID pid_yawrate(P2, I2, D2);

	while(ok()){

		if(Ww_Reff == 0)
			slip_ratio = 0;
		else
			slip_ratio = (Ww_Reff - v_x) / Ww_Reff;

		err = slip_ratio - desired_slip_ratio;
		u = pid_dcmotor.update(err, dt);

		err_angvel_z = -faZ;
		//err_angvel_z = fYaw;

		v = 65 + pid_yawrate.update(err_angvel_z, dt);
		
		vv[cnt++] = v;
		vfinal = getMean(vv);

		if(cnt > ARRAYNUM) cnt = 0;

		//cout << "slip is :  " << slip_ratio << ", WwReff is :  " << Ww_Reff << " , v_x is : " << v_x;
		//cout << ", err1 is : [ "<< err  << " ] u is : [ " << u << " ], v is [ " << v << " ]" << endl;

		if(u > 70) u = 70;

		dc_motor.data = TARGET_VAL + u;
		//servo.data = vfinal;
		servo.data = 65;
		servo.data = vfinal;
		
		//cout << servo << ",  " << dc_motor << endl;

		cout << ult << endl;

		servo_pub.publish(servo);		
		motor_pub.publish(dc_motor);		

		loop_rate.sleep();
		spinOnce();
	}
	return 0;
}

