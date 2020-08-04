#include "mutex.hpp"
#include <assert.h>
#include <errno.h>
#include <new>

namespace experis {

Mutex::Mutex()
: m_locker()
, Uncopyable() {
    int status = pthread_mutex_init(&m_locker, NULL);
    if(0 != status) {
        assert(status != EINVAL);
        assert(status != EBUSY);

        if(EPERM == status) {
            throw ExcNotEnoughPermission();
        }
        if(ENOMEM == status) {
            throw std::bad_alloc();
        }
        if(EAGAIN) {
           throw ExcNotEnoughSyncResources(); 
        }
        assert(!"undocumented error for pthread_mutex_init");
    }
}

Mutex::~Mutex() { // one error is possible
    int status = pthread_mutex_destroy(&m_locker);
    assert(0 == status);
}

void Mutex::Lock() {
    int status = pthread_mutex_lock(&m_locker);
    if(0 != status) {
        assert(status != EINVAL);
        assert(status != EBUSY);
        assert(status != EAGAIN);
        
        if(EDEADLK == status) {
            throw ExcMutexIsAlreadyLocked();
        }
        assert(!"undocumented error for pthread_mutex_lock");
    }
}

void Mutex::Unlock() {
    int status = pthread_mutex_unlock(&m_locker);
    if(0 != status) {
        assert(status != EINVAL);
        assert(status != EBUSY);
        assert(status != EAGAIN);
        
        if(EPERM == status) {
            throw ExcDoesNotOwnCurrentMutex();
        }
        assert(!"undocumented error for pthread_mutex_unlock");
    }
}

} // experis