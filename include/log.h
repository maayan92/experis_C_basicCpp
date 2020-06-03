#ifndef __LOG__
#define __LOG__

enum
{
	INFO,
	ERROR
};

void CreateLog(char *_fileName);

void CloseLog();

void LOG(char *_moduleName, int _trace, char *_userStr);




#endif
