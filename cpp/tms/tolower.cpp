#include "tolower.hpp"
#include <algorithm>

namespace experis {

void Tolower::TokenManipulation(std::string& a_token) {
    std::transform (a_token.begin(), a_token.end(), a_token.begin(), tolower);
}

} // experis