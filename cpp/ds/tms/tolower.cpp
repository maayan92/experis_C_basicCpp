#include "tolower.hpp"

namespace experis {

void Tolower::TokenManipulation(std::string& a_token) {
    for(int i = 0 ; i < a_token.size() ; ++i) {
        a_token[i] = tolower(a_token[i]);
    }
}

} // experis