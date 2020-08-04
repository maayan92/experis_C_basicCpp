#include <iostream>
#include <pthread.h>
#include <semaphore.h>

volatile int global = 0;
sem_t semaphore;

#define NUM_OF_THREADS 2
#define RUN_TIMES 100000000

void* IncreaseGlobal(void* a_threadId) {
    for (size_t i = 0; i < RUN_TIMES; ++i) {
        sem_wait(&semaphore);
        ++global;
        sem_post(&semaphore);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_OF_THREADS];
    sem_init(&semaphore, 0, 1);
    
    for (size_t i = 0; i < NUM_OF_THREADS; ++i) {
        if(0 != pthread_create(&threads[i], NULL, IncreaseGlobal, (void*)i)) {
            std::cout << "thread create failed!" << std::endl;
            return 1;
        }
    }

    for (size_t i = 0; i < NUM_OF_THREADS; ++i) {
        if(0 != pthread_join(threads[i], NULL)) {
            std::cout << "thread join error!!" << std::endl;
            return 1;
        }
    }

    std::cout << "global value: " << global << std::endl;

    pthread_exit(NULL);
}