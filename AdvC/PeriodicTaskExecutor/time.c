#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#define IS_TIMESPEC_NOT_VALID(_timespec) (0 > _timespec.tv_sec || 0 > _timespec.tv_nsec)

enum
{
	NANO_VS_MILI = 1000,
	SEC_VS_MILI = 1000000,
	NANO_VS_SEC  = 1000000000
};

/*order the sec and nsec if nsec to big*/
static struct timespec ReorderSecNsec(struct timespec _startTime);


struct timespec GetCurrentTime(clockid_t _clkId)
{
	struct timespec currentTime;
	
	if(-1 == clock_gettime(_clkId, &currentTime))
	{
		return (struct timespec){-1};
	}
	
	return currentTime;
}

struct timespec GetRunTime(struct timespec _startTime, size_t _periodMs, clockid_t _clkId)
{
	if(IS_TIMESPEC_NOT_VALID(_startTime))
	{
		return (struct timespec){-1};
	}
	
	_startTime.tv_nsec += (_periodMs % NANO_VS_MILI) * SEC_VS_MILI;
	_startTime.tv_sec += _periodMs / NANO_VS_MILI;
	
	ReorderSecNsec(_startTime);
	
	return _startTime;
}

size_t SleepTime(struct timespec _nextTime, clockid_t _clkId)
{
	struct timespec current = GetCurrentTime(_clkId);
	
	if(IS_TIMESPEC_NOT_VALID(_nextTime))
	{
		return 0;
	}

	size_t runTime = _nextTime.tv_sec * SEC_VS_MILI + _nextTime.tv_nsec / NANO_VS_MILI;
	size_t currentMili = current.tv_sec * SEC_VS_MILI + current.tv_nsec / NANO_VS_MILI;
	
	usleep((runTime > currentMili) ? (runTime - currentMili) : 0);
	
	return 1;
}

int CompareTime(struct timespec _time1, struct timespec _time2)
{
	if(IS_TIMESPEC_NOT_VALID(_time1) || IS_TIMESPEC_NOT_VALID(_time2))
	{
		return 0;
	}

	size_t miliTime1 = _time1.tv_sec * SEC_VS_MILI + _time1.tv_nsec / NANO_VS_MILI;
	size_t miliTime2 = _time2.tv_sec * SEC_VS_MILI + _time2.tv_nsec / NANO_VS_MILI;
	
	if(miliTime1 < miliTime2)
	{
		return 1;
	}
	
	return 0;
}

void PrintTime(struct timespec _time)
{
	printf("time sec %ld all %ld \n", _time.tv_sec , _time.tv_nsec );
}

/* SUB FUNCTIONS */

static struct timespec ReorderSecNsec(struct timespec _startTime)
{
	while(_startTime.tv_nsec > NANO_VS_SEC)
	{
		_startTime.tv_nsec -= NANO_VS_SEC;
		++_startTime.tv_sec;
	}
	
	return _startTime;
}






