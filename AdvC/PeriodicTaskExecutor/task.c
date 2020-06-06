#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "time.h"

#define TASK_MAGIC_NUMBER 0xa1a1a1a1
#define TASK_NO_MAGIC_NUMBER 0xa0a0a0a0

#define IS_NOT_EXIST(_task) (NULL == _task || _task->m_magicNumber != TASK_MAGIC_NUMBER)


struct Task
{
	size_t m_magicNumber;
	TaskFunction m_taskFunction;
	size_t m_periodTime;
	double m_nextTime;
	struct timespec m_startTime;
	void *m_context;
};

Task* TaskCreate(TaskFunction _taskFunction, void* _context, size_t _periodMs)
{
	Task *task = (Task*)malloc(sizeof(Task));
	if(!task)
	{
		return NULL;
	}
	
	task->m_taskFunction = _taskFunction;
	task->m_periodTime = _periodMs;
	task->m_nextTime = _periodMs;
	task->m_context = _context;
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

int SetFirstTime(void *_task, void *_context)
{
	((Task*)_task)->m_startTime = GetCurrentTime();
	
	/*((Task*)_task)->m_nextTime = GetNextRunTime(((Task*)_task)->m_startTime,((Task*)_task)->m_periodTime);*/
	
	return 1;
}

static void GetNextTime(Task *_task)
{
	_task->m_nextTime = GetNextRunTime(_task->m_startTime,(double)(_task->m_periodTime));
}

int TaskRun(Task *_task)
{
	int res;
	
	if(IS_NOT_EXIST(_task))
	{
		return 0;
	}
	
	printf("sleep -> %f \n", SleepTime(_task->m_startTime,_task->m_nextTime));
	
	usleep(SleepTime(_task->m_startTime,_task->m_nextTime));
	
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

void PrintTime(void *_task)
{
	printf("task %c next time -> %f \n",*(char*)(((Task*)_task)->m_context), ((Task*)_task)->m_nextTime);
}






