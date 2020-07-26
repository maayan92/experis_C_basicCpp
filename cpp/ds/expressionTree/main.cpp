#include <iostream>
#include <fstream>
#include "exprTree.h"
#include "number.h"
#include "mul.h"
#include "add.h"

typedef experis::ExprTree ExprTree;
typedef experis::AddOp AddOp;
typedef experis::MulOp MulOp;
typedef experis::Number Number;

void TestCreateExprTree(ExprTree *a_expr, const char* a_str, size_t a_sum) {
    
    static int testNum = 0;

    std::cout << a_str << " create test " <<  ++testNum << ": \t\t \033[1;31m"
            << ((a_expr->Calculate() == a_sum) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;
    
}

void TestExprTrePrintToFile(ExprTree *a_expr, std::stringstream& a_result) {
    
    static int testNum = 0;
   
    std::stringstream out;
    a_expr->Print(out);

    std::cout << "print to file test " <<  ++testNum << ": \t\t\t \033[1;31m"
            << ((out.str() == a_result.str()) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;
}


int main() {
    
    ExprTree *exprNumber = new Number(5);
    TestCreateExprTree(new Number(5), "expression num",  5);
    delete exprNumber;

    ExprTree *exprAdd = new AddOp(new Number(1), new Number(3));
    TestCreateExprTree(exprAdd, "expression add", 4);
    delete exprAdd;

    ExprTree *exprMul = new MulOp(new Number(1), new Number(3));
    TestCreateExprTree(exprMul, "expression mul", 3);
    delete exprMul;

    ExprTree *exprfirst = new AddOp(new Number(3), new MulOp(new Number(4), new Number(5)));
    TestCreateExprTree(exprfirst, "expression tree", 23);

    ExprTree *exprSecond = new AddOp(new AddOp(new Number(1),
                                    new MulOp(new Number(9),
                                            new AddOp(new Number(2),
                                                    new MulOp(new Number(3),
                                                            new Number(2))))),
                            new Number(27));
    TestCreateExprTree(exprSecond, "expression tree", 100);

    std::stringstream str("(3 + (4 * 5))");
    TestExprTrePrintToFile(exprfirst, str);

    str.str("((1 + (9 * (2 + (3 * 2)))) + 27)");
    TestExprTrePrintToFile(exprSecond, str);

    delete exprfirst;
    delete exprSecond;

    return 0;
}
