#ifndef __TASK__
#define __TASK__

typedef struct Task Task;

typedef int (*TaskFunction)(void *);

/*
	Description: create a new task.
	Input: _taskFunction - task function action, _context - the task context, _periodMs - period run time.
	Return value: return pointer to the new task, NULL if _taskFunction is NULL or the allocation fails. 
*/
Task* TaskCreate(TaskFunction _taskFunction, void* _context, size_t _periodMs, clockid_t _clkId);

/*
	Description: destroy the task.
	Input: _task - pointer to the task.
	Return value: nothing returns.
*/
void TaskDestroy(Task *_task);

/*
	Description: get the start time by the current time.
	Input: _clockId - clock id type.
	Return value: return timespec of the current time.
*/
struct timespec TaskGetStartTime(clockid_t _clockId);

/*
	Description: set the start time and the run time at start point.
	Input: _task - pointer to the task, _context - the start time.
	Return value: return false if _task or _context isn't exist, true on success.
*/
int TaskSetRunTime(void *_task, void *_context);

/*
	Description: run the task at its right time.
	Input:  _task - pointer to the task.
	Return value: return true to continue running the task, false to stop or if the _task isn't exist.
*/
int TaskRun(Task *_task);

/*
	Description: compare two tasks.
	Input: _task1 - pointer to the first task, _task2 - pointer to the first task.
	Return value: return 1 if _task1 < _task2, 0 if not or -1 if one of the tasks are not exist.
*/
int CompareTasks(const void *_task1, const void *_task2);

/*
	Description: print the task.
	Input: _task - pointer to the first task.
	Return value: 
*/
/*for debug only*/
void PrintTask(Task *_task);

#endif
