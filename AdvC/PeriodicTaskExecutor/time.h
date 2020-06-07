#ifndef __CALCULATE_TIME__
#define __CALCULATE_TIME__

#include <unistd.h>
#include <time.h>
#include <sys/time.h>

enum { false, true };

/*
	Description: get the current time.
	Input: _clkId - clock type of clockid.
	Return value: return timespec of the current time, struct of -1 if it fails.
*/
struct timespec GetCurrentTime(clockid_t _clkId);

/*
	Description: get the run time by the start time and the period.
	Input: _startTime - the start time, _periodMs - period time, _clkId - clock type of clockid.
	Return value: return timespec of the run time, struct of -1 if it fails.
*/
struct timespec GetRunTime(struct timespec _startTime, size_t _periodMs, clockid_t _clkId);

/*
	Description: stop the running until time gets to _nextTime.
	Input: _nextTime - the next run time, _clkId - clock type of clockid.
	Return value: return 1 on success, or 0 if _nextTime isn't valid.
*/
size_t SleepTime(struct timespec _nextTime, clockid_t _clkId);

/*
	Description: compare two timespecs.
	Input: _time1 - first time to compare, _time2 - second time to compare.
	Return value: return true if _time1 < _time2, false if not or if one of the timespecs isn't valid.
*/
int CompareTime(struct timespec _time1, struct timespec _time2);

/*
	Description: print the time.
	Input: _time - the time to print.
	Return value: nothing returns.
*/
/*for debug only*/
void PrintTime(struct timespec _time);


#endif
