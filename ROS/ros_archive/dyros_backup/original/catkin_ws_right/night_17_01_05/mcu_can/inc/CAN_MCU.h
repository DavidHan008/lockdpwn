#pragma once

#include "eCAN.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>             


using namespace std;


struct sOdometry {	//130321 Lk
	double t;
	double WheelSpeed_FL;	// m/s
	double WheelSpeed_FR;	// m/s
	double WheelSpeed_RL;	// m/s
	double WheelSpeed_RR;	// m/s
};

struct sObdVelocity{ //130524 Lk
	double t;
	double Speed;
};


struct sMcuBrkAcc{
	int BrkCtlBit;
	int AccCtlBit;
	double ArmAngle;
	double AccVoltage;
};

struct sMcuSAS{
	int SteerCtlBit;
	double SteeringAngle;
};



class CAN_MCU
{
public:
	CAN_MCU(int can_I);
	~CAN_MCU();

	bool GetOdometrydata();
	bool GetMcuBrkAcc();
	bool GetMcuSAS();

public:
	eCAN *_canport;
	
	sOdometry _mcuOdometry;		
	sMcuBrkAcc _mcuBrkAcc;
	sMcuSAS _mcuSAS;


};





