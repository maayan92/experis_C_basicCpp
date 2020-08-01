#include "manipulator.hpp"

namespace experis {

Manipulator::~Manipulator() {}

void Manipulator::Manipulation(Tokenizer::Tokens& m_buffer) {
    for(size_t position = 0 ; position < m_buffer.size() ; ++position) {
        TokenManipulation(m_buffer[position]);
    }
}

} // experis