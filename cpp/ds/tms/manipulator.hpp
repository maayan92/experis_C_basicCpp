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

    void Manipulation(Tokenizer::Tokens& m_buffer);
    virtual void TokenManipulation(std::string& a_token) = 0;
};

} // experis


#endif