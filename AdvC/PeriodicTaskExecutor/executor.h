#ifndef __EXECUTER__
#define __EXECUTER__

#include <unistd.h>
#include <time.h> 
#include <sys/types.h>
/*
typedef enum
{
	CLOCK_REALTIME,
	CLOCK_REALTIME_COARSE,
	CLOCK_MONOTONIC
}clockid_t;
*/
enum { true,false };

typedef struct PeriodicExecutor PeriodicExecutor; 

/*
	Description: create a new periodic executor.
	Input: _name - name TODO,  _clkId - the id of the system clock to be used.
	Return value: return pointer to the periodic executor.
*/
PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clkId);

/*
	Description: destroy the periodic executor.
	Input: _executor - pointer to the periodic executor.
	Return value: nothing returns.
*/
void PeriodicExecutorDestroy(PeriodicExecutor* _executor);

/*
	Description: add a new task to the periodic executor.
	Input: _executor - pointer to the periodic executor, _taskFunction - the task function, 
		_context - context to send to the task function, _periodMs - the period of recurrence in milliseconds.
	Return value: return false if the _executor isn't exist or if allocation fails, true on success.
*/
int PeriodicExecutorAdd(PeriodicExecutor* _executor, int (*_taskFunction)(void *), void* _context, size_t _periodMs);

/*
	Description: run all the tasks.
	Input: _executor - pointer to the periodic executor.
	Return value: return the number of execution cycles performed.
*/
size_t PeriodicExecutorRun(PeriodicExecutor* _executor);

/*
	Description: pause the running of all tasks.
	Input: _executor - pointer to the periodic executor.
	Return value: 
*/
size_t PeriodicExecutorPause(PeriodicExecutor* _executor);

/*
	Description: 
	Input: 
	Return value: 
*/



#endif
