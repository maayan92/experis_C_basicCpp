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

void TestCreateNumber() {
    experis::Number *num = new experis::Number(5);
    static int testNum = 0;

    std::cout << "number create test " <<  ++testNum << ": \t\t\t \033[1;31m"
            << ((num->Calculate() == 5) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;

    delete num;
}

void TestCreateAddOp() {
    AddOp *add = new AddOp(new Number(1), new Number(3)); 
    static int testNum = 0;

    std::cout << "add expression test " <<  ++testNum << ": \t\t\t \033[1;31m"
            << ((add->Calculate() == 4) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;

    delete add;
}

void TestCreateMulOp() {
    MulOp *mul = new MulOp(new Number(1), new Number(3)); 
    static int testNum = 0;

    std::cout << "multiple expression create test " <<  ++testNum << ": \t \033[1;31m"
            << ((mul->Calculate() == 3) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;

    delete mul;
}

void TestCreateExprTree(ExprTree *a_expr, size_t a_sum) {
    
    static int testNum = 0;

    std::cout << "expression tree create test " <<  ++testNum << ": \t\t \033[1;31m"
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

    TestCreateNumber();
    TestCreateAddOp();
    TestCreateMulOp();

    ExprTree *exprfirst = new AddOp(new Number(3), new MulOp(new Number(4), new Number(5)));
    TestCreateExprTree(exprfirst, 23);

    ExprTree *exprSecond = new AddOp(new AddOp(new Number(1),
                                    new MulOp(new Number(9),
                                            new AddOp(new Number(2),
                                                    new MulOp(new Number(3),
                                                            new Number(2))))),
                            new Number(27));
    TestCreateExprTree(exprSecond, 100);

    std::ofstream file("exprTree.txt");
    TestExprTrePrintToFile(exprfirst, 23, file);
    TestExprTrePrintToFile(exprSecond, 100, file);

    delete exprfirst;
    delete exprSecond;

    return 0;
}
