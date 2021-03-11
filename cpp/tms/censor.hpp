#ifndef __CENSOR_H__
#define __CENSOR_H__

#include "manipulator.hpp"
#include "tokenizer.hpp"

namespace experis {

class Censor : public Manipulator {
public:
    // inherits from Manipulator:
    //void Manipulation(Tokenizer::Tokens& m_buffer);
    
    Censor(std::ifstream& a_words);
    //Censor(const Censor& a_censor) = default;
    
    virtual void TokenManipulation(std::string& a_token);
private:
    Censor& operator=(const Censor& a_censor);
    virtual ~Censor() {}

    Tokenizer m_wordTokens;
};

} // experis


#endif