#include "cyclicQueueMT.hpp"
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

namespace experis {

typedef experis::CyclicQueueMT<5, int> Queue;

static void* AddElement(void* a_cyclicQueueMT) {
    int val = random() % 10;
    Queue* cQueue = static_cast<Queue*>(a_cyclicQueueMT);

    while(1) {
        try {
            sleep(2);
            cQueue->AddNewElement(val);
            std::cout << "add val -> " << val << std::endl;

        }catch(const std::exception& exc) {
            std::cout << exc.what() << std::endl;
        }
    }
}

static void* RemoveElement(void* a_cyclicQueueMT) {
    Queue* cQueue = static_cast<Queue*>(a_cyclicQueueMT);
    while(1) {
        try {
            sleep(2);
            std::cout << "removed val -> " << cQueue->RemoveElement() << std::endl;

        }catch(const std::exception& exc) {
            std::cout << exc.what() << std::endl;
        }
    }
}

} // experis

int main() {
    experis::CyclicQueueMT<5, int> cyclicQueue;
    pthread_t threadAdd1, threadAdd2, threadAdd3, threadAdd4, 
            threadRemove1, threadRemove2, threadRemove3, threadRemove4;
    pthread_create(&threadAdd1, NULL, experis::AddElement, (void*)&cyclicQueue);
    pthread_create(&threadAdd2, NULL, experis::AddElement, (void*)&cyclicQueue);
    pthread_create(&threadAdd3, NULL, experis::AddElement, (void*)&cyclicQueue);
    pthread_create(&threadAdd4, NULL, experis::AddElement, (void*)&cyclicQueue);

    pthread_create(&threadRemove1, NULL, experis::RemoveElement, (void*)&cyclicQueue);
    pthread_create(&threadRemove2, NULL, experis::RemoveElement, (void*)&cyclicQueue);
    pthread_create(&threadRemove3, NULL, experis::RemoveElement, (void*)&cyclicQueue);
    pthread_create(&threadRemove4, NULL, experis::RemoveElement, (void*)&cyclicQueue);

    pthread_join(threadAdd1, NULL);
    pthread_join(threadAdd2, NULL);
    pthread_join(threadAdd3, NULL);
    pthread_join(threadAdd4, NULL);

    pthread_join(threadRemove1, NULL);
    pthread_join(threadRemove2, NULL);
    pthread_join(threadRemove3, NULL);
    pthread_join(threadRemove4, NULL);

    return 0;
}