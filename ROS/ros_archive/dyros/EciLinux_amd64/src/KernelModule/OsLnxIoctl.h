#ifndef OSLNXIOCTL_H_INCLUDED
#define OSLNXIOCTL_H_INCLUDED

#define OSLNXKM_PCIREG1_MAP_INDEX 0
#define OSLNXKM_PCIREG2_MAP_INDEX 1
#define OSLNXKM_DEVMEM_MAP_INDEX  2
#define OSLNXKM_ADDMEM_MAP_INDEX  64
#define OSLNXKM_DMA_MAP_OFFSET    128


// For IOCTL_GETDEVICETYPE
struct getdevicetype_param
{
  unsigned short int wVendorId;
  unsigned short int wDeviceId;
  unsigned short int wSubVendorId;
  unsigned short int wSubSystemId;
};

// For IOCTL_GETDEVICEINFO
struct getdeviceinfo_param
{
  unsigned long lPciRegister1;
  unsigned long lPciRegister2;
  unsigned long lDevMemory;
  unsigned int  dwDevIrq;
};

// For IOCTL_GETDMAINFO
struct getdmainfo_param
{
  unsigned long lDmaIndex;  //in
  unsigned long lDmaOffset; //out
  unsigned long lPhysAddr;  //out
};

#define IOCTL_GETREGMAPOFFSET     _IOR ('E', 0xF2, unsigned long)
#define IOCTL_GETDATAMAPOFFSET    _IOR ('E', 0xF3, unsigned long)
#define IOCTL_GETDEVICETYPE       _IOR ('E', 0xF4, struct getdevicetype_param)
#define IOCTL_GETADDMEMMAPOFFSET  _IOR ('E', 0xF5, unsigned long)
#define IOCTL_GETDMAINFO          _IOWR('E', 0xF6, struct getdmainfo_param)
#define IOCTL_GETREG2MAPOFFSET    _IOR ('E', 0xF7, unsigned long)
#define IOCTL_GETDEVICEINFO       _IOR ('E', 0xF8, struct getdeviceinfo_param)
#define IOCTL_SETDEVICEIRQ        _IOW ('E', 0xF9, unsigned int)

#endif // OSLNXIOCTL_H_INCLUDED
