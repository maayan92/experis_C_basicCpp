#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

namespace experis {

class Tokenizer {
    typedef std::string::iterator Itr;
public:
    typedef std::vector<std::string> Tokens;
    Tokenizer(std::string& a_delimiters);
    //Tokenizer(const Tokenizer& a_tokenizer) = default;
    //~Tokenizer() = default;
    //Tokenizer& operator=(const Tokenizer& a_tokenizer) = default;

    Tokens& DivideIntoTokens(std::ifstream& a_inputFile);
    void SetTokensToFile(std::ostream& a_outFile) const;

private:
    void DivideLineIntoTokens(std::string& a_wordFromFile);

    std::string m_delimiters;
    Tokens m_tokens;
};

} // experis

#endif