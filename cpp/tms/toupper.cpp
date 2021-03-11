#include "toupper.hpp"
#include <algorithm>

namespace experis {

void Toupper::TokenManipulation(std::string& a_token) {
    std::transform (a_token.begin(), a_token.end(), a_token.begin(), toupper);
}

} // experis