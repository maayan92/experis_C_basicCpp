#include "operator.h"

namespace experis {

Operator::Operator(ExprTree* a_left, ExprTree* a_right)
: m_left(a_left), m_right(a_right) {
}

Operator::~Operator() {
    delete m_left;
    delete m_right;
}

} // experis