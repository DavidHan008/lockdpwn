#include "../inc/CAN_OBD2.h"

#define UINT8 uint8_t
#define UINT16 uint16_t

CAN_OBD2::CAN_OBD2(int can_I)  	
{
	m_canport = new eCAN(can_I);
}

CAN_OBD2::~CAN_OBD2()
{
	delete m_canport;
	m_canport = NULL;
}

bool CAN_OBD2::GetCANdata()
{												
	UINT8 *pData;
	UINT16 Temp;
	
	if (m_canport->s_vehicle_obd[3].updateFlag == true){

		pData = m_canport->s_vehicle_obd[3].abData;

		m_gyro[0] = 0;		//deg/s
		m_gyro[1] = 0;

		Temp = (0x1F & pData[7])<<8;
		Temp |= pData[6];	
		m_gyro[2] = -(Temp*0.01 - 40.95); //deg/s

		m_accl[0] = 0;
		m_accl[1] = 0;	
		m_accl[2] = 0;	

		m_canport->s_vehicle_obd[3].updateFlag = false;
		return true;
	}else{	
		return false;
	}
}	

void CAN_OBD2::DoIMUFilter()
{
	double gyro[3] = { m_gyro[0], m_gyro[1], m_gyro[2] };	

	m_Filter.LowpPassFilter (gyro);
	m_Filter.HDR (gyro, 0.1, 0.001);		
	m_Filter.Delagging (gyro);
	
}


bool CAN_OBD2::GetObdSAS()
{
	UINT8 *pData;
	UINT16 Temp;

	if (m_canport->s_vehicle_obd[0].updateFlag == true){
		pData = m_canport->s_vehicle_obd[0].abData;
		Temp = pData[1]<<8;
		Temp |= pData[0];	

		m_steeringAngle = Temp * 0.1;
	
		if ( m_steeringAngle >= 3276.8 )
			m_steeringAngle -= 6553.5;

		m_steeringAngle *= -1;

		m_canport->s_vehicle_obd[0].updateFlag = false;
		return true;
	}
	else
		return false;
}

bool CAN_OBD2::GetObdVelocity1()
{
	UINT8 *pData;
	UINT16 Temp;
	
	if (m_canport->s_vehicle_obd[1].updateFlag == true){	

		pData = m_canport->s_vehicle_obd[1].abData;
		Temp = pData[6];			
		m_speed1 = Temp * 1000./(60.*60.) * 3.6;	

		m_canport->s_vehicle_obd[1].updateFlag = false;
		return true;
	}
	else{	
		return false;
	}
}

bool CAN_OBD2::GetObdVelocity2()
{
	UINT8 *pData;
	UINT16 Temp;
	
	if (m_canport->s_vehicle_obd[2].updateFlag == true){
		pData = m_canport->s_vehicle_obd[2].abData;
		Temp = (0x1 & pData[2])<<8;
		Temp |= pData[1];			
		m_speed2 = Temp * 0.5*1000./(60.*60.) * 3.6;	

		m_canport->s_vehicle_obd[2].updateFlag = false;
		return true;
	}
	else{
		return false;
	}
}

