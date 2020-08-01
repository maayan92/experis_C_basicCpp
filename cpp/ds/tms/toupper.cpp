#include "toupper.hpp"

namespace experis {

void Toupper::TokenManipulation(std::string& a_token) {
    for(int i = 0 ; i < a_token.size() ; ++i) {
        a_token[i] = toupper(a_token[i]);
    }
}

} // experis