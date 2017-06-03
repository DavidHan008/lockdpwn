/*
 * c++ ==> ROS, 캡스톤프로젝트 정상원주행용 코드
 * 				1520의 속도 76도의 각도로 정상원주행을 하고
 *				30번 루프 후 firstValue = faZ 저장
 *				40번 루프 후 속도 1505로 감속
 *				초음파센서 인지해서 벽 만나면 정지
 */
#include <iostream>
#include <string>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include "pid.h"

#define TARGET_VAL 1520
#define TARGET_ANGLE 76
#define ARRAYNUM 15
#define ARRAYNUM2 15

using namespace std;
using namespace ros;

int cnt = 0;
int cnt2 = 0;

int startFlag = 0;

double ult = 0;

double P = 0;
double I = 0;
double D = 0;

double P2 = 5;
double I2 = .5;
double D2 = .5;

double v_x = 0;
double Ww_Reff = 0;
double slip_ratio = 0;
double err = 0;
double u = 0;
double uu[ARRAYNUM] = {0};
double dt = 100;
double threshold = 0;
double desired_slip_ratio = 0.0;

double err_angvel_z = 0;
double v = 0;
double vfinal = 0;
double vv[ARRAYNUM] = {0};

double ww[ARRAYNUM2] = {0};
double wfinal = 0;

double aZ;
double faZ;
double alpha = 0.5;

double Yaw;
double fYaw;

double firstValue = 0;
int counter = 0;
int target_val_final = TARGET_VAL;

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

	if(ult > 100) ult = 100;

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

	if(startFlag > 5)
		counter++;
	if(counter == 30) firstValue = faZ;
}

void getYaw(const std_msgs::Float64 yaw){
	Yaw = yaw.data;

	fYaw = Yaw * alpha + (fYaw * (1.0 - alpha));
}

int main(int argc, char **argv){
	init(argc, argv, "odroid_control_cornering_ed_node");
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
	//Subscriber imudata = nh.subscribe("imu/yaw_ed", 1, getYaw);

	PID pid_dcmotor(P , I , D);
	PID pid_yawrate(P2, I2, D2);

	while(ok()){
		// slip ratio 계산
		if(Ww_Reff == 0)
			slip_ratio = 0;
		else
			slip_ratio = (Ww_Reff - v_x) / Ww_Reff;

		// DC Motor 에러값 설정
		err = slip_ratio - desired_slip_ratio;

		// DC Motor PID 값 계산
		u = pid_dcmotor.update(err, dt);

		// Servo Motor 에러값 설정
		faZ -= firstValue / 2;

		if(firstValue != 0)
			err_angvel_z = faZ;
		else
			err_angvel_z = 0;
	
		// Servo Motor PId 값 계산
		v =  pid_yawrate.update(err_angvel_z, dt);
		
		if(v > 20) v = 20;
		else if(v < -20) v = -20;

		// 평균이동필터로 서보모터 각도값 보정
		vv[cnt++] = -v;
		vfinal = getMean(vv);

		if(cnt > ARRAYNUM) cnt = 0;

		cout << "slip is :  " << slip_ratio << ", WwReff is :  " << Ww_Reff << " , v_x is : " << v_x;
		cout << ", err1 is : [ "<< err  << " ] u is : [ " << u << " ], v is [ " << v << " ]" << endl;

		// 모터의 최고 속도 고정
		if(u > 70) u = 70;

		dc_motor.data = target_val_final + u;
	
		// 40번 루프 후 모터 속도를 1505로 감속합니다
		if(counter > 40) 
			if(target_val_final > 1506)
					target_val_final -= 2;

		if(vfinal > 20) vfinal = 20;
		if(vfinal < -20) vfinal = -20;

		servo.data = TARGET_ANGLE + vfinal;
	
		// 초음파센서를 평균이동필터로 보정합니다
		ww[cnt2++] = ult;
		wfinal = getMean(ww);

		// 초음파센서에 물체가 감지되면 1503 모터 정지
		if(wfinal > 5 && wfinal < 90 && startFlag > 5) dc_motor.data -= 3;
	 if(wfinal > 5 && wfinal < 90 && startFlag < 5) dc_motor.data = 1504;

		if(wfinal > 50)
			startFlag++;

		if(cnt2 > ARRAYNUM2) cnt2 = 0;

		servo_pub.publish(servo);		
		motor_pub.publish(dc_motor);		

		cout << servo << ",  " << dc_motor << endl;
		cout << "faZ is : " << faZ <<", fYaw is : "<< fYaw  << ", and firstValue is : " << firstValue << endl;
		cout << wfinal << endl;
		cout <<"startFlag is : "<< startFlag << endl;

		loop_rate.sleep();
		spinOnce();
	}
	return 0;
}

