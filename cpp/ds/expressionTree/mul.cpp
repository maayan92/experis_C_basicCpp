#include "mul.h"

namespace experis {

MulOp::MulOp(ExprTree* a_left, ExprTree* a_right)
: Operator(a_left, a_right) {
}

int MulOp::Calculate() const {
    return this->GetLeftExprTree()->Calculate() * this->GetRightExprTree()->Calculate();
}

void MulOp::Print(std::ostream& a_os) const {
    
    a_os << "(";
    this->GetLeftExprTree()->Print(a_os);
    a_os << " * ";
    this->GetRightExprTree()->Print(a_os);
    a_os << ")";
}

} // experis