#include "func.h"
#include <stdio.h>
#include <wdm.h>

#define MD5ENCODELEN 16

#define READ(x) status = ZwReadFile(hFile, \
        NULL, \
        NULL, \
        NULL, \
        &iostatus, \
        (PVOID) (x), \
        MD5ENCODELEN, \
        NULL, \
        NULL)

#define WRITE(x) ZwWriteFile(hFile, \
      NULL, \
      NULL, \
      NULL, \
      &iostatus, \
      (PVOID) (x), \
      MD5ENCODELEN, \
      NULL, \
      NULL)

unsigned char* md5(char* str) {
  static unsigned char digest[MD5ENCODELEN];

  MD5_CTX ctx;
  MD5Init(&ctx);
  MD5Update(&ctx, (unsigned char*)str, (unsigned)strlen(str));
  MD5Final(digest, &ctx);
  return digest;
}

int CheckUser(USER_INFO* user_info) {
  NTSTATUS status;
  OBJECT_ATTRIBUTES oa;
  IO_STATUS_BLOCK iostatus;
  HANDLE hFile;
  UNICODE_STRING filename = RTL_CONSTANT_STRING(L"\\??\\C:\\user.dat");
  unsigned char md5username[MD5ENCODELEN];
  unsigned char md5password[MD5ENCODELEN]; 
  InitializeObjectAttributes(&oa, &filename, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

  status = ZwCreateFile(&hFile,
      GENERIC_READ,
      &oa,
      &iostatus,
      NULL,
      0,
      FILE_SHARE_READ,
      FILE_OPEN_IF,
      FILE_SYNCHRONOUS_IO_NONALERT,
      NULL,
      0);
  if (!NT_SUCCESS(status)) {
    DbgPrint("Open file error");
    ZwClose(hFile);
    return 0;
  }
  while (1) {
    READ(md5username);
    if (!NT_SUCCESS(status)) {
      break;
    }
    READ(md5password);
    if (!NT_SUCCESS(status)) {
      DbgPrint("Read password error");
      ZwClose(hFile);
      return 0;
    }
    if (!memcmp(md5username, md5(user_info->username), MD5ENCODELEN) &&
        !memcmp(md5password, md5(user_info->password), MD5ENCODELEN)) {
      ZwClose(hFile);
      return 1;
    }
  }
  ZwClose(hFile);
  return 0;
}

int AddUser(USER_INFO* user_info) {
  NTSTATUS status;
  OBJECT_ATTRIBUTES oa;
  IO_STATUS_BLOCK iostatus;
  HANDLE hFile;
  UNICODE_STRING filename = RTL_CONSTANT_STRING(L"\\??\\C:\\user.dat");
  unsigned char md5username[MD5ENCODELEN];
  unsigned char md5password[MD5ENCODELEN]; 
  InitializeObjectAttributes(&oa, &filename, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

  status = ZwCreateFile(&hFile,
      GENERIC_READ,
      &oa,
      &iostatus,
      NULL,
      0,
      FILE_SHARE_READ,
      FILE_OPEN_IF,
      FILE_SYNCHRONOUS_IO_NONALERT,
      NULL,
      0);
  if (!NT_SUCCESS(status)) {
    DbgPrint("Open file error");
    ZwClose(hFile);
    return 0;
  }
  while (1) {
    READ(md5username);
    if (!NT_SUCCESS(status)) {
      break;
    }
    READ(md5password);
    if (!NT_SUCCESS(status)) {
      DbgPrint("Read password error");
      ZwClose(hFile);
      return 0;
    }
    if (!memcmp(md5username, md5(user_info->username), MD5ENCODELEN)) {
      ZwClose(hFile);
      return 0;
    }
  }
  ZwClose(hFile);

  status = ZwCreateFile(&hFile,
    FILE_APPEND_DATA,
    &oa,
    &iostatus,
    NULL,
    0,
    FILE_SHARE_WRITE,
    FILE_OPEN_IF,
    FILE_SYNCHRONOUS_IO_NONALERT,
    NULL,
    0);
  if (!NT_SUCCESS(status)) {
    DbgPrint("Open file error");
    ZwClose(hFile);
    return 0;
  }
  WRITE(md5(user_info->username));
  if (!NT_SUCCESS(status)) {
    ZwClose(hFile);
    return 0;
  }
  WRITE(md5(user_info->password));
  if (!NT_SUCCESS(status)) {
    ZwClose(hFile);
    return 0;
  }
  ZwClose(hFile);
  return 1;
}

