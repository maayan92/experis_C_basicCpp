#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "time.h"

#define TASK_MAGIC_NUMBER 0xa1a1a1a1
#define TASK_NO_MAGIC_NUMBER 0xa0a0a0a0

#define IS_NOT_EXIST(_task) (NULL == _task || _task->m_magicNumber != TASK_MAGIC_NUMBER)

/*get the next run time*/
static void GetNextTime(Task *_task);

struct Task
{
	size_t m_magicNumber;
	TaskFunction m_taskFunction;
	size_t m_periodTime;
	void *m_context;
	struct timespec m_nextTime;
	clockid_t m_clockId;
};

Task* TaskCreate(TaskFunction _taskFunction, void* _context, size_t _periodMs, clockid_t _clkId)
{
	Task *task;
	
	if(!_taskFunction)
	{
		return NULL;
	}
	
	task = (Task*)malloc(sizeof(Task));
	if(!task)
	{
		return NULL;
	}
	
	task->m_taskFunction = _taskFunction;
	task->m_context = _context;
	task->m_periodTime = _periodMs;
	task->m_nextTime = (struct timespec){0};
	task->m_clockId = _clkId;
	task->m_magicNumber = TASK_MAGIC_NUMBER;
	
	return task;
}

void TaskDestroy(Task *_task)
{
	if(IS_NOT_EXIST(_task))
	{
		return;
	}
	
	_task->m_magicNumber = TASK_NO_MAGIC_NUMBER;
	free(_task);
}

struct timespec TaskGetStartTime(clockid_t _clockId)
{
	return GetCurrentTime(_clockId);
}

int TaskSetRunTime(void *_task, void *_context)
{
	if(IS_NOT_EXIST(((Task*)_task)) || !_context)
	{
		return false;
	}
	
	((Task*)_task)->m_nextTime = GetRunTime(*(struct timespec*)_context,((Task*)_task)->m_periodTime,((Task*)_task)->m_clockId);
	
	return true;
}

int TaskRun(Task *_task)
{
	int res;
	
	if(IS_NOT_EXIST(_task))
	{
		return false;
	}
	
	SleepTime(_task->m_nextTime,_task->m_clockId);
	
	res = _task->m_taskFunction(_task->m_context);
	
	GetNextTime(_task);
	
	return res;
}

int CompareTasks(const void *_task1, const void *_task2)
{
	if(IS_NOT_EXIST(((Task*)_task1)) || IS_NOT_EXIST(((Task*)_task2)))
	{
		return -1;
	}
	
	return CompareTime(((Task*)_task1)->m_nextTime,((Task*)_task2)->m_nextTime);
}

void PrintTask(Task *_task)
{
	printf("task %c period time %ld \n",*(char*)(_task->m_context), _task->m_periodTime);
	
	PrintTime(((Task*)_task)->m_nextTime);
}

/* SUB FUNCTIONS */

static void GetNextTime(Task *_task)
{
	struct timespec currentTime = GetCurrentTime(_task->m_clockId);

	_task->m_nextTime = GetRunTime(currentTime,_task->m_periodTime,_task->m_clockId);
}




