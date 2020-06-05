#include <stdio.h>

#include "executor.h"

#define SIZE 7

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

static int TaskAction(void *_context)
{
	if(*(int*)_context > 0)
	{
		++*(int*)_context;
		
		return 1;
	}
	
	return 0;
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
	
	
	
	
	
	
	return 0;
}








