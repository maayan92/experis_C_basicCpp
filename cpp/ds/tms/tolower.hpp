#ifndef __TO_LOWER_H__
#define __TO_LOWER_H__

#include "manipulator.hpp"

namespace experis {

class Tolower : public Manipulator {
public:
    // inherits from Manipulator:
    //void Manipulation(Tokenizer::Tokens& m_buffer);
    
    //Tolower() = default;
    //Tolower(const Tolower& a_tolower) = default;
    //Tolower& operator=(const Tolower& a_tolower) = default;
    
    virtual void TokenManipulation(std::string& a_token);
private:
    virtual ~Tolower() {}
};

} // experis


#endif