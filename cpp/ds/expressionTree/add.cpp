#include "add.h"

namespace experis {

AddOp::AddOp(ExprTree* a_left, ExprTree* a_right)
: Operator(a_left, a_right) {
}

int AddOp::Calculate() const {
    return this->GetLeftExprTree()->Calculate() + this->GetRightExprTree()->Calculate();
}

void AddOp::Print() const {
    
    std::cout << " ( ";
    this->GetLeftExprTree()->Print();
    std::cout << " + ";
    this->GetRightExprTree()->Print();
    std::cout << " ) ";
}

} // experis