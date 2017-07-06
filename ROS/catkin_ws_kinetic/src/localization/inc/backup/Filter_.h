#pragma once

#include "mm.h"
#include "attitude.h"
#include "posvel.h"

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "Filter_IMU.h"

using namespace std;


struct sIMU
{
	double t;		
	double gyro[3];		
	double accl[3];		
	double magnet[3];
	double obdVel;
};

class Filter
{
public:
	Filter();
	~Filter();

	void DoGPS();
	void DoIMU(double dt);

	//sGPS m_gps;
	double m_tm_x, m_tm_y, m_tm_z, m_theta; // velodyne
	
	double m_ha[3];		//radianŽÜÀ§, _ha[2]°¡ N±Ø ±âÁØ heading angle		 //130312 Lk
	
	// Attitude, Velocity, Position Kalman FilterÀÇ »óÅÂº¯Œöµé

	double m_v[3];		// Velocity: vx, vy, vz
	double m_p[3];		// Position: px-ºÏÂÊ, py-Œ­ÂÊ, pz-ÇÏŽÃ

	
	// Attitude, Velocity, Position Kalman FilterÀÇ °øºÐ»ê
	double m_P[6][6];	// Velocity, Position Kalman FilterÀÇ °øºÐ»ê
	double m_Q[3][3];	// Attitude Kalman FilterÀÇ °øºÐ»ê

	double m_Kh[3][3];
	double m_Kv[6][3];
	double m_Kp[6][3];

	double m_heading;

	double VehicleRad2NaviRad(double ang);
	double GpsDeg2NaviDeg(double ang);
	double init_bias_gyro[3];
	double init_bias_accl[3];

	bool CalcInitBiasScale (double gyro[3], double accl[3], int maxCount);

public:
	sIMU m_canimu;
	int m_count;
	
private:
	AttitudeKF m_attitude_kf;
	PosVelKF m_posvel_kf;
	Filter_IMU m_filter_gyro;
	Filter_IMU m_filter_accl;

};





