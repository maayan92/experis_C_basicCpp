#include <stdio.h>
#include <pthread.h>

#define NUM_OF_THREADS 100

int g_var = 0;

static void* PrintFunc(void* tid)
{
	int i, l_var = 0;
	
	for(i = 0;i < 1000;++i)
	{
		++l_var;
		++g_var;
		
		printf("thread num -> %ld , g_var -> %d , l_var -> %d \n", (size_t)tid, g_var, l_var);
	}
	pthread_exit(0);
}



int main()
{
	int status;
	size_t i;
	pthread_t threads[NUM_OF_THREADS];
	
	for(i = 0;i < NUM_OF_THREADS;++i)
	{
		status = pthread_create(&threads[i],NULL,PrintFunc, (void*)i);
		
		if(status)
		{
			printf("failed");
		}
	}
	
	for(i = 0;i < NUM_OF_THREADS;++i)
	{
		pthread_join(threads[i],NULL);
	}



	return 0;
}
