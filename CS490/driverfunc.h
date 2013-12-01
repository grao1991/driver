#include "public.h"
#include <windows.h>
#include <setupapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <winioctl.h>

typedef enum OperationType {
  LOGIN,
  ADDUSER
} OPERATION_TYPE;

int ApplyToDriver(USER_INFO* user_info, OPERATION_TYPE operation_type, HANDLE hDevice) {
  int bResult;
  ULONG ulOutput;
  DWORD dwIoControlCode;
  switch (operation_type) {
    case LOGIN:
      dwIoControlCode = IOCTL_LOGIN;
      break;
    case ADDUSER:
      dwIoControlCode = IOCTL_ADDUSER;
      break;
    default:
      return 0; 
  }
  DeviceIoControl(hDevice,
      dwIoControlCode,
      user_info,
      sizeof(USER_INFO),
      &bResult,
      1,
      &ulOutput,
      NULL);
  return bResult;
}

PCHAR GetDevicePath(LPGUID InterfaceGuid) {  
    HDEVINFO HardwareDeviceInfo;  
    SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;  
    PSP_DEVICE_INTERFACE_DETAIL_DATA DeviceInterfaceDetailData = NULL;  
    ULONG Length, RequiredLength = 0;  
    BOOL bResult;  
  
    HardwareDeviceInfo = SetupDiGetClassDevs(  
                             InterfaceGuid,  
                             NULL,  
                             NULL,  
                             (DIGCF_PRESENT | DIGCF_DEVICEINTERFACE));  
  
    if (HardwareDeviceInfo == INVALID_HANDLE_VALUE) {  
        fprintf(stderr, "SetupDiGetClassDevs failed!\n");  
        exit(1);  
    }  
    DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);  
  
    bResult = SetupDiEnumDeviceInterfaces(HardwareDeviceInfo,  
        0,  
        InterfaceGuid,  
        0,  
        &DeviceInterfaceData);  
    if (bResult == FALSE) {  
        fprintf(stderr, "SetupDiEnumDeviceInterfaces failed.\n");  
        SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);  
        exit(1);  
    }  
  
    SetupDiGetDeviceInterfaceDetail(  
        HardwareDeviceInfo,  
        &DeviceInterfaceData,  
        NULL,  
        0,  
        &RequiredLength,  
        NULL  
        );  

    DeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA) LocalAlloc(LMEM_FIXED, RequiredLength);  
    if (DeviceInterfaceDetailData == NULL) {  
        fprintf(stderr, "Failed to allocate memory.\n");  
        SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);  
        exit(1);  
    }  
    DeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);  
    Length = RequiredLength;  
  
    bResult = SetupDiGetDeviceInterfaceDetail(  
                  HardwareDeviceInfo,  
                  &DeviceInterfaceData,  
                  DeviceInterfaceDetailData,  
                  Length,  
                  &RequiredLength,  
                  NULL);  
    if (bResult == FALSE) {  
        fprintf(stderr, "Error in SetupDiGetDeviceInterfaceDetail\n");  
        SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);  
        LocalFree(DeviceInterfaceDetailData);  
        exit(1);  
    }  
    return DeviceInterfaceDetailData->DevicePath;  
}  

