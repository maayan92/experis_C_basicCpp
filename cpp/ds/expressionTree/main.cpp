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

void TestExprTrePrintToFile(ExprTree *a_expr, size_t a_sum, std::ofstream& a_file) {
    
    static int testNum = 0;
    
    a_expr->Print(a_file);
    a_file << std::endl;

    std::cout << "print to file test " <<  ++testNum << ": \t\t\t \033[1;31m"
            << ((a_expr->Calculate() == a_sum) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;
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

    std::ofstream file("exprTree.txt");
    TestExprTrePrintToFile(exprfirst, 23, file);
    TestExprTrePrintToFile(exprSecond, 100, file);

    delete exprfirst;
    delete exprSecond;

    return 0;
}
