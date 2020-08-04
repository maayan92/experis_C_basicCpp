#include "conditionVariable.hpp"
#include <pthread.h>
#include <assert.h>
#include <errno.h>
#include <iostream>

namespace experis {

ConditionVariable::ConditionVariable()
: m_condVar() {
    int status = pthread_cond_init(&m_condVar, NULL);
    if(0 != status) {
        assert(EBUSY != status);
        assert(EINVAL != status);

        if(EAGAIN == status) {
            throw ExcSystemLackedOfResources();
        }
        if(ENOMEM == status) {
            throw ExcInsufficientMemory();
        }
        assert(!"undocumented error for pthread_cond_init");
    }
}

ConditionVariable::~ConditionVariable() {
    int status = pthread_cond_destroy(&m_condVar);
    if(0 != status) {
        assert(EINVAL != status);
        assert(EBUSY != status);
        assert(!"undocumented error for pthread_cond_destroy");
    }
}

void ConditionVariable::Wait(MutexLocker &a_mutex) {
    int status = pthread_cond_wait(&m_condVar, &(a_mutex.GetMutex().GetMutex()));
    if(0 != status) {
        assert(EINVAL != status);
        assert(EPERM != status);
        assert(!"undocumented error for pthread_cond_wait");
    }
}

void ConditionVariable::NotifyOne() {
    int status = pthread_cond_signal(&m_condVar);
    assert(0 == status);
}

void ConditionVariable::NotifyAll() {
    int status = pthread_cond_broadcast(&m_condVar);
    assert(0 == status);
}

} // experis