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
	Vector *m_vec;
	size_t m_isPaused;
};

/*call the task destroy function*/
static void DestroyTask(void *_task);
/*set the start time and create the heap*/
static Heap* SetStartTimeCreateHeap(PeriodicExecutor* _executor);
/*run all the tasks, untill they over or paused occurred*/
static size_t RunAllTasks(PeriodicExecutor* _executor, Heap *heap);


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
	executor->m_isPaused = 0;
	executor->m_magicNumber = EXECUTOR_MAGIC_NUMBER;
	
	return executor;
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
	
	_executor->m_magicNumber = EXECUTOR_NO_MAGIC_NUMBER;
	free(_executor);
}

int PeriodicExecutorAdd(PeriodicExecutor* _executor, TaskFunction _taskFunction, void* _context, size_t _periodMs)
{
	Task *task;
	
	if(IS_NOT_EXIST(_executor) || NULL == _taskFunction)
	{
		return -1;
	}
	
	task = TaskCreate(_taskFunction,_context,_periodMs,_executor->m_clockId);
	if(NULL == task)
	{
		return -1;
	}
	
	if(SUCCEEDED != VectorAddTail(_executor->m_vec,task))
	{
		return -1;
	}
	
	 return 1;
}

size_t PeriodicExecutorRun(PeriodicExecutor* _executor)
{
	Heap *heap;
	
	if(IS_NOT_EXIST(_executor))
	{
		return 0;
	}
	
	heap = SetStartTimeCreateHeap(_executor);
	
	if(NULL == heap)
	{
		return 0;
	}
	
	_executor->m_isPaused = 0;
	
	return RunAllTasks(_executor,heap);
}

size_t PeriodicExecutorPause(PeriodicExecutor* _executor)
{
	if(IS_NOT_EXIST(_executor))
	{
		return 0;
	}

	_executor->m_isPaused = 1;

	return VectorNumOfelements(_executor->m_vec);
}

/* SUB FUNCTION */

static void DestroyTask(void *_task)
{
	TaskDestroy((Task*)_task);
}

static Heap* SetStartTimeCreateHeap(PeriodicExecutor* _executor)
{
	int countElements;
	struct timespec startTime;
	Heap *heap;
	
	startTime = TaskGetStartTime(_executor->m_clockId);
	if(-1 == startTime.tv_sec)
	{
		return NULL;
	}
	
	countElements = VectorForEach(_executor->m_vec,TaskSetRunTime,(void*)&startTime);
	
	if(countElements != VectorNumOfelements(_executor->m_vec))
	{
		return NULL;
	}
	
	heap = HeapBuild(_executor->m_vec,CompareTasks);
	if(NULL == heap)
	{
		return NULL;
	}
	
	return heap;
}

static size_t RunAllTasks(PeriodicExecutor* _executor, Heap *heap)
{
	Task *currentTask;
	size_t count = 0;
	
	while(HeapItemsNum(heap) && 0 == _executor->m_isPaused)
	{
		currentTask = (Task*)HeapExtract(heap);

		if(TaskRun(currentTask))
		{
			HeapInsert(heap,currentTask);
		}
		
		++count;
	}
	
	HeapDestroy(&heap);
	
	return count;
}




