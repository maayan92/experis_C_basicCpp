#include <iostream>
#include "exprTree.h"
#include "number.h"
#include "mul.h"
#include "add.h"

void TestNumberCreate() {
    experis::Number *num = new experis::Number(5);
    static int testNum = 0;
    std::cout << "number create test " <<  ++testNum << ": "
            << ((num->Calculate() == 5) ? "SUCCESS" : "FAILED") << std::endl;

    delete num;
}

int main() {

    TestNumberCreate();

    experis::Number(5);

    experis::ExprTree *expr = new experis::AddOp(new experis::Number(3), new experis::MulOp(new experis::Number(4), new experis::Number(5)));

    std::cout << expr->Calculate() << std::endl;

    expr->Print();

    std::cout << std::endl;

/*
    ExprTree exprTreeFirst;
   
    exprTreeFirst.AddNumber(3);
    exprTreeFirst.AddOperationPlus();
    exprTreeFirst.AddNumber(4);
    exprTreeFirst.AddOperationMultiple();
    exprTreeFirst.AddNumber(5);
    
    exprTreeFirst.calculateExpression();

    exprTreeFirst.AddDivid();
    exprTreeFirst.AddMinus();


*/

/*

    new Add(new Number(3), new Mul(new Number(4), new Number(5));

    ExprTree *exp = new AddOp(new AddOp(new Number(1),
                                    new MulOp(new Number(9),
                                            new AddOp(new Number(2),
                                                    new MulOp(new Number(3),
                                                            new Number(2))))),
                            new Number(27));


    exp->Calc();
    exp->Print(std::cout);
    ofstream outfile("a.txt");
    exp->Print(outfile);

*/






    return 0;
}
