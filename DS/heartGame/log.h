#ifndef __LOG__
#define __LOG__

enum
{
	INFO,
	ERROR
};

#define Z_LOG(_trace, _userStr) LOG(__FILE__, __FUNCTION__, __LINE__, _trace, _userStr)

void CreateLog(char *_fileName);

void CloseLog();

void LOG(const char *_moduleName, const char *_funcName, int _lineNum, int _trace, char *_userStr);




#endif
