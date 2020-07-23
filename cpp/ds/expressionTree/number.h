#ifndef __NUMBER_H__
#define __NUMBER_H__

#include "exprTree.h"

namespace experis {

class Number : public ExprTree {
public:
    Number(int a_value);
    //Number(const Number& a_number) = default;
    //Number& operator=(const Number& a_number) = default;
    virtual ~Number() {}

    virtual int Calculate() const;
    virtual void Print() const; // TODO stringstream

private:
    int m_value;
};

} // experis

#endif