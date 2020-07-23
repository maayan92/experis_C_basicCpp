#include "mul.h"

namespace experis {

MulOp::MulOp(ExprTree* a_left, ExprTree* a_right)
: Operator(a_left, a_right) {
}

int MulOp::Calculate() const {
    return this->GetLeftExprTree()->Calculate() * this->GetRightExprTree()->Calculate();
}

void MulOp::Print() const {
    
    std::cout << " ( ";
    this->GetLeftExprTree()->Print();
    std::cout << " * ";
    this->GetRightExprTree()->Print();
    std::cout << " ) ";
}


} // experis