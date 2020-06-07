#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "../task.h"

typedef enum
{
	SUCCEDD,
	FAILED
}Result;


static int TaskAction(void *_context)
{
	static int count = 0;
	
	if(count < 3)
	{
		++count;
		
		return 1;
	}
	
	return 0;
}

/* CREATE TASK */

Result TestTaskCreate_Valid()
{
	Task *task = TaskCreate(TaskAction,(void*)'a',5000,CLOCK_REALTIME);
	if(!task)
	{
		return FAILED;
	}
	
	TaskDestroy(task);
	return SUCCEDD;
}

Result TestTaskCreate_NULLFunction()
{
	Task *task = TaskCreate(NULL,(void*)'a',5000,CLOCK_REALTIME);
	if(!task)
	{
		return SUCCEDD;
	}
	
	TaskDestroy(task);
	return FAILED;
}

/* DESTROY TASK */

Result TestTaskDestroy_Valid()
{
	Task *task = TaskCreate(TaskAction,(void*)'a',5000,CLOCK_REALTIME);
	if(!task)
	{
		return FAILED;
	}
	
	TaskDestroy(task);
	return SUCCEDD;
}

Result TestTaskDestroy_double()
{
	Task *task = TaskCreate(TaskAction,(void*)'a',5000,CLOCK_REALTIME);
	if(!task)
	{
		return FAILED;
	}
	
	TaskDestroy(task);
	TaskDestroy(task);
	return SUCCEDD;
}

Result TestTaskDestroy_NULL()
{
	TaskDestroy(NULL);
	return SUCCEDD;
}

/* GET START TIME */

Result TestTaskGetStartTime_Valid()
{
	struct timespec currentTime;
	
	Task *task = TaskCreate(TaskAction,(void*)'a',5000,CLOCK_REALTIME);
	if(!task)
	{
		return FAILED;
	}
	
	clock_gettime(CLOCK_REALTIME, &currentTime);
	
	if(currentTime.tv_sec != TaskGetStartTime(CLOCK_REALTIME).tv_sec)
	{
		TaskDestroy(task);
		return FAILED;
	}
	
	TaskDestroy(task);
	return SUCCEDD;
}

/* SET RUN TIME */

Result TestTaskSetRunTime_Valid()
{
	struct timespec currentTime;
	
	Task *task = TaskCreate(TaskAction,(void*)'a',5000,CLOCK_REALTIME);
	if(!task)
	{
		return FAILED;
	}
	
	clock_gettime(CLOCK_REALTIME, &currentTime);
	
	if(1 != TaskSetRunTime(task,&currentTime))
	{
		TaskDestroy(task);
		return FAILED;
	}
	
	TaskDestroy(task);
	return SUCCEDD;
}

Result TestTaskSetRunTime_NULLTask()
{
	struct timespec currentTime;
	
	clock_gettime(CLOCK_REALTIME, &currentTime);
	
	if(0 == TaskSetRunTime(NULL,&currentTime))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

Result TestTaskSetRunTime_NULLContext()
{
	Task *task = TaskCreate(TaskAction,(void*)'a',5000,CLOCK_REALTIME);
	if(!task)
	{
		return FAILED;
	}
	
	if(0 == TaskSetRunTime(task,NULL))
	{
		TaskDestroy(task);
		return SUCCEDD;
	}
	
	TaskDestroy(task);
	return FAILED;
}

/* RUN TASK */

Result TestTaskRun_Valid()
{
	char a = 'a';
	struct timespec currentTime, endTime;
	
	Task *task = TaskCreate(TaskAction,(void*)&a,5000,CLOCK_REALTIME);
	if(!task)
	{
		return FAILED;
	}
	
	clock_gettime(CLOCK_REALTIME, &currentTime);
	
	TaskSetRunTime(task,&currentTime);
	
	while(TaskRun(task)){}
	
	clock_gettime(CLOCK_REALTIME, &endTime);
	
	if(20 != (endTime.tv_sec - currentTime.tv_sec))
	{
		TaskDestroy(task);
		return FAILED;
	}
	
	TaskDestroy(task);
	return SUCCEDD;
}

Result TestTaskRun_NULL()
{
	if(0 == TaskRun(NULL))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* COMPARE TASKS */

Result TestCompareTasks_Valid()
{
	Task *task1, *task2;
	char a = 'a', b = 'b';
	struct timespec currentTime;
	
	task1 = TaskCreate(TaskAction,(void*)&a,5000,CLOCK_REALTIME);
	if(!task1)
	{
		return FAILED;
	}
	
	task2 = TaskCreate(TaskAction,(void*)&b,7000,CLOCK_REALTIME);
	if(!task2)
	{
		TaskDestroy(task1);
		return FAILED;
	}
	
	clock_gettime(CLOCK_REALTIME, &currentTime);
	
	TaskSetRunTime(task1,&currentTime);
	TaskSetRunTime(task2,&currentTime);
	
	if(1 != CompareTasks(task1,task2))
	{
		TaskDestroy(task1);
		TaskDestroy(task2);
		return FAILED;
	}
	
	TaskDestroy(task1);
	TaskDestroy(task2);
	return SUCCEDD;
}

Result TestCompareTasks_NULLTask2()
{
	Task *task = TaskCreate(TaskAction,(void*)'a',5000,CLOCK_REALTIME);
	if(!task)
	{
		return FAILED;
	}
	
	if(-1 == CompareTasks(task,NULL))
	{
		TaskDestroy(task);
		return SUCCEDD;
	}
	
	TaskDestroy(task);
	return FAILED;
}

Result TestCompareTasks_NULLTask1()
{
	Task *task = TaskCreate(TaskAction,(void*)'b',7000,CLOCK_REALTIME);
	if(!task)
	{
		return FAILED;
	}
	
	if(-1 == CompareTasks(NULL,task))
	{
		TaskDestroy(task);
		return SUCCEDD;
	}
	
	TaskDestroy(task);
	return FAILED;
}


static void PrintRes(char *_str, Result(*ptrPrint)(void))
{
	static int count = 0;
	++count;
	
	printf("\n%d. %-40s \t %s \n", count, _str, (SUCCEDD == (*ptrPrint)()) ? "succedded" : "failed");
}


int main()
{

	/*Create task*/
	printf("\n--- Create task: ---\n");
	/*POS*/
	PrintRes("TestTaskCreate_Valid",TestTaskCreate_Valid);
	/*NEG*/
	PrintRes("TestTaskCreate_NULLFunction",TestTaskCreate_NULLFunction);
	
	/*Destroy task*/
	printf("\n--- Destroy task: ---\n");
	/*POS*/
	PrintRes("TestTaskDestroy_Valid",TestTaskDestroy_Valid);
	/*NEG*/
	PrintRes("TestTaskDestroy_double",TestTaskDestroy_double);
	PrintRes("TestTaskDestroy_NULL",TestTaskDestroy_NULL);
	
	/*Start time*/
	printf("\n--- Start time: ---\n");
	/*POS*/
	PrintRes("TestTaskGetStartTime_Valid",TestTaskGetStartTime_Valid);
	
	/*Run time*/
	printf("\n--- Run time: ---\n");
	/*POS*/
	PrintRes("TestTaskSetRunTime_Valid",TestTaskSetRunTime_Valid);
	/*NEG*/
	PrintRes("TestTaskSetRunTime_NULLTask",TestTaskSetRunTime_NULLTask);
	PrintRes("TestTaskSetRunTime_NULLContext",TestTaskSetRunTime_NULLContext);

	/*Run task*/
	printf("\n--- Run task: ---\n");
	/*POS*/
	PrintRes("TestTaskRun_Valid",TestTaskRun_Valid);
	/*NEG*/
	PrintRes("TestTaskRun_NULL",TestTaskRun_NULL);

	/*Compare tasks*/
	printf("\n--- Compare tasks: ---\n");
	/*POS*/
	PrintRes("TestCompareTasks_Valid",TestCompareTasks_Valid);
	/*NEG*/
	PrintRes("TestCompareTasks_NULLTask2",TestCompareTasks_NULLTask2);
	PrintRes("TestCompareTasks_NULLTask1",TestCompareTasks_NULLTask1);




	return 0;
}







