#include "tms.hpp"
#include "tokenizer.hpp"
#include "tolower.hpp"
#include "toupper.hpp"
#include <iostream>
#include <algorithm>
#include <ostream>

namespace experis {

static void setTokensToFile(std::ostream& a_outFile, Tokenizer::Tokens& a_tokens) {
    for(size_t position = 0 ; position < a_tokens.size() ; ++position) {
        a_outFile << a_tokens[position];
    }
}

Tms::Tms(TmsArgs a_tmsArgs)
: m_tmsArgs(a_tmsArgs) {
}

void Tms::Run() const {
    if(0 == m_tmsArgs.size()) {
        return;
    }
    
    size_t position = 0, inputFilepos = m_tmsArgs.size() - 1;
    Tokenizer::Tokens tokens;
    setInputFile(tokens, inputFilepos);

    while(position <= inputFilepos) {
        ManipulatorHandler manipulatorHandler(tokens);
        setAllManipulators(manipulatorHandler, position);
        Tokenizer::Tokens tokensResult = manipulatorHandler.DoAllManipulation();
        setResultToOutput(tokensResult, position);
    }
}

// private functions:

void Tms::setAllManipulators(ManipulatorHandler& a_manipulatorHandler, size_t& a_position) const {
    Manipulator* manipulator;
    while(a_position < m_tmsArgs.size()) {
        if(0 == strcmp(m_tmsArgs[a_position], "-tolow")) {
            manipulator = new Tolower();
        }
        else if(0 == strcmp(m_tmsArgs[a_position], "-toup")) {
            manipulator = new Toupper();
        }
        else if(0 == strcmp(m_tmsArgs[a_position], "-censor")) {
            //manipulator = new Encrypt();
        }
        else if(0 == strcmp(m_tmsArgs[a_position], "-decrypt")) {
            //manipulator = new Decrypt();
        }
        else if(0 == strcmp(m_tmsArgs[a_position], "-singlespc")) {
            //manipulator = new Singlespc();
        }
        else if((0 == strcmp(m_tmsArgs[a_position], "-censor")) && isTxtFile(a_position + 1)){
            //manipulator = new Censor();
            ++a_position;
        }
        else { return; }
        a_manipulatorHandler.AddManipulator(manipulator);
        ++a_position;
    }
}

void Tms::setResultToOutput(Tokenizer::Tokens& a_tokens, size_t& a_position) const {
    if(0 == strcmp(m_tmsArgs[a_position], "-out")) {
        if(isTxtFile(a_position + 1)) {
            std::ofstream outFile(m_tmsArgs[a_position + 1]);
            setTokensToFile(outFile, a_tokens);
            ++a_position;
        }
        else {
            setTokensToFile(std::cout, a_tokens);
        }
        ++a_position;
    }
    else {
        throw ExcOperationUnKnown();
    }
}

void Tms::setInputFile(Tokenizer::Tokens& tokens, size_t& a_position) const {
    std::string s(";())!{}[]");
    Tokenizer tokenizer(s);

    if(isInputFile(a_position)) {
        std::ifstream inputFile(m_tmsArgs[a_position]);
        tokens = tokenizer.DivideIntoTokens(inputFile);
        --a_position;
    }
    else {
        tokens = tokenizer.DivideIntoTokens(std::cin);
    }
}

bool Tms::isInputFile(size_t a_position) const {
    return isTxtFile(a_position) && (0 != strcmp(m_tmsArgs[a_position-1], "-out"))
                    && (0 != strcmp(m_tmsArgs[a_position-1], "-censor"));
}

bool Tms::isTxtFile(size_t a_position) const {
    int argPosition = strlen(m_tmsArgs[a_position]) - 4;

    return (0 == strcmp(m_tmsArgs[a_position] + argPosition, ".txt"));
}

} // experis