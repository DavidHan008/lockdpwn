#include "ECI10A.h"
#include "ECI_pshpack1.h"
#include "ECI_poppack.h"
#include <stdint.h>


#define UINT8 uint8_t
#define UINT16 uint16_t
#define UINT32 uint32_t

struct sCanData{
	UINT32	dwTime;
	UINT8	abData[8];
	bool	updateFlag;
	DWORD	dwMsgId;	// 추가.
	char	text[256];	// 추가.
};


class eCAN
{
public:
	ECI_CTRL_HDL hCanCtl[2];
	
	sCanData s_vehicle_obd[4];
	
	bool switching;

	eCAN(int can_I = 0);
	~eCAN();

	void GetCanMsg(sCanData *TargetData, ECI_CTRL_MESSAGE *SourceData);
	void ReadCanBuffer(void);
	void EciPrintHwInfo(const ECI_HW_INFO* pstcHwInfo);
	void TransmitCanMsg(UINT8 *msgData, UINT32 id);	
	void EciPrintCtrlCapabilities(const ECI_CTRL_CAPABILITIES* pstcCtrlCaps);

	ECI_RESULT EciGetNthCtrlOfClass(const ECI_HW_INFO* pstcHwInfo, e_CTRLCLASS eCtrlClass, DWORD dwRelCtrlIndex, DWORD* pdwCtrIndex);

private:
	
};





