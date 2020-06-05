#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>


struct timespec* GetCurrentTime()
{
	struct timespec *startTime = (struct timespec *)malloc(sizeof(struct timespec));
	
	if(!startTime)
	{
		return NULL;
	}
	
	clock_gettime(CLOCK_REALTIME, startTime); 
	
	return startTime;
}


double GetNextRunTime(struct timespec *_startT, size_t _periodMs)
{
	struct timespec *current = GetCurrentTime();
	
	double nextText = (current->tv_sec - _startT->tv_sec) + _periodMs;
	
	free(current);
	
	return nextText; 
}


double SleepTime(struct timespec *_startT, long _time)
{
	struct timespec *current = GetCurrentTime();
	
	double nextText = (_startT->tv_sec + _time) - current->tv_sec;
	
	free(current);
	
	return nextText;
}

int CompareTime()
{
	
}


