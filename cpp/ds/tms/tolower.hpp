#ifndef __TO_LOWER_H__
#define __TO_LOWER_H__

#include "manipulator.hpp"

namespace experis {

class Tolower : Manipulator {
public:
    //Tolower() = default;
    //Tolower(const Tolower& a_tolower) = default;
    //Tolower& operator=(const Tolower& a_tolower) = default;
    //virtual ~Tolower() = default;
    
    virtual void Manipulation(Tokenizer::Tokens& m_buffer);
};

} // experis


#endif