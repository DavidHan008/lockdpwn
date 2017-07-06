#include "../inc/CAN_MCU.h"



#define FALSE 0
#define TRUE 1

#define UINT8 uint8_t
#define UINT16 uint16_t



CAN_MCU::CAN_MCU(int can_I)  	
{
	_canport = new eCAN(can_I);

}

CAN_MCU::~CAN_MCU()
{
	delete _canport;
	_canport = NULL;
}

bool CAN_MCU::GetOdometrydata ()	
{
	UINT8 *pData;
	UINT16 Temp;
	
	if (_canport->CAR_WHL_SPD_RAW.updateFlag == TRUE){	
		pData = _canport->CAR_WHL_SPD_RAW.abData;
		Temp = pData[1]<<8;
		Temp |= pData[0];			
		_mcuOdometry.WheelSpeed_RR	= Temp * 0.01*1000./(60.*60.);	
	
		Temp = pData[3]<<8;
		Temp |= pData[2];
		_mcuOdometry.WheelSpeed_RL	= Temp * 0.01*1000./(60.*60.); 

		Temp = pData[5]<<8;
		Temp |= pData[4];			
		_mcuOdometry.WheelSpeed_FR	= Temp * 0.01*1000./(60.*60.);	
	
		Temp = pData[7]<<8;
		Temp |= pData[6];
		_mcuOdometry.WheelSpeed_FL	= Temp * 0.01*1000./(60.*60.); 

		_canport->CAR_WHL_SPD_RAW.updateFlag = FALSE;
		return true;
	}else
		return false;
}

bool CAN_MCU::GetMcuBrkAcc ()
{
	UINT8 *pData;
	UINT16 Temp;
	int bit;	

	if (_canport->CAR_MONITOR_BRK_ACC.updateFlag == TRUE){	
		
		pData = _canport->CAR_MONITOR_BRK_ACC.abData;
	
		bit = (0x1 & pData[0]);
		_mcuBrkAcc.BrkCtlBit = bit;

		bit = (0x1 & (pData[0] >> 1));
		_mcuBrkAcc.AccCtlBit = bit;

		Temp = pData[1];
		_mcuBrkAcc.ArmAngle = Temp;

		Temp = pData[2];
		_mcuBrkAcc.AccVoltage = Temp;

		_canport->CAR_MONITOR_BRK_ACC.updateFlag = FALSE;
		return true;
	}else{	
		return false;
	}
}



bool CAN_MCU::GetMcuSAS ()
{
	UINT8 *pData;
	UINT16 Temp;
	int bit;	

	if (_canport->CAR_MONITOR_STEER.updateFlag == TRUE){	
		
		pData = _canport->CAR_MONITOR_STEER.abData;
	
		bit = (0x1 & pData[0]);
		_mcuSAS.SteerCtlBit = bit;

		Temp = pData[2]<<8;
		Temp |= pData[1];	

		_mcuSAS.SteeringAngle = Temp * 0.1;
	
		if ( _mcuSAS.SteeringAngle >= 3276.8 )
			_mcuSAS.SteeringAngle -= 6553.5;

		_canport->CAR_MONITOR_STEER.updateFlag = FALSE;
		return true;
	}else{	
		return false;
	}
}







