#ifndef __EXECUTER__
#define __EXECUTER__

#include <unistd.h>
#include <time.h> 
#include <sys/types.h>

enum { true,false };

typedef struct PeriodicExecutor PeriodicExecutor;

/*
	Description: create a new periodic executor.
	Input: _name - name of executor, should not be NULL, _clkId - the id of the system clock to be used.
	Return value: return pointer to the periodic executor, NULL if _name is NULL or if the allocation fails.
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
	Description: run all the tasks, untill they over or paused.
	Input: _executor - pointer to the periodic executor.
	Return value: return the number of execution cycles performed.
*/
size_t PeriodicExecutorRun(PeriodicExecutor* _executor);

/*
	Description: pause the running of all tasks.
	Input: _executor - pointer to the periodic executor.
	Return value: return the number of tasks remaining inside the executor.
*/
size_t PeriodicExecutorPause(PeriodicExecutor* _executor);

/*
	Description: print the executor.
	Input:  _executor - pointer to the periodic executor.
	Return value: nothing returns.
*/
/*for debug only*/
void PrintExecutor(PeriodicExecutor* _executor);

#endif
