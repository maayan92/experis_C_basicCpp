#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#define SEC_VS_MILI 1000000
#define NANO_VS_MILI 1000

struct timespec GetCurrentTime()
{
	struct timespec startTime;
	
	clock_gettime(CLOCK_REALTIME, &startTime);
	
	return startTime;
}

double GetNextRunTime(struct timespec _startT, double _periodMs)
{
	struct timespec current = GetCurrentTime();
	
	double nsec = (current.tv_nsec - _startT.tv_nsec) / NANO_VS_MILI;/*TODO*/
	long sec = (current.tv_sec - _startT.tv_sec) * SEC_VS_MILI;
	
	return _periodMs + (sec + nsec) / SEC_VS_MILI;
}

double SleepTime(struct timespec _startT, double _nextTime)
{
	struct timespec current = GetCurrentTime();
	
	double runTime = ( _startT.tv_sec * SEC_VS_MILI + _startT.tv_nsec / NANO_VS_MILI) + _nextTime * SEC_VS_MILI;
	double currentMili = ( current.tv_sec * SEC_VS_MILI + current.tv_nsec / NANO_VS_MILI);

	return (runTime > currentMili) ? (runTime - currentMili) : 0;
}

int CompareTime(double _time1, double _time2)
{
	if((int)(_time1*SEC_VS_MILI) < (int)(_time2*SEC_VS_MILI))
	{
		return 1;
	}
	
	return 0;
}










