#include "number.h"

namespace experis {

Number::Number(int a_value)
: m_value(a_value) {
}

inline int Number::Calculate() const {
    return m_value;
}

void Number::Print() const {
    std::cout << m_value << ' ';
}

} // experis