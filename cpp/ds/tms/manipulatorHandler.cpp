#include "manipulatorHandler.hpp"

namespace experis {

ManipulatorHandler::ManipulatorHandler(Tokenizer::Tokens& a_buffer)
: m_manipulators()
, m_buffer(a_buffer) {
}

ManipulatorHandler::~ManipulatorHandler() {
    for(Iterator itr = m_manipulators.begin() ; itr != m_manipulators.end(); ++itr) {
        Manipulator *manipulator =  *itr;
        delete manipulator;
    }
}

void ManipulatorHandler::AddManipulator(const Manipulator* a_manipulator) {
    if(!a_manipulator) { 
        throw ExcNullInput();
    }
    m_manipulators.push_back(const_cast<Manipulator*>(a_manipulator));
}

Tokenizer::Tokens ManipulatorHandler::DoAllManipulation() {
    for(size_t position = 0 ; position < m_manipulators.size() ; ++position) {
        m_manipulators[position]->Manipulation(m_buffer);
    }
    return m_buffer;
}

} // experis