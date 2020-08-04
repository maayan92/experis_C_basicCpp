#ifndef __MUTEX_LOCKER_H__
#define __MUTEX_LOCKER_H__

#include "mutex.hpp"

namespace experis {

class MutexLocker : private Uncopyable {
public:
    explicit MutexLocker(Mutex &a_mutex);
    ~MutexLocker();
    inline void Lock();
    inline void Unlock();
    inline Mutex& GetMutex();

private:
    Mutex& m_mutex;
};

} // experis

namespace experis {

inline MutexLocker::MutexLocker(Mutex &a_mutex)
: m_mutex(a_mutex) {
    a_mutex.Lock();
}

inline MutexLocker::~MutexLocker() {
    m_mutex.Unlock();
}

inline void MutexLocker::Lock() {
    m_mutex.Lock();
}

inline void MutexLocker::Unlock() {
    m_mutex.Unlock();
}

inline Mutex& MutexLocker::GetMutex() {
    return m_mutex;
}

} // experis

#endif