#ifndef __MUL_OPERTOR_H__
#define __MUL_OPERTOR_H__

#include "operator.h"

namespace experis {

class MulOp : public Operator {
public:
    MulOp(ExprTree* a_left, ExprTree* a_right);
    //MulOp(const MulOp& a_MulOp) = default;
    //MulOp& operator=(const MulOp& a_MulOp) = default;

    virtual int Calculate() const;
    virtual void Print(std::ostream& a_os) const;

private:
    virtual ~MulOp() {}
};

} // experis

#endif