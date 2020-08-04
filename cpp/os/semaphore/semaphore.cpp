#include "semaphore.hpp"
#include <assert.h>
#include <errno.h>

namespace experis {

Semaphore::Semaphore()
: m_semaphore()
, Uncopyable() {
    int status = sem_init(&m_semaphore, 0, 1);
    if(-1 == status) {
        assert(ENOSYS != errno);
        assert(EINVAL != errno);
        assert(!"undocumented error for sem_init");
    }
}

Semaphore::Semaphore(unsigned int a_value)
: m_semaphore()
, Uncopyable() {
    int status = sem_init(&m_semaphore, 0, a_value);
    if(-1 == status) {
        assert(ENOSYS != errno);

        if(EINVAL == errno) {
            throw ExcValueTooBig();
        }
        assert(!"undocumented error for sem_init");
    }
}

Semaphore::~Semaphore() {
    int status = sem_destroy(&m_semaphore);
    assert(0 == status);
}

void Semaphore::Wait() {
    int status = sem_wait(&m_semaphore);
    if(-1 == status) {
        assert(EINVAL != errno);
        assert(EAGAIN != errno);

        if(EINTR == errno) {
            throw ExcInterruptedBySignalHandler();
        }
        if(ETIMEDOUT == errno) {
            throw ExcTimeOutBeforeLocked();
        }
        assert(!"undocumented error for sem_wait");
    }
}

void Semaphore::Post() {
    int status = sem_post(&m_semaphore);
    if(-1 == status) {
        assert(EINVAL != errno);

        if(EOVERFLOW == errno) {
            throw ExcMaximumAllowableValue();
        }
        assert(!"undocumented error for sem_post");
    }
}

} // experis