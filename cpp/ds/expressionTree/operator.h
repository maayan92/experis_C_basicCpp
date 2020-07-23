#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "exprTree.h"

namespace experis {

class Operator : public ExprTree {
public:
    Operator(ExprTree* a_left, ExprTree* a_right) : m_left(a_left), m_right(a_right) {}
    //Operator(const Operator& a_operator) = default;
    //Operator& operator=(const Operator& a_operator) = default;
    virtual ~Operator() {}

    virtual int Calculate() const = 0;
    virtual void Print() const = 0;

protected:
    ExprTree* GetLeftExprTree() const { return m_left; }
    ExprTree* GetRightExprTree() const { return m_right; }

private:
    ExprTree* m_left;
    ExprTree* m_right;
};

} // experis

#endif