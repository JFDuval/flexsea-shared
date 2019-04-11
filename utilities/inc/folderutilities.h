#ifndef FOLDER_UTILITIES_H
#define FOLDER_UTILITIES_H

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
inline int isIllegalFileChar(char c)
{
    return c == '\n' || c == '\t';
}
void appendExtension(const char * file, const char * extension, char * fileExt);
void appendPath(const char* directory1,const char* directory2, char * appendedDir);


#endif //FOLDER_UTILITIES_H
