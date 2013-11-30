/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//
#ifndef PUBLIC_H
#define PUBLIC_H
#include <initguid.h>
DEFINE_GUID (GUID_DEVINTERFACE_CS490,
    0xaf5e8605,0xa301,0x463f,0x90,0xad,0x3b,0xee,0xf5,0x1d,0xad,0xa2);
// {af5e8605-a301-463f-90ad-3beef51dada2}

#define IOCTL_LOGIN CTL_CODE(FILE_DEVICE_UNKNOWN, 2222, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_ADDUSER CTL_CODE(FILE_DEVICE_UNKNOWN, 3333, METHOD_BUFFERED, FILE_WRITE_ACCESS)

#define MAX_STRING_LENGTH 256

typedef struct UserInfo {
  char username[MAX_STRING_LENGTH];
  char password[MAX_STRING_LENGTH];
} USER_INFO;
#endif