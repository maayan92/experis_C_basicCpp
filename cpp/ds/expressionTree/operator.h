#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "exprTree.h"

namespace experis {

class Operator : public ExprTree {
public:
    Operator(ExprTree* a_left, ExprTree* a_right);
    //Operator(const Operator& a_operator) = default;
    //Operator& operator=(const Operator& a_operator) = default;
    virtual ~Operator() = 0;

    virtual int Calculate() const = 0;
    virtual void Print(std::ostream& a_os) const = 0;

protected:
    ExprTree* GetLeftExprTree() const { return m_left; }
    ExprTree* GetRightExprTree() const { return m_right; }

private:
    ExprTree* m_left;
    ExprTree* m_right;
};

} // experis

#endif