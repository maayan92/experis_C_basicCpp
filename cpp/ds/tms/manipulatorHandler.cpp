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

void ManipulatorHandler::DoAllManipulation() {
    size_t position = 0;
    while(position < m_manipulators.size()) {
        m_manipulators[position]->Manipulation(m_buffer);
    }
}

} // experis