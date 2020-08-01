#ifndef __TO_UP_H__
#define __TO_UP_H__

#include "manipulator.hpp"

namespace experis {

class Toupper : public Manipulator {
public:
    // inherits from Manipulator:
    //void Manipulation(Tokenizer::Tokens& m_buffer);
    
    //Toupper() = default;
    //Toupper(const Toup& a_toup) = default;
    //Toupper& operator=(const Toup& a_toup) = default;
    
    virtual void TokenManipulation(std::string& a_token);
private:
    virtual ~Toupper() {}
};

} // experis


#endif