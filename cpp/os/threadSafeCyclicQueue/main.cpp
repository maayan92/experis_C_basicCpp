#include "cyclicQueueMT.hpp"
#include <pthread.h>
#include <iostream>
#include <unistd.h>

namespace experis {

static void TestCreateCyclicQueueMT() {

}

static void* RunThreadFirst(void* a_cyclicQueueMT) {
    int val5 = 5, val6 = 6;

    experis::CyclicQueueMT<5, int>* cQueue = static_cast<experis::CyclicQueueMT<5, int> *>(a_cyclicQueueMT);

    cQueue->AddNewElement(val5);
    cQueue->AddNewElement(val6);

    std::cout << "first --- free lock " << std::endl;
    std::cout << cQueue->RemoveElement() << std::endl;
    std::cout << cQueue->RemoveElement() << std::endl;
}

static void* RunThreadSecond(void* a_cyclicQueueMT) {
    int val1 = 1, val2 = 2, val3 = 3, val4 = 4;

    experis::CyclicQueueMT<5, int>* cQueue = static_cast<experis::CyclicQueueMT<5, int> *>(a_cyclicQueueMT);

    cQueue->AddNewElement(val1);
    cQueue->AddNewElement(val2);
    cQueue->AddNewElement(val3);
    cQueue->AddNewElement(val4);

    std::cout << "second --- free lock " << std::endl;
    std::cout << cQueue->RemoveElement() << std::endl;
    std::cout << cQueue->RemoveElement() << std::endl;
}

} // experis

int main() {
    experis::CyclicQueueMT<5, int> cyclicQueue;
    pthread_t threadFirst, threadSecond;
    pthread_create(&threadFirst, NULL, experis::RunThreadFirst, (void*)&cyclicQueue);
    pthread_create(&threadSecond, NULL, experis::RunThreadSecond, (void*)&cyclicQueue);

    pthread_join(threadFirst, NULL);
    pthread_join(threadSecond, NULL);

    return 0;
}