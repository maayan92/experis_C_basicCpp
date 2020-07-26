#ifndef __ADD_OPERATOR_H__
#define __ADD_OPERATOR_H__

#include "operator.h"

namespace experis {

class AddOp : public Operator {
public:
    AddOp(ExprTree* a_left, ExprTree* a_right);
    //AddOp(const AddOp& a_add) = default;
    //AddOp& operator=(const AddOp& a_add) = default;

    virtual int Calculate() const;
    virtual void Print(std::ostream& a_os) const;

private:
    virtual ~AddOp() {}
};

} // experis

#endif