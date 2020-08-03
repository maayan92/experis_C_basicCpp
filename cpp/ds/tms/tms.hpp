#ifndef __TMS_H__
#define __TMS_H__

#include "manipulatorHandler.hpp"

namespace experis {

class ExcOperationUnKnown : public std::exception {
public:
    const char* what() const throw() { return "unknown operation!"; }
};

class Tms {
public:
    typedef std::vector<char*> TmsArgs;
    typedef TmsArgs::iterator Itr;

    Tms(TmsArgs a_tmsArgs);
    //Tms(const Tms& a_tms) = default;
    //~Tms() = default;
    //Tms& operator=(const Tms& a_tms) = default;

    void Run() const; // throw ExcOperationUnKnown if operation is unknown.

private:
    void setInputFile(Tokenizer::Tokens& tokens, size_t& a_position) const;
    void setAllManipulators(ManipulatorHandler& a_manipulatorHandler, size_t& a_position) const;
    void setResultToOutput(Tokenizer::Tokens& a_tokens, size_t& a_position) const;
    bool isInputFile(size_t a_position) const;
    bool isTxtFile(size_t a_position) const;

    TmsArgs m_tmsArgs;
};

} // experis

#endif