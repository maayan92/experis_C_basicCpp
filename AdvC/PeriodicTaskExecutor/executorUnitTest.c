#include <stdio.h>

#include "executor.h"

#define SIZE 3

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

static int TaskActionRealTime(void *_context)
{
	static int count = 0;
	
	return (count < 6) ? (++count) : 0;
}

static int TaskActionCoarse(void *_context)
{
	static int count = 0;
	
	return (count < 6) ? (++count) : 0;
}

static int TaskActionMonotonic(void *_context)
{
	static int count = 0;
	
	return (count < 6) ? (++count) : 0;
}

static int TaskActionAddTask(void *_context)
{
	static int count = 0;
	
	return (count < 4) ? (++count) : 0;
}

static int TaskActionWithPause(void *_context)
{
	static int count = 0;
	
	return (count < 4) ? (++count) : 0;
}

static int TaskActionZeroPeriod(void *_context)
{
	static int count = 0;
	
	return (count < 4) ? (++count) : 0;
}

static int AddNewTaskAction(void *_context)
{
	char d = 'd';
	
	if(SUCCESS != PeriodicExecutorAdd((PeriodicExecutor*)_context,TaskActionAddTask,(void*)&d,15000))
	{
		return PeriodicExecutorPause((PeriodicExecutor*)_context);
	}
	
	return 0;
}

static int TaskActionPause(void *_context)
{
	PeriodicExecutorPause((PeriodicExecutor*)_context);

	return 0;
}

static Result FillExecutor(PeriodicExecutor *_executor, int (*_taskFunction)(void *), int *_time, char *_context, int _size)
{
	int i;
	
	for(i = 0;i < _size;++i)
	{
		if(SUCCESS != PeriodicExecutorAdd(_executor,_taskFunction,(void*)&_context[i],_time[i]))
		{
			return FAILED;
		}
	}
	
	return SUCCEDD;
}

/* CREATE EXECUTOR */

Result TestPeriodicExecutorCreate_Valid()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorCreate_EmptyName()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate("",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorCreate_NULLName()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate(NULL,CLOCK_REALTIME);
	if(!executor)
	{
		return SUCCEDD;
	}
	
	PeriodicExecutorDestroy(executor);
	return FAILED;
}

/* DESTROY EXECUTOR */

Result TestPeriodicExecutorDestroy_Valid()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorDestroy_Double()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorDestroy_NULLExe()
{
	PeriodicExecutorDestroy(NULL);
	return SUCCEDD;
}

/* ADD TASK */

Result TestPeriodicExecutorAdd_ValidRealTime()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	if(SUCCESS != PeriodicExecutorAdd(executor,TaskActionRealTime,(void*)3,5000))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorAdd_ValidCoarse()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME_COARSE);
	if(!executor)
	{
		return FAILED;
	}
	
	if(SUCCESS != PeriodicExecutorAdd(executor,TaskActionCoarse,(void*)3,5000))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorAdd_ValidMonotonic()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_MONOTONIC);
	if(!executor)
	{
		return FAILED;
	}
	
	if(SUCCESS != PeriodicExecutorAdd(executor,TaskActionMonotonic,(void*)3,5000))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorAdd_NULL()
{
	if(NOT_EXIST == PeriodicExecutorAdd(NULL,TaskActionRealTime,(void*)3,5000))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* RUN TASKS */

Result TestPeriodicExecutorRun_ValidRealTime()
{
	int time[] = {10000,5000,13000};
	char context[] = {'a','c','b'};
	
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	if(FAILED == FillExecutor(executor,TaskActionRealTime,time,context,SIZE))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	if(9 != PeriodicExecutorRun(executor))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorRun_ValidCoarse()
{
	int time[] = {10000,5000,13000};
	char context[] = {'a','c','b'};
	
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME_COARSE);
	if(!executor)
	{
		return FAILED;
	}
	
	if(FAILED == FillExecutor(executor,TaskActionCoarse,time,context,SIZE))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	if(9 != PeriodicExecutorRun(executor))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorRun_ValidMonotonic()
{
	int time[] = {10000,5000,13000};
	char context[] = {'a','c','b'};
	
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_MONOTONIC);
	if(!executor)
	{
		return FAILED;
	}
	
	if(FAILED == FillExecutor(executor,TaskActionMonotonic,time,context,SIZE))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	if(9 != PeriodicExecutorRun(executor))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorRun_ValidAddTask()
{
	int time[] = {10000,5000,7000};
	char context[] = {'a','c','b'};
	
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	if(FAILED == FillExecutor(executor,TaskActionAddTask,time,context,SIZE-1))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	if(SUCCESS != PeriodicExecutorAdd(executor,AddNewTaskAction,(void*)executor,time[2]))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	if(8 != PeriodicExecutorRun(executor))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

Result TestPeriodicExecutorRun_ValidZeroPeriod()
{
	int time[] = {10000,5000,13000};
	char context[] = {'a','c','b'};
	
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	if(FAILED == FillExecutor(executor,TaskActionZeroPeriod,time,context,SIZE-1))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	if(SUCCESS != PeriodicExecutorAdd(executor,TaskActionZeroPeriod,(void*)&context[2],0))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	if(7 != PeriodicExecutorRun(executor))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}


Result TestPeriodicExecutorRun_NULL()
{
	if(0 == PeriodicExecutorRun(NULL))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* RUS AND PAUSE */

Result TestPeriodicExecutorPause_Valid()
{
	int time[] = {10000,5000,7000};
	char context[] = {'a','c','b'};
	
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	if(FAILED == FillExecutor(executor,TaskActionWithPause,time,context,SIZE))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	if(SUCCESS != PeriodicExecutorAdd(executor,TaskActionPause,(void*)executor,6000))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
		
	if(2 != PeriodicExecutorRun(executor) || 6 != PeriodicExecutorRun(executor))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

static void PrintRes(char *_str, Result(*ptrPrint)(void))
{
	static int count = 0;
	++count;
	
	printf("\n%d. %-40s \t %s \n", count, _str, (SUCCEDD == (*ptrPrint)()) ? "succedded" : "failed");
}


int main()
{

	/*Create executor*/
	/*POS*/printf("\n--- Create executor: ---\n");
	PrintRes("TestPeriodicExecutorCreate_Valid:",TestPeriodicExecutorCreate_Valid);
	PrintRes("TestPeriodicExecutorCreate_EmptyName:",TestPeriodicExecutorCreate_EmptyName);
	/*NEG*/
	PrintRes("TestPeriodicExecutorCreate_NULLName:",TestPeriodicExecutorCreate_NULLName);

	/*Destroy executor*/
	/*POS*/printf("\n--- Destroy executor: ---\n");
	PrintRes("TestPeriodicExecutorDestroy_Valid:",TestPeriodicExecutorDestroy_Valid);
	/*NEG*/
	PrintRes("TestPeriodicExecutorDestroy_Double:",TestPeriodicExecutorDestroy_Double);
	PrintRes("TestPeriodicExecutorDestroy_NULLExe:",TestPeriodicExecutorDestroy_NULLExe);
	
	/*Add task*/
	/*POS*/printf("\n--- Add task: ---\n");
	PrintRes("TestPeriodicExecutorAdd_ValidRealTime:",TestPeriodicExecutorAdd_ValidRealTime);
	PrintRes("TestPeriodicExecutorAdd_ValidCoarse:",TestPeriodicExecutorAdd_ValidCoarse);
	PrintRes("TestPeriodicExecutorAdd_ValidMonotonic:",TestPeriodicExecutorAdd_ValidMonotonic);
	/*NEG*/
	PrintRes("TestPeriodicExecutorAdd_NULL:",TestPeriodicExecutorAdd_NULL);
		
	/*Run tasks*/
	/*POS*/printf("\n--- Run tasks: ---\n");
	PrintRes("TestPeriodicExecutorRun_ValidRealTime:",TestPeriodicExecutorRun_ValidRealTime);
	PrintRes("TestPeriodicExecutorRun_ValidCoarse:",TestPeriodicExecutorRun_ValidCoarse);
	PrintRes("TestPeriodicExecutorRun_ValidMonotonic:",TestPeriodicExecutorRun_ValidMonotonic);
	PrintRes("TestPeriodicExecutorRun_ValidAddTask:",TestPeriodicExecutorRun_ValidAddTask);
	PrintRes("TestPeriodicExecutorRun_ValidZeroPeriod:",TestPeriodicExecutorRun_ValidZeroPeriod);
	/*NEG*/
	PrintRes("TestPeriodicExecutorRun_NULL:",TestPeriodicExecutorRun_NULL);
	
	/*Run and pause*/
	/*POS*/printf("\n--- Run and pause: ---\n");
	PrintRes("TestPeriodicExecutorPause_Valid:",TestPeriodicExecutorPause_Valid);
	
	return 0;
}



