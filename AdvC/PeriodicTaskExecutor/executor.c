#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "executor.h"
#include "task.h"
#include "heap.h"

#define EXECUTOR_MAGIC_NUMBER 0xeeeecccc
#define EXECUTOR_NO_MAGIC_NUMBER 0xe0e0c0c0

#define VECTOR_SIZE 10
#define VECTOR_BLOCK_S 5
#define LENGTH 20

#define IS_NOT_EXIST(_executor) (NULL == _executor || _executor->m_magicNumber != EXECUTOR_MAGIC_NUMBER)

struct PeriodicExecutor
{
	size_t m_magicNumber;
	char m_name[LENGTH];	
	clockid_t m_clockId;
	Heap *m_heap;
	Vector *m_vec;
	size_t m_isPaused;
};

PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clkId)
{

	PeriodicExecutor *executor = (PeriodicExecutor*)malloc(sizeof(PeriodicExecutor));
	if(NULL == executor)
	{
		return NULL;
	}
	
	executor->m_vec = VectorCreate(VECTOR_SIZE,VECTOR_BLOCK_S);
	if(NULL == executor->m_vec)
	{
		free(executor);
		return NULL;
	}

	strcpy(executor->m_name,_name);
	executor->m_clockId = _clkId;
	executor->m_heap = NULL;
	executor->m_isPaused = 0;
	executor->m_magicNumber = EXECUTOR_MAGIC_NUMBER;
	
	return executor;
}

static void DestroyTask(void *_task)
{
	TaskDestroy((Task*)_task);
}

void PeriodicExecutorDestroy(PeriodicExecutor* _executor)
{
	if(IS_NOT_EXIST(_executor))
	{
		return;	
	}
	
	if(_executor->m_vec)
	{
		VectorDestroy(_executor->m_vec,DestroyTask);
	}
	
	if(_executor->m_heap)
	{
		HeapDestroy(&_executor->m_heap);
	}
	
	_executor->m_magicNumber = EXECUTOR_NO_MAGIC_NUMBER;
	free(_executor);
}

int PeriodicExecutorAdd(PeriodicExecutor* _executor, TaskFunction _taskFunction, void* _context, size_t _periodMs)
{
	Task *task;
	
	if(IS_NOT_EXIST(_executor))
	{
		return -1;
	}
	
	task = TaskCreate(_taskFunction,_context,_periodMs);
	if(NULL == task)
	{
		return -1;
	}
	
	if(_executor->m_heap)
	{
		if(SUCCEEDED != HeapInsert(_executor->m_heap,task))
		{
			return -1;
		}
		
		return 1;
	}
	
	if(SUCCEEDED != VectorAddTail(_executor->m_vec,task))
	{
		return -1;
	}
	
	 return 1;
}

static size_t RunAllTasks(PeriodicExecutor* _executor)
{
	Task *currentTask;
	size_t count = 0;
	
	while(HeapItemsNum(_executor->m_heap) && 0 == _executor->m_isPaused)
	{
		currentTask = (Task*)HeapExtract(_executor->m_heap);

		PrintTime(currentTask);/*print*/
		
		if(TaskRun(currentTask))
		{
			HeapInsert(_executor->m_heap,currentTask);
		}
		
		++count;
	}
	
	return count;
}

static size_t CreateHeapIfNotExist(PeriodicExecutor* _executor)
{
	if(NULL == _executor->m_heap)
	{
		_executor->m_heap = HeapBuild(_executor->m_vec,CompareTasks);
		if(NULL != _executor->m_heap)
		{
			return 0;
		}
	}
	
	return 1;
}

size_t PeriodicExecutorRun(PeriodicExecutor* _executor)
{
	int countElements;
	
	if(IS_NOT_EXIST(_executor))
	{
		return 0;
	}
	
	countElements = VectorForEach(_executor->m_vec,SetFirstTime,NULL);
	
	if(countElements != VectorNumOfelements(_executor->m_vec))
	{
		return 0;
	}
	
	CreateHeapIfNotExist(_executor);
	
	_executor->m_isPaused = 0;
	
	HeapPrint(_executor->m_heap,PrintTime);
	
	return RunAllTasks(_executor);;
}

size_t PeriodicExecutorPause(PeriodicExecutor* _executor)
{
	if(IS_NOT_EXIST(_executor))
	{
		return 0;	
	}

	return _executor->m_isPaused = 1;
}








