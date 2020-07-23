#ifndef __MUL_OPERTOR_H__
#define __MUL_OPERTOR_H__

#include "operator.h"

namespace experis {

class MulOp : public Operator {
public:
    MulOp(ExprTree* a_left, ExprTree* a_right);
    //MulOp(const MulOp& a_MulOp) = default;
    //MulOp& operator=(const MulOp& a_MulOp) = default;
    //~MulOp() = default; TODO

    virtual int Calculate() const;
    virtual void Print() const;
};

} // experis

#endif