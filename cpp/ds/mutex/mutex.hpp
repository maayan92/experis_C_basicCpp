#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
#include <exception>
#include <assert.h>

namespace experis {

class ExcMutexInitFailed : public std::exception {
public:
    virtual const char* what() const throw() { return "mutex initialization failed!"; }
};

class ExcLockFailed : public std::exception {
public:
    virtual const char* what() const throw() { return "mutex lock failed!"; }
};

class ExcUnLockFailed : public std::exception {
public:
    virtual const char* what() const throw() { return "mutex unlock failed!"; }
};

class Mutex {
public:
    Mutex();
    //Mutex(const Mutex& a_mutex) = default;
    ~Mutex();
    //Mutex& operator=(const Mutex& a_mutex) = default;

    void Lock();
    void Unlock();

private:
    pthread_mutex_t m_locker;
};

} // experis

#endif