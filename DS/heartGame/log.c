#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "log.h"

FILE *logFile;

void CreateLog(char *_fileName)
{
	char path[20] = "./log/";
	
	strcat(path,_fileName);
	
	logFile = fopen(path,"a");
	
	assert(logFile);
}

void CloseLog()
{
	fclose(logFile);
}

void LOG(const char *_moduleName, const char *_funcName, int _lineNum, int _trace, char *_userStr)
{
	static int pid = 1;
	char buff[20], traceStr[20] = "";
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
 	strftime(buff, sizeof(buff), "%H:%M:%S %d-%m-%Y", tm);
 	
	strcat(traceStr,(INFO == _trace) ? "INFO" : "ERROR");
	
	fprintf(logFile, "Current time: %s | Module name: %s | PID: %d | TRACE: %s | Text: %s \n", buff, _moduleName, pid, traceStr, _userStr);
	
	++pid;
}



