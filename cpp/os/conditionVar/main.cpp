#include "conditionVariable.hpp"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

typedef experis::ConditionVariable ConditionVariable;

namespace experis {

int g_starTimes = 0;
Mutex g_mutex;

void PrintStar(ConditionVariable& a_conditionVariable) {
    //g_mutex.Lock();
    while (!g_starTimes) {
        MutexLocker mLocker(g_mutex);
        a_conditionVariable.Wait(mLocker);
        std::cout << "vvv  lock" << std::endl;
    }
    --g_starTimes;
    g_mutex.Unlock();

    std::cout << "*" << std::endl;
}

void AddStar(ConditionVariable& a_conditionVariable) {
    std::cout << "add --- lock" << std::endl;
    g_mutex.Lock();
    ++g_starTimes;
    g_mutex.Unlock();
    a_conditionVariable.NotifyAll();
}

void *PrintLooper(void* a_conditionVariable) {
    while (1) {
        //sleep(random() % 10);
        PrintStar(*(static_cast<ConditionVariable*>(a_conditionVariable)));
    }

    return NULL;
}

void *AddLooper(void* a_conditionVariable) {
    while (1) {
        //sleep(random() % 10);
        AddStar(*(static_cast<ConditionVariable*>(a_conditionVariable)));
    }

    return NULL;
}

} // experis

int main() {

    try {
        ConditionVariable conditionVariable;

        pthread_t threadPrint1, threadPrint2, threadPrint3, threadPrint4,
                    threadAdd1, threadAdd2, threadAdd3 , threadAdd4;

        pthread_create(&threadPrint1, NULL, experis::PrintLooper,NULL);
        pthread_create(&threadPrint2, NULL, experis::PrintLooper,NULL);
        pthread_create(&threadPrint3, NULL, experis::PrintLooper,NULL);
        pthread_create(&threadPrint4, NULL, experis::PrintLooper,NULL);
        pthread_create(&threadAdd1, NULL, experis::AddLooper,NULL);
        pthread_create(&threadAdd2, NULL, experis::AddLooper,NULL);
        pthread_create(&threadAdd3, NULL, experis::AddLooper,NULL);
        pthread_create(&threadAdd4, NULL, experis::AddLooper,NULL);

        pthread_join(threadPrint1, NULL);
        pthread_join(threadPrint2, NULL);
        pthread_join(threadPrint3, NULL);
        pthread_join(threadPrint4, NULL);
        pthread_join(threadAdd1, NULL);
        pthread_join(threadAdd2, NULL);
        pthread_join(threadAdd3, NULL);
        pthread_join(threadAdd4, NULL);
    }catch(const std::exception& exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}