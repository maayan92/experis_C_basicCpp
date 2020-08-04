#include <iostream>
#include <pthread.h>

#define NUM_OF_THREADS 100000

void* PrintHello(void *a_threadId) {
    std::cout << "hello! -> " << *((size_t*)&a_threadId) << std::endl;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_OF_THREADS];
    size_t j = 0;
    for (size_t i = 0; i < NUM_OF_THREADS; ++i) {
        if(0 != pthread_create(&threads[i], NULL, PrintHello, (void*)i)) {
            for( j = j + 1 ; j < i ; ++j) {
                if(0 != pthread_join(threads[j], NULL)) {
                    std::cout << "thread join error!!" << std::endl;
                    return 1;
                }
            }
        }
    }
    
    for (j = j + 1; j < NUM_OF_THREADS; ++j) {
        if(0 != pthread_join(threads[j], NULL)) {
            std::cout << "thread join error!!" << std::endl;
            return 1;
        }
    }

    pthread_exit(NULL);
    return 0;
}