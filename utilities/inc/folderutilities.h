#ifndef FOLDER_UTILITIES_H
#define FOLDER_UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include<sys/stat.h>
#endif

#define MAX_DATE_TIME_STR_LEN 80
#define MAX_PATH_LEN 255

void NowTime(char *);
void str_replace(char toReplace,char replacement,char * dest, int maxLen);
int createFolder(const char * path);
int isIllegalFileChar(char c);
void appendExtension(const char * file, const char * extension, char * fileExt);
void appendPath(const char* directory1,const char* directory2, char * appendedDir);
#ifdef __cplusplus
}
#endif

#endif //FOLDER_UTILITIES_H
