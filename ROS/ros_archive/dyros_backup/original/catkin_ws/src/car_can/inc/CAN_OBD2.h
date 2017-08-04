#pragma once

#include "eCAN.h"
#include "Filter.h"

#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>


using namespace std;

class CAN_OBD2
{
public:
	CAN_OBD2(int can_I = 0);
	~CAN_OBD2();

	bool GetCANdata(); 
	bool GetObdSAS();	
	bool GetObdVelocity1();	
	bool GetObdVelocity2();	

	void DoIMUFilter();

public:
	double m_gyro[3];		
	double m_accl[3];		
	double m_magnet[3];
	double m_speed1;
	double m_speed2;
	double m_steeringAngle;
	double m_t;

	Filter m_Filter;

	eCAN * m_canport;
};





