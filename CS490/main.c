#include "driverfunc.h"

int _cdecl main() {
  int num = 0;
  USER_INFO user_info;
  PCHAR DevicePath = GetDevicePath((LPGUID)&GUID_DEVINTERFACE_CS490);
  HANDLE hDevice = CreateFile((LPCTSTR)DevicePath,
      GENERIC_READ|GENERIC_WRITE,
      0,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL);
  if (hDevice == NULL) {
    fprintf(stderr, "CreateFile Error %d\n", GetLastError());
    return GetLastError();
  }

  while (1) {
	  scanf("%d", &num);
	  printf("Username: ");
	  scanf("%s", user_info.username);
	  printf("Password: ");
	  scanf("%s", user_info.password);
	  if (ApplyToDriver(&user_info, num ? ADDUSER : LOGIN, hDevice)) {
        puts("SUCCESS");
	  } else {
        puts("FAILED");
	  }
  }
  CloseHandle(hDevice);
  return 0;
}


