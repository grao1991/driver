#include <md5.h>
#include <public.h>
#include <stdio.h>

#define MD5ENCODELEN 16
#define FILE_PATH "C:\\user.txt"

unsigned char* md5(char* str);
int CheckUser(USER_INFO* user_info);
int AddUser(USER_INFO* user_info);

