#include "add.h"

namespace experis {

AddOp::AddOp(ExprTree* a_left, ExprTree* a_right)
: Operator(a_left, a_right) {
}

int AddOp::Calculate() const {
    return this->GetLeftExprTree()->Calculate() + this->GetRightExprTree()->Calculate();
}

void AddOp::Print(std::ostream& a_os) const {
    
    a_os << "(";
    this->GetLeftExprTree()->Print(a_os);
    a_os << " + ";
    this->GetRightExprTree()->Print(a_os);
    a_os << ")";
}

} // experis