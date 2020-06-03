#include <stdio.h>
#include <semaphore.h> 
#include <pthread.h>
#include <unistd.h> 

#define N 100
#define PRODUCERS_NUM 2
#define CONSUMERS_NUM 5

sem_t mutex;
sem_t empty;
sem_t full;
int count = 0;

void* Producer(void* _pid)
{
	while(1)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		/*cs*/
		++count;
		printf("produce %ld -> %d \n", (size_t)_pid, count);
		/*end cs*/
		sem_post(&mutex);
		sem_post(&full);
	}
}

void* Consumer(void* _pid)
{
	while(1)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		/*cs*/
		--count;
		printf("consume %ld -> %d \n", (size_t)_pid, count);
		/*end cs*/
		sem_post(&mutex);
		sem_post(&empty);
	}
}

int main()
{
	pthread_t producer[PRODUCERS_NUM],consumer[CONSUMERS_NUM];
	size_t i;

	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);

	for(i = 0;i < PRODUCERS_NUM;++i)
	{
		pthread_create(&producer[i],NULL,Producer,(void*)i);
	}
	
	for(i = 0;i < CONSUMERS_NUM;++i)
	{
		pthread_create(&consumer[i],NULL,Consumer,(void*)i);
	}
	
	for(i = 0;i < PRODUCERS_NUM;++i)
	{
		pthread_join(producer[i],NULL);
	}
	
	for(i = 0;i < CONSUMERS_NUM;++i)
	{
		pthread_join(consumer[i],NULL);
	}
	
	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;
}










