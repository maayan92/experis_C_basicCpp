#include <stdio.h>

#include "executor.h"

#define SIZE 3

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

static int TaskAction(void *_context)
{
	static int count = 0;
	
	if(count < 6)
	{
		++count;
		
		return 1;
	}
	
	return 0;
}

static Result FillExecutor(PeriodicExecutor *executor, int *_time, char *_context)
{
	int i;
	
	for(i = 0;i < SIZE;++i)
	{
		if(-1 == PeriodicExecutorAdd(executor,TaskAction,(void*)&_context[i],_time[i]))
		{
			return FAILED;
		}
	}
	
	return SUCCEDD;
}

/* CREATE EXECUTOR */

Result TestPeriodicExecutorCreate()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
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

/* INSERT TASK */

Result TestPeriodicExecutorAdd_Valid()
{
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	if(-1 == PeriodicExecutorAdd(executor,TaskAction,(void*)3,5))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	PeriodicExecutorDestroy(executor);
	return SUCCEDD;
}

/* RUN TASKS */

Result TestPeriodicExecutorRun_Valid()
{
	int time[] = {10,5,13};
	char context[] = {'a','c','b'};
	
	PeriodicExecutor *executor = PeriodicExecutorCreate("executor",CLOCK_REALTIME);
	if(!executor)
	{
		return FAILED;
	}
	
	if(FAILED == FillExecutor(executor,time,context))
	{
		PeriodicExecutorDestroy(executor);
		return FAILED;
	}
	
	if(0 == PeriodicExecutorRun(executor))
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
	printf("\n--- Create executor: ---\n");
	/*POS*/
	PrintRes("TestPeriodicExecutorCreate:",TestPeriodicExecutorCreate);

	/*Destroy executor*/
	printf("\n--- Destroy executor: ---\n");
	/*POS*/
	PrintRes("TestPeriodicExecutorDestroy_Valid:",TestPeriodicExecutorDestroy_Valid);
	/*NEG*/
	PrintRes("TestPeriodicExecutorDestroy_Double:",TestPeriodicExecutorDestroy_Double);
	PrintRes("TestPeriodicExecutorDestroy_NULLExe:",TestPeriodicExecutorDestroy_NULLExe);
	
	/*Add task*/
	printf("\n--- Add task: ---\n");
	/*POS*/
	PrintRes("TestPeriodicExecutorAdd_Valid:",TestPeriodicExecutorAdd_Valid);
	
	/*Run tasks*/
	printf("\n--- Run tasks: ---\n");
	/*POS*/
	PrintRes("TestPeriodicExecutorRun_Valid:",TestPeriodicExecutorRun_Valid);
	
	
	
	
	return 0;
}








