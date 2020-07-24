#ifndef __MUL_OPERTOR_H__
#define __MUL_OPERTOR_H__

#include "operator.h"

namespace experis {

class MulOp : public Operator {
public:
    MulOp(ExprTree* a_left, ExprTree* a_right);
    //MulOp(const MulOp& a_MulOp) = default;
    //MulOp& operator=(const MulOp& a_MulOp) = default;
    virtual ~MulOp() {} // a_left and a_right are destroyed in the Operator's DTOR.

    virtual int Calculate() const;
    virtual void Print(std::ostream& a_os) const;
};

} // experis

#endif