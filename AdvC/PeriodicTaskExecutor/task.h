#ifndef __TASK__
#define __TASK__

typedef struct Task Task;

typedef int (*TaskFunction)(void *);

/*
	Description: 
	Input: 
	Return value: 
*/
Task* TaskCreate(int (*_taskFunction)(void *), void* _context, size_t _periodMs);

/*
	Description: 
	Input: 
	Return value: 
*/
void TaskDestroy(Task *_task);

/*
	Description: 
	Input: 
	Return value: 
*/
int TaskRun(Task *_task);

/*
	Description: 
	Input: 
	Return value: 
*/
int CompareTasks(Task *_task1, Task *_task2);


#endif
