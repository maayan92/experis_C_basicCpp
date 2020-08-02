#include "mutex.hpp"

namespace experis {

Mutex::Mutex()
: m_locker() {
    if(0 != pthread_mutex_init(&m_locker, NULL)) {
        throw ExcMutexInitFailed();
    }
}

Mutex::~Mutex() {
    assert(0 == pthread_mutex_destroy(&m_locker));
}

void Mutex::Lock() {
    if(0 != pthread_mutex_lock(&m_locker)) {
        throw ExcLockFailed();
    }
}

void Mutex::Unlock() {
    if(0 != pthread_mutex_unlock(&m_locker)) {
        throw ExcUnLockFailed();
    }
}

} // experis