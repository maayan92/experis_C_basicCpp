#ifndef __CALCULATE_TIME__
#define __CALCULATE_TIME__

#include <unistd.h>
#include <time.h>
#include <sys/time.h>

enum { false, true };

/*
	Description: 
	Input: 
	Return value: 
*/
struct timespec GetCurrentTime();

/*
	Description: 
	Input: 
	Return value: 
*/
double GetNextRunTime(struct timespec _startT, size_t _periodMs);

/*
	Description: 
	Input: 
	Return value: 
*/
double SleepTime(struct timespec _startT, long _time);

/*
	Description: 
	Input: 
	Return value: 
*/
int CompareTime(double _time1, double _time2);


#endif
