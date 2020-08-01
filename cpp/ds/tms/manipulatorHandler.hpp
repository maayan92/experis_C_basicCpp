#ifndef __MANIPULATOR_HANDLER_H__
#define __MANIPULATOR_HANDLER_H__

#include <vector>
#include <exception>
#include "manipulator.hpp"

namespace experis {

class ExcNullInput : public std::exception {
    const char* what() const throw() { return "NULL input!"; }
};

class ManipulatorHandler {
    typedef std::vector<Manipulator*> Manipulators;
    typedef Manipulators::iterator Iterator;
public:
    ManipulatorHandler(Tokenizer::Tokens& a_buffer);
    //ManipulatorHandler(const ManipulatorHandler& a_manipulator) = default;
    //ManipulatorHandler& operator=(const ManipulatorHandler& a_manipulator) = default;
    ~ManipulatorHandler();

    // bad_alloc exception is thrown on failure.
    void AddManipulator(const Manipulator* a_manipulator);
    Tokenizer::Tokens DoAllManipulation();

private:
    Manipulators m_manipulators;
    Tokenizer::Tokens m_buffer;
};

} // experis

#endif