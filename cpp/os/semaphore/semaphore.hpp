#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <semaphore.h>
#include <exception>
#include "uncopyable.hpp"

namespace experis {

class ExcValueTooBig : public std::exception {
public:
    virtual const char* what() const throw() { 
        return "initialization error - value is too big!";
    }
};

class ExcInterruptedBySignalHandler : public std::exception {
public:
    virtual const char* what() const throw() { 
        return "wait error - interrupted by signal handler!";
    }
};

class ExcTimeOutBeforeLocked : public std::exception {
public:
    virtual const char* what() const throw() { 
        return "wait error - call timed out before semaphore could be locked!";
    }
};

class ExcMaximumAllowableValue : public std::exception {
public:
    virtual const char* what() const throw() { 
        return "post error - maximum allowable semaphore value exceeded!";
    }
};

class Semaphore : private Uncopyable{
public:
    Semaphore(unsigned int a_value);
    Semaphore();
    ~Semaphore();

    void Wait();
    void Post();

private:
    sem_t m_semaphore;
};

} // experis

#endif