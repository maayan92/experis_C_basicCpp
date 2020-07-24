#include "number.h"

namespace experis {

Number::Number(int a_value)
: m_value(a_value) {
}

inline int Number::Calculate() const {
    return m_value;
}

void Number::Print(std::ostream& a_os) const {
    a_os << m_value ;
}

} // experis