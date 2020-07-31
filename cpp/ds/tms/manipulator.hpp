#ifndef __MANIPULATOR_H__
#define __MANIPULATOR_H__

#include <iostream>
#include "tokenizer.hpp"

namespace experis {
    
class Manipulator {
public:
    //Manipulator() = default;
    //Manipulator(const Manipulator& a_manipulator) = default;
    //Manipulator& operator=(const Manipulator& a_manipulator) = default;
    virtual ~Manipulator() = 0;

    virtual void Manipulation(Tokenizer::Tokens& m_buffer) = 0;
};

} // experis

namespace experis {

Manipulator::~Manipulator() {
}

} // experis

#endif