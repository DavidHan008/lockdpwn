#include "../inc/eCAN.h"
#include <time.h>

//////////////////////////////////////////////////////////////////////////
// static constants, types, macros, variables

/** ECI Demo send timeout in [ms] @ingroup EciDemo */
#define ECI_TX_TIMEOUT 500

/** ECI Demo TX message count for CAN @ingroup EciDemo */
#define ECI_TX_MSGCOUNT_CAN (0x800 * 1)

/** ECI Demo receive timeout in [ms] @ingroup EciDemo */
#define ECI_RX_TIMEOUT 0

//#define ECIDEMO_HWUSEPOLLINGMODE

/** ECI Demo error check macro @ingroup EciDemo */
#define ECIDEMO_CHECKERROR(FuncName)					\
  {                                                                     \
    if(ECI_OK == hResult)                                               \
    {                                                                   \
      OS_Printf(#FuncName "...succeeded.\n");                           \
    }                                                                   \
    else                                                                \
    {                                                                   \
      OS_Printf( #FuncName "...failed with errorcode: 0x%08X. %s\n",    \
                 hResult,                                               \
                 ECI10A_GetErrorString(hResult));                       \
    }                                                                   \
  }

eCAN::eCAN (int can_I)		
{
  for(int i = 0 ; i < 4 ; i++)
  {
    sprintf(s_vehicle_obd[i].text, "no data");
    //s_vehicle_obd[i].updateFlag = false;
  }


  OS_Printf("CAN 초기화\n");

  ECI_RESULT hResult = ECI_OK;

  ECI_HW_PARA aHwPara[2];
  ECI_HW_INFO stcHwInfo   = {0};
  DWORD       dwHwIndex   = 0;
  DWORD       dwCtrlIndex = can_I;

  // 두번째 연결 위한 초기화.
  memset(aHwPara, 0, sizeof(ECI_HW_PARA) * 2);
  aHwPara[0].wHardwareClass = ECI_HW_USB;
  aHwPara[1].wHardwareClass = ECI_HW_USB;


  hResult = ECI10A_Initialize(1,  aHwPara);
  ECIDEMO_CHECKERROR(ECI10A_Initialize);





  // Retrieve hardware info
  if(ECI_OK == hResult)
  {
    // Retrieve hardware info
    hResult = ECI10A_GetInfo(dwHwIndex, &stcHwInfo);
    ECIDEMO_CHECKERROR(ECI10A_GetInfo);
    if(ECI_OK == hResult)
      EciPrintHwInfo(&stcHwInfo);
  }

  if(ECI_OK == hResult)
  {
    hResult = EciGetNthCtrlOfClass(&stcHwInfo,
                                   ECI_CTRL_CAN,
                                   can_I, //first relative controller
                                   &dwCtrlIndex);
  }

  hCanCtl[0] = ECI_INVALID_HANDLE;


  if(ECI_OK == hResult)
  {
    ECI_CTRL_CONFIG stcCtrlConfig = {0};

    // Set CAN Controller configuration
    stcCtrlConfig.wCtrlClass                = ECI_CTRL_CAN;
    stcCtrlConfig.u.sCanConfig.dwVer        = ECI_STRUCT_VERSION_V0;
    stcCtrlConfig.u.sCanConfig.u.V0.bBtReg0 = ECI_CAN_BT0_500KB;
    stcCtrlConfig.u.sCanConfig.u.V0.bBtReg1 = ECI_CAN_BT1_500KB;
    stcCtrlConfig.u.sCanConfig.u.V0.bOpMode = ECI_CAN_OPMODE_STANDARD | ECI_CAN_OPMODE_EXTENDED | ECI_CAN_OPMODE_ERRFRAME;

    // Open and Initialize given Controller of given board
    hResult = ECI10A_CtrlOpen(&hCanCtl[0], dwHwIndex, dwCtrlIndex, &stcCtrlConfig);
    ECIDEMO_CHECKERROR(ECI10A_CtrlOpen);
  }



  if(ECI_OK == hResult)
  {
    ECI_CTRL_CAPABILITIES stcCtrlCaps = {0};

    hResult = ECI10A_CtrlGetCapabilities(hCanCtl[0], &stcCtrlCaps);
    ECIDEMO_CHECKERROR(ECI10A_CtrlGetCapabilities);
    if(ECI_OK == hResult)
    {EciPrintCtrlCapabilities(&stcCtrlCaps);}
  }




  if(ECI_OK == hResult)
  {
    hResult = ECI10A_CtrlStart(hCanCtl[0]);
    ECIDEMO_CHECKERROR(ECI10A_CtrlStart);
  }



}

eCAN::~eCAN()	 
{
  ECI10A_Release();

  ECI10A_CtrlStop(hCanCtl[0], ECI_STOP_FLAG_NONE);
  ECI10A_CtrlStop(hCanCtl[0], ECI_STOP_FLAG_RESET_CTRL);
  ECI10A_CtrlClose(hCanCtl[0]);
  hCanCtl[0] = ECI_INVALID_HANDLE;

}




void eCAN::TransmitCanMsg(UINT8 *msgData, UINT32 id)
{
  HRESULT hResult;
  ECI_CTRL_MESSAGE sCanMsg = {0};
  DWORD dwTxMsgCount = ECI_TX_MSGCOUNT_CAN;
  DWORD dwIndex = 0;
  int i;

  srand((unsigned int)time(NULL));

  OS_Printf("Now, sending %u CAN Messages\n", dwTxMsgCount);

  sCanMsg.wCtrlClass                            = ECI_CTRL_CAN;
  sCanMsg.u.sCanMessage.dwVer                   = ECI_STRUCT_VERSION_V0;
  sCanMsg.u.sCanMessage.u.V0.dwMsgId            = id;
  sCanMsg.u.sCanMessage.u.V0.uMsgInfo.Bits.dlc  = 8;


  for (i = 0; i < 8; i++ )
  {
    sCanMsg.u.sCanMessage.u.V0.abData[i] = msgData[i];
    printf("%02X ", msgData[i]);
  }

  hResult = ECI10A_CtrlSend( hCanCtl[0], &sCanMsg, ECI_TX_TIMEOUT );
	
  if(hResult == ECI_OK)
    printf("trans ok\n");
}


void eCAN::GetCanMsg(sCanData *TargetData, ECI_CTRL_MESSAGE *SourceData)
{
	
  int j;
  TargetData->dwTime = SourceData->u.sCanMessage.u.V0.dwTime;
  TargetData->dwMsgId = SourceData->u.sCanMessage.u.V0.dwMsgId;
	
  for (j = 0; j < 8; j++){
    TargetData->abData[j] = SourceData->u.sCanMessage.u.V0.abData[j];
  }

  sprintf(TargetData->text, "ID: %08X Data: %02X %02X %02X %02X %02X %02X %02X %02X\n",TargetData->dwMsgId,
          TargetData->abData[0],
          TargetData->abData[1],
          TargetData->abData[2],
          TargetData->abData[3],
          TargetData->abData[4],
          TargetData->abData[5],
          TargetData->abData[6],
          TargetData->abData[7]);
}


void eCAN::ReadCanBuffer(void)
{
  ECI_CTRL_MESSAGE stcCtrlMsg   = {0};
  DWORD dwCount = 0;

  dwCount = 1;


  // CAN MSG 수신.
  while(ECI10A_CtrlReceive(hCanCtl[0], &dwCount, &stcCtrlMsg, ECI_RX_TIMEOUT) == ECI_OK)
  {
    if(ECI_STRUCT_VERSION_V0 == stcCtrlMsg.u.sCanMessage.dwVer)
    {
      //*** Print Data if not RTR
      if(!stcCtrlMsg.u.sCanMessage.u.V0.uMsgInfo.Bits.rtr)
      {

        // 수신한 CAN data 할당.
        switch(stcCtrlMsg.u.sCanMessage.u.V0.dwMsgId)
        {
          case 0x220:
            GetCanMsg(&s_vehicle_obd[3], &stcCtrlMsg);
            s_vehicle_obd[3].updateFlag = true;
            break;
          case 0x2B0:
            GetCanMsg(&s_vehicle_obd[0], &stcCtrlMsg);
            s_vehicle_obd[0].updateFlag = true;
            break;
          case 0x316:
            GetCanMsg(&s_vehicle_obd[1], &stcCtrlMsg);
            s_vehicle_obd[1].updateFlag = true;
            break;
          case 0x4F0:
            GetCanMsg(&s_vehicle_obd[2], &stcCtrlMsg);
            s_vehicle_obd[2].updateFlag = true;
            break;
        }
      }
    }
  }

}


// 핸들 할당.

ECI_RESULT eCAN::EciGetNthCtrlOfClass( const ECI_HW_INFO* pstcHwInfo,
				       e_CTRLCLASS        eCtrlClass,
				       DWORD              dwRelCtrlIndex,
				       DWORD*             pdwCtrIndex)
{
  ECI_RESULT hResult = ECI_ERR_RESOURCE_NOT_FOUND;

  //*** Check Arguments
  if((NULL != pstcHwInfo) && (NULL != pdwCtrIndex))
  {
    //*** Struct Version 0
    if(pstcHwInfo->dwVer == ECI_STRUCT_VERSION_V0)
    {
      DWORD dwIndex = 0;
      //*** Iterate through all controllers
      for(dwIndex=0; dwIndex < pstcHwInfo->u.V0.dwCtrlCount; dwIndex++)
      {
        if(pstcHwInfo->u.V0.sCtrlInfo[dwIndex].wCtrlClass == eCtrlClass)
        {
          //*** Controller not found yet
          if(hResult != ECI_OK)
          {
            if(dwRelCtrlIndex == 0)
            {
              //*** Controller found
              *pdwCtrIndex = dwIndex;
              hResult    = ECI_OK;
            }
            else
              dwRelCtrlIndex--;
          }
        }//endif
      }//end for
    }//endif
  }
  else
    hResult = ECI_ERR_INVALID_POINTER;

  return hResult;
}




//  하드웨어 정보 출력 함수.


void eCAN::EciPrintHwInfo(const ECI_HW_INFO* pstcHwInfo)
{
  //*** Check Argument
  if(NULL == pstcHwInfo)
  {
    OS_Printf("ERROR: invalid pointer: pstcHwInfo\n");
    return;
  }

  OS_Printf( "HwInfoVer: \"%u\"\n", pstcHwInfo->dwVer);

  //*** Struct Version 0
  if(pstcHwInfo->dwVer == ECI_STRUCT_VERSION_V0)
  {
    DWORD dwCtrlIndex = 0;

    OS_Printf( "BoardType: \"%s\"\n",
               pstcHwInfo->u.V0.szHwBoardType);
    OS_Printf( "HwSerial : \"%s\"\n",
               pstcHwInfo->u.V0.szHwSerial);
    OS_Printf( "HwVersion: \"%u.%u.%u.%u\"\n",
               pstcHwInfo->u.V0.abHwVersion[0],
               pstcHwInfo->u.V0.abHwVersion[1],
               pstcHwInfo->u.V0.abHwVersion[2],
               pstcHwInfo->u.V0.abHwVersion[3]);
    OS_Printf( "BmVersion: \"%u.%u.%u.%u\"\n",
               pstcHwInfo->u.V0.abBmVersion[0],
               pstcHwInfo->u.V0.abBmVersion[1],
               pstcHwInfo->u.V0.abBmVersion[2],
               pstcHwInfo->u.V0.abBmVersion[3]);
    OS_Printf( "FwIdentif: \"%s\"\n",
               pstcHwInfo->u.V0.szFwIdentification);
    OS_Printf( "FwVersion: \"%u.%u.%u.%u\"\n",
               pstcHwInfo->u.V0.abFwVersion[0],
               pstcHwInfo->u.V0.abFwVersion[1],
               pstcHwInfo->u.V0.abFwVersion[2],
               pstcHwInfo->u.V0.abFwVersion[3]);
    OS_Printf( "EciApiVer: \"%u.%u.%u.%u\"\n",
               pstcHwInfo->u.V0.adwApiVersion[0],
               pstcHwInfo->u.V0.adwApiVersion[1],
               pstcHwInfo->u.V0.adwApiVersion[2],
               pstcHwInfo->u.V0.adwApiVersion[3]);

    OS_Printf( "CtrlCount: \"%u\"\n",
               pstcHwInfo->u.V0.dwCtrlCount);
    for(dwCtrlIndex=0; dwCtrlIndex < pstcHwInfo->u.V0.dwCtrlCount; dwCtrlIndex++)
    {
      OS_Printf( "CtrlIndex: \"%u\"\n",
                 dwCtrlIndex);
      OS_Printf( "CtrlClass: \"0x%04x\"\n",
                 pstcHwInfo->u.V0.sCtrlInfo[dwCtrlIndex].wCtrlClass);
      OS_Printf( "CtrlState: \"0x%04x\"\n",
                 pstcHwInfo->u.V0.sCtrlInfo[dwCtrlIndex].wCtrlState);
    }//end for
  }//endif
}



void eCAN::EciPrintCtrlCapabilities(const ECI_CTRL_CAPABILITIES* pstcCtrlCaps)
{
  //*** Check Argument

  if(NULL == pstcCtrlCaps)
  {
    OS_Printf("ERROR: invalid pointer: pstcCtrlCaps\n");
    return;
  }

  //*** Switch on controller class
  switch(pstcCtrlCaps->wCtrlClass)
  {
    //*** CAN
    case ECI_CTRL_CAN:
      {
        OS_Printf( "CapsVer  : \"%u\"\n",
                   pstcCtrlCaps->u.sCanCaps.dwVer);

        //*** Struct Version 0
        if(pstcCtrlCaps->u.sCanCaps.dwVer == ECI_STRUCT_VERSION_V0)
        {
          OS_Printf( "CanType  : \"0x%04x\"\n",
                     pstcCtrlCaps->u.sCanCaps.u.V0.wCanType);
          OS_Printf( "BusCoupl : \"0x%04x\"\n",
                     pstcCtrlCaps->u.sCanCaps.u.V0.wBusCoupling);
          OS_Printf( "Feature  : \"0x%04x\"\n",
                     pstcCtrlCaps->u.sCanCaps.u.V0.dwFeatures);
          OS_Printf( "ClockFreq: \"%u\"\n",
                     pstcCtrlCaps->u.sCanCaps.u.V0.dwClockFreq);
          OS_Printf( "TscDiv   : \"%u\"\n",
                     pstcCtrlCaps->u.sCanCaps.u.V0.dwTscDivisor);
          OS_Printf( "DtxDiv   : \"%u\"\n",
                     pstcCtrlCaps->u.sCanCaps.u.V0.dwDtxDivisor);
          OS_Printf( "DtxMaxTic: \"%u\"\n",
                     pstcCtrlCaps->u.sCanCaps.u.V0.dwDtxMaxTicks);
          OS_Printf( "PrioQueue: \"%u\"\n",
                     pstcCtrlCaps->u.sCanCaps.u.V0.dwNoOfPrioQueues);
        }
        break;
      }//end case ECI_CTRL_CAN

      //*** Unknown
    default:
      break;
  }//end switch
}


