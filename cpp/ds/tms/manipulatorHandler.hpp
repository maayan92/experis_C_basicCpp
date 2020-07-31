#ifndef __MANIPULATOR_HANDLER_H__
#define __MANIPULATOR_HANDLER_H__

#include <vector>
#include "manipulator.hpp"

namespace experis {

class ManipulatorHandler {
    typedef std::vector<Manipulator*> Manipulators;
    typedef Manipulators::iterator Iterator;
public:
    ManipulatorHandler(Tokenizer::Tokens& a_buffer);
    //ManipulatorHandler(const ManipulatorHandler& a_manipulator) = default;
    //ManipulatorHandler& operator=(const ManipulatorHandler& a_manipulator) = default;
    ~ManipulatorHandler();

    void DoAllManipulation();
    std::string GatBuffer() const;

private:
    Manipulators m_manipulators;
    Tokenizer::Tokens m_buffer;
};

} // experis

#endif