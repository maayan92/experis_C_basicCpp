#include <stdio.h>

#include "../time.h"

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

/* CURRENT TIME */

Result TestGetCurrentTime_Valid()
{
	struct timespec currentTime, getTime;
	
	clock_gettime(CLOCK_REALTIME, &currentTime);
	
	getTime = GetCurrentTime(CLOCK_REALTIME);
	
	if(currentTime.tv_sec != getTime.tv_sec)
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

/* RUN TIME */

Result TestGetRunTime_Valid()
{
	struct timespec currentTime, runTime;
	
	currentTime = GetCurrentTime(CLOCK_REALTIME);
	
	runTime = GetRunTime(currentTime,5000,CLOCK_REALTIME);
	
	if((currentTime.tv_sec + 5) != runTime.tv_sec)
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestGetRunTime_NotValid()
{
	struct timespec runTime;
	
	runTime = GetRunTime((struct timespec){-1},5000,CLOCK_REALTIME);
	
	if(-1 == runTime.tv_sec)
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* SLEEP TIME */

Result TestSleepTime_Valid()
{
	struct timespec beforeTime, afterTime, runTime;
	
	beforeTime = GetCurrentTime(CLOCK_REALTIME);
	
	runTime = GetRunTime(beforeTime,7000,CLOCK_REALTIME);
	
	if(1 != SleepTime(runTime,CLOCK_REALTIME))
	{
		return FAILED;
	}
	
	afterTime = GetCurrentTime(CLOCK_REALTIME);
	
	if(7 != (afterTime.tv_sec - beforeTime.tv_sec))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestSleepTime_NotValid()
{
	if(0 == SleepTime((struct timespec){-1},CLOCK_REALTIME))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* COMPARE TIMES */

Result TestCompareTime_ValidT()
{
	struct timespec currentTime, runTime1, runTime2;
	
	currentTime = GetCurrentTime(CLOCK_REALTIME);
	
	runTime1 = GetRunTime(currentTime,13000,CLOCK_REALTIME);
	
	runTime2 = GetRunTime(currentTime,7000,CLOCK_REALTIME);
	
	if(!CompareTime(runTime2,runTime1))
	{
		return FAILED; 
	}
	
	return SUCCEDD;
}

Result TestCompareTime_ValidF()
{
	struct timespec currentTime, runTime1, runTime2;
	
	currentTime = GetCurrentTime(CLOCK_REALTIME);
	
	runTime1 = GetRunTime(currentTime,5000,CLOCK_REALTIME);
	
	runTime2 = GetRunTime(currentTime,7000,CLOCK_REALTIME);
	
	if(!CompareTime(runTime2,runTime1))
	{
		return SUCCEDD; 
	}
	
	return FAILED;
}

Result TestCompareTime_NotExistFirst()
{
	struct timespec currentTime, runTime;
	
	currentTime = GetCurrentTime(CLOCK_REALTIME);
	
	runTime = GetRunTime(currentTime,5000,CLOCK_REALTIME);
	
	if(!CompareTime((struct timespec){-1},runTime))
	{
		return SUCCEDD; 
	}
	
	return FAILED;
}

Result TestCompareTime_NotExistSecond()
{
	struct timespec currentTime, runTime;
	
	currentTime = GetCurrentTime(CLOCK_REALTIME);
	
	runTime = GetRunTime(currentTime,5000,CLOCK_REALTIME);
	
	if(!CompareTime(runTime,(struct timespec){-1}))
	{
		return SUCCEDD; 
	}
	
	return FAILED;
}

static void PrintRes(char *_str, Result(*ptrPrint)(void))
{
	static int count = 0;
	++count;
	
	printf("\n%d. %-40s \t %s \n", count, _str, (SUCCEDD == (*ptrPrint)()) ? "succedded" : "failed");
}

int main()
{

	/*Current time*/
	printf("\n--- Current time: ---\n");
	/*POS*/
	PrintRes("TestGetCurrentTime_Valid",TestGetCurrentTime_Valid);
	
	/*Run time*/
	printf("\n--- Run time: ---\n");
	/*POS*/
	PrintRes("TestGetRunTime_Valid",TestGetRunTime_Valid);
	/*NEG*/
	PrintRes("TestGetRunTime_NotValid",TestGetRunTime_NotValid);
	
	/*Sleep time*/
	printf("\n--- Sleep time: ---\n");
	/*POS*/
	PrintRes("TestSleepTime_Valid",TestSleepTime_Valid);
	/*NEG*/
	PrintRes("TestSleepTime_NotValid",TestSleepTime_NotValid);
	
	/*Compare times*/
	printf("\n--- Compare times: ---\n");
	/*POS*/
	PrintRes("TestCompareTime_ValidT",TestCompareTime_ValidT);
	PrintRes("TestCompareTime_ValidF",TestCompareTime_ValidF);
	/*NEG*/
	PrintRes("TestCompareTime_NotExistFirst",TestCompareTime_NotExistFirst);
	PrintRes("TestCompareTime_NotExistSecond",TestCompareTime_NotExistSecond);
	
	
	
	
	return 0;
}


