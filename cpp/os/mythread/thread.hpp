#ifndef __THREAD_H__
#define __THREAD_H__

#include "runnable.hpp"
#include <exception>
#include <pthread.h>

namespace experis {
    
class ExcNoResourcesToCreateThread : public std::exception {
public:
    const char* what() const throw() {
        return "create thread - insufficient resources to create another thread!";
    }
};

class ExcReachedToMaximum : public std::exception {
public:
    const char* what() const throw() {
        return "create thread - reached to the maximum number of PIDs!";
    }
};

class ExcThreadNotJoinable : public std::exception {
public:
    const char* what() const throw() {
        return "join thread - not joinable!";
    }
};

class ExcDeadlockDetected : public std::exception {
public:
    const char* what() const throw() {
        return "join thread - a deadlock was detected!";
    }
};

class ExcThreadNotExist : public std::exception {
public:
    const char* what() const throw() {
        return "join thread - no thread with this id!";
    }
};

class Thread : private Uncopyable {
public:
    Thread(Runnable &a_threadAction);
    ~Thread();

    void Join();
    
private:
    pthread_t m_thread;
    bool m_hasJoined;
};

} // experis

#endif