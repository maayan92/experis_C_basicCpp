#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

#include "uncopyable.hpp"

namespace experis {

class Runnable : private Unassignable {
public:
    //Runnable() = default;
    //Runnable(const Runnable &a_other) = default;
    virtual ~Runnable() {}
    virtual void Do() = 0;
};

} // experis

#endif