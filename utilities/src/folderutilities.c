
#ifdef __cplusplus
extern "C" {
#endif

#include "folderutilities.h"
#include <errno.h>

// Generic function to create string out of current data and time
void NowTime(char *dt)
{
	time_t now = time(0);
	// convert now to string form and format properly
	struct tm * timeinfo = localtime(&now);
	//Do I need to null terminated string
	int size_of_timeDate_string = strftime(dt,MAX_DATE_TIME_STR_LEN,"%Y-%m-%d_%Hh%Mm%Sss", timeinfo);
	str_replace(' ','_',dt,size_of_timeDate_string);
	str_replace(':','.',dt,size_of_timeDate_string);
}

void str_replace(char toReplace,char replacement,char * dest, int maxLen)
{
	int counter = 0;
	while (*dest && counter < maxLen)
	{
		if(*dest == toReplace)
		{
			*dest = replacement;
		}
		dest++;
		counter++;
	}
}

inline int isIllegalFileChar(char c)
{
    return c == '\n' || c == '\t';
}

// Assumes strings are null terminated
inline void appendPath(const char* directory1,const char* directory2, char * appendedDir)
{
	strcpy(appendedDir,directory1);
	#ifdef _WIN32
	char seperator[] = "\\\0";
	#elif __linux__
	char seperator[] = "/\0";
	#endif
	strcat(appendedDir,seperator);
	strcat(appendedDir,directory2);
}

inline void appendExtension(const char * file, const char * extension, char * fileExt)
{
	strcpy(fileExt,file);
	strcat(fileExt,extension);
}

// Type cast into a bool for c++



// Generic function to create folders
int createFolder(const char * path)
{
   int success = 0;
   char pathCopy[MAX_PATH_LEN];
   strcpy(pathCopy,path);
#ifdef _WIN32
   //define something for Windows (32-bit and 64-bit, this part is common)
	str_replace('/','\\',pathCopy,MAX_PATH_LEN);
    CreateDirectoryA(pathCopy, NULL);

    int status = GetLastError();
    if(status == ERROR_ALREADY_EXISTS || status == 0) success = 1;

#elif __linux__
	str_replace('\\','/',pathCopy,MAX_PATH_LEN);

#ifdef __linux__
	mkdir(pathCopy, 777); // Is this too permissive?
#else
	_mkdir(pathCopy);
#endif

    if(errno == EEXIST || errno == 0) success = 1;

#else
#   error "Unknown compiler"
#endif
   //if(success) std::cout << "Folder created : " << pathOK << std::endl;

   return success;
}

#ifdef __cplusplus
}
#endif