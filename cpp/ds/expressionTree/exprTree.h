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
    virtual ~ExprTree() = 0;

    virtual int Calculate() const = 0;
    virtual void Print(std::ostream& a_os) const = 0;
};

} // experis

namespace experis{

inline ExprTree::~ExprTree() { }

} // experis

#endif