#ifndef __EXPR_TREE_H__
#define __EXPR_TREE_H__

#include <iostream>
#include <string>
#include <sstream>

namespace experis {

class ExprTree {
public:
    //ExprTree() = default;
    //ExprTree(const ExprTree& a_exprTree) = default;
    //ExprTree& operator=(const ExprTree& a_exprTree) = default;
    virtual ~ExprTree() {}

    virtual int Calculate() const = 0;
    virtual void Print() const = 0;
};

} // experis

#endif