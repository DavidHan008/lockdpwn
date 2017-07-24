#include "../inc/Filter.h"

#define FALSE 0
#define TRUE 1

#define UINT8 uint8_t
#define UINT16 uint16_t

Filter::Filter()  	
{
	memset (&m_ha[0], 0, sizeof(m_ha));
	memset (&m_a[0], 0, sizeof(m_a));
	memset (&m_v[0], 0, sizeof(m_v));
	memset (&m_p[0], 0, sizeof(m_p));

	memset (&m_P[0][0], 0, sizeof(m_P));
	memset (&m_Q[0][0], 0, sizeof(m_Q));
	

	m_count = 0;
	m_heading = 0;	
	
	for(int i = 0 ; i < 3 ; i++)
	{
		init_bias_gyro[i] = 0.;
		init_bias_accl[i] = 0.;
	}

}

Filter::~Filter()
{

}


bool Filter::CalcInitBiasScale (double gyro[3], double accl[3], int maxCount)		
{
	if (m_count < maxCount) {
		init_bias_gyro[0] += gyro[0];
		init_bias_gyro[1] += gyro[1];
		init_bias_gyro[2] += gyro[2];

		init_bias_accl[0] += accl[0];
		init_bias_accl[1] += accl[1];
		init_bias_accl[2] += accl[2];

		return false;
	}
	else if (m_count == maxCount) {
		init_bias_gyro[0] /= maxCount;
		init_bias_gyro[1] /= maxCount;
		init_bias_gyro[2] /= maxCount;

		init_bias_accl[0] /= maxCount;
		init_bias_accl[1] /= maxCount;
		init_bias_accl[2] /= maxCount;
		
		return false;
	}
	else {
		gyro[0] -= init_bias_gyro[0];
		gyro[1] -= init_bias_gyro[1];
		gyro[2] -= init_bias_gyro[2];
	
		accl[0] -= init_bias_accl[0];
		accl[1] -= init_bias_accl[1]; 
		accl[2] -= init_bias_accl[2];

		return true;
	}
}
	

void Filter::DoCal(double dt)
{
	double gyro[3] = { m_canimu.gyro[0], m_canimu.gyro[1], m_canimu.gyro[2] };	
	double accl[3] = { m_canimu.accl[0], m_canimu.accl[1], m_canimu.accl[2] };		

		
	{
		if (0 < m_gps.gps_quality) 
		{
			double yaw = -m_gps.heading;		

			//double vel = (odometry.WheelSpeed_RL + odometry.WheelSpeed_RR)/2;
			double vel = m_canimu.obdVel*1000./(60.*60.);//m_gps.velocity*1000./(60.*60.);

			m_attitude_kf.Predict (gyro, dt);
			m_attitude_kf.Update (yaw, vel);	
	
			m_posvel_kf.Predict (m_attitude_kf._X_XYZ, gyro, accl, dt);
			m_posvel_kf.Update (m_attitude_kf._X_XYZ, m_tm_x, m_tm_y, m_gps.altitude);
			
			//memcpy (&_a[0], &_posvel_kf._a[0], sizeof(_a));
			memcpy (&m_v[0], &m_posvel_kf._x[0], sizeof(m_v));
		
			memcpy (&m_p[0], &m_posvel_kf._x[3], sizeof(m_p));
	

			m_heading =  VehicleRad2NaviRad(-atan2(m_attitude_kf._X_XYZ(1,0) ,m_attitude_kf._X_XYZ(0,0)));
			/*
m_heading =  atan2(m_attitude_kf._X_XYZ(1,0) ,m_attitude_kf._X_XYZ(0,0));
			if ( m_heading < 0 )
			{
				m_heading += _DEG2RAD*450.0;
			}
			else
			{
 				m_heading += _DEG2RAD*90.0;
			}
			*/
			//printf("x : %f, y: %f, heading : %f\n", m_p[0], m_p[1], m_heading);

		}
	}

	if (m_count < 10000) ++m_count;
}

double Filter::VehicleRad2NaviRad(double ang)
{

	double da;
	if(ang >=0)
	{
		da = ang;
	}
	else
	{
		da = ang + 2*M_PI;
		
	}
	return da;
/*
	double da;
	if(ang >=0){
		da = ang + M_PI/2;
	}else{
		if(ang >= -M_PI/2){
			da = ang + M_PI/2;
		}else{
			da = ang + 2*M_PI + M_PI/2;
			da = fmod (da, 2*M_PI);
		}
	}
	return da;
*/

}
double Filter::GpsDeg2NaviDeg(double ang)
{
	double da =360 + 90 - ang;
	da = fmod (da, 360);
	return da;
}





