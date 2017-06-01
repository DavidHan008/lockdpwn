/*
 * c++ ==> ROS, IMU 센서의 가속도값을 읽어와 평균이동필터를 적용해 차량의 실제 velocity를 구해보는 코드
 */
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <iostream>
#include <cmath>

#define MAXNUM 15  // 평균이동필터 array 길이 설정

using namespace std;
using namespace ros;

double acceleration_x = 0;
double acceleration_xold = 0;
double velocity_x = 0;
double velocity_xold = 0;

double roll;
double pitch;

int cnt = 0;

const double alpha = 0.5;
double fXg_old =0;
double Xg, Yg, Zg;
double fXg = 0;
double fYg = 0;
double fZg = 0;
double accSumVector;
double accSumVector_array[MAXNUM] = {0};
double accSumVector_filtered = 0;
double dt = 0.01;  // 100Hz로 토픽을 전송하므로

// 평균이동필터를 위해 평균을 반환하는 함수
double getMean(double acc[]){
	double sum = 0;

	for(int k = 0 ; k < MAXNUM ; k++)
		sum += acc[k];

	return sum / MAXNUM;
}

// Subscriber 호출 함수
void getImuData(const sensor_msgs::Imu& imu){
	// imu 센서로부터 선형가속도성분을 가져온다
	Xg = imu.linear_acceleration.x;
	Yg = imu.linear_acceleration.y;
	Zg = imu.linear_acceleration.z;
	 
	// 저역통과필터를 통해 한 번 데이터를 가공해준다 
	fXg = Xg * alpha + (fXg * (1.0 - alpha));
	fYg = Yg * alpha + (fYg * (1.0 - alpha));
	fZg = Zg * alpha + (fZg * (1.0 - alpha));

	// 롤과 피치값을 계산한다(사용안함)
	//roll = (atan2(-fYg, fZg) * 180.0) / M_PI;
	//pitch = (atan2(fXg, sqrt(fYg * fYg + fZg* fZg)) * 180.0) / M_PI;
	//acceleration_x = (fXg + 9.81 * sin(pitch)) * cos(pitch);

	// acc_x,y,z의 합벡터의 크기를 구하는 코드
	accSumVector = sqrt(pow(fXg,2) + pow(fYg,2) + pow(fZg,2));
	
	// 기본 중력에 의한 값인 9.65를 제거한다
	accSumVector -= 9.65;

	//velocity_x = velocity_xold +  accSumVector_filtered * dt;
	velocity_x = accSumVector_filtered * dt;
	velocity_xold = velocity_x;
	
	// 가속도에 평균이동필터를 적용한다
	accSumVector_array[cnt++] = accSumVector;
	accSumVector_filtered = getMean(accSumVector_array);
	
	if(cnt > MAXNUM)  cnt = 0;
	
	// 소수점 자리를 2자리로 고정시키는 코드
	cout << fixed;
	cout.precision(2);
	//cout << "vel_x : " << velocity_x << "   [m/s], acc_x : "  << accSumVector <<  "   [m/s^2]" << "   f_acc : " << accSumVector_filtered << "  [m/s^2]" << endl;
	cout << "vel_x : " << velocity_x << "   [m/s]" << "     " << velocity_x * 3.6 << "   [km/h]" <<  endl;
}

int main(int argc, char **argv){
	init(argc, argv, "imu_velocity_node");
	NodeHandle nh;

	Subscriber imudata = nh.subscribe("imu/data", 1000, getImuData);
	spin();
	return 0;
}

