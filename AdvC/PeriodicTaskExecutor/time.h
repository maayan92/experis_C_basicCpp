#ifndef __CALCULATE_TIME__
#define __CALCULATE_TIME__

#include <unistd.h>
#include <time.h>
#include <sys/time.h>

/*
	Description: 
	Input: 
	Return value: 
*/
struct timespec* GetCurrentTime();

/*
	Description: 
	Input: 
	Return value: 
*/
long GetNextRunTime(struct timespec *_startT, size_t _periodMs);

/*
	Description: 
	Input: 
	Return value: 
*/
long SleepTime(struct timespec *_startT, long _time);


#endif
