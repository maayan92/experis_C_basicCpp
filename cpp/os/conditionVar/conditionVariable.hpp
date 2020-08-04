#ifndef __CONDITION_VARIABLE_H__
#define __CONDITION_VARIABLE_H__

#include "mutexLocker.hpp"

namespace experis {

class ConditionVariable : private Uncopyable {
public:
    ConditionVariable();
    ~ConditionVariable();

    void NotifyOne();
    void NotifyAll();
    void Wait(MutexLocker &a_mutex);

private:
    pthread_cond_t m_condVar;
};

class ExcSystemLackedOfResources : public std::exception {
public:
    const char* what() const throw() {
        return "create error - system lacked the necessary resources";
    }
};

class ExcInsufficientMemory : public std::exception {
public:
    const char* what() const throw() {
        return "create error - Insufficient memory exists to initialize";
    }
};

} // experis

#endif