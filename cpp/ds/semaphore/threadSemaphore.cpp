#include <iostream>
#include <pthread.h>
#include "semaphore.hpp"

volatile int global = 0;
experis::Semaphore semaphoreBinary;

#define NUM_OF_THREADS 2
#define RUN_TIMES 100000000

void* IncreaseGlobal(void* a_threadId) {
    for (size_t i = 0; i < RUN_TIMES; ++i) {
        try {
            semaphoreBinary.Wait();
            ++global;
            semaphoreBinary.Post();
        }catch(const std::exception& exc) {
            std::cout << exc.what() << std::endl;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_OF_THREADS];

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