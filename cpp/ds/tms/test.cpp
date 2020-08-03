#include "tolower.hpp"
#include "toupper.hpp"
#include "manipulatorHandler.hpp"

namespace experis { 

static void FillTokensResultTokenizer(Tokenizer::Tokens& a_result) {
    a_result.push_back("I"); a_result.push_back(" "); a_result.push_back("FORgot");
    a_result.push_back(" "); a_result.push_back("bla"); a_result.push_back("!");
    a_result.push_back("Bla"); a_result.push_back(" "); a_result.push_back("Pfg");
    a_result.push_back("\n"); a_result.push_back("heLLo");
    a_result.push_back("("); a_result.push_back(")"); a_result.push_back("hh");
    a_result.push_back(" "); a_result.push_back("wor0LD"); a_result.push_back("\n");
}

static void FillTokensResultTolower(Tokenizer::Tokens& a_result) {
    a_result.push_back("i"); a_result.push_back(" "); a_result.push_back("forgot");
    a_result.push_back(" "); a_result.push_back("bla"); a_result.push_back("!");
    a_result.push_back("bla"); a_result.push_back(" "); a_result.push_back("pfg");
    a_result.push_back("\n"); a_result.push_back("hello");
    a_result.push_back("("); a_result.push_back(")"); a_result.push_back("hh");
    a_result.push_back(" "); a_result.push_back("wor0ld"); a_result.push_back("\n");
}

static void FillTokensResultToupper(Tokenizer::Tokens& a_result) {
    a_result.push_back("I"); a_result.push_back(" "); a_result.push_back("FORGOT");
    a_result.push_back(" "); a_result.push_back("BLA"); a_result.push_back("!");
    a_result.push_back("BLA"); a_result.push_back(" "); a_result.push_back("PFG");
    a_result.push_back("\n"); a_result.push_back("HELLO");
    a_result.push_back("("); a_result.push_back(")"); a_result.push_back("HH");
    a_result.push_back(" "); a_result.push_back("WOR0LD"); a_result.push_back("\n");
}

static void TestTokenizerDivideToTokens(std::ifstream& a_file) {
    std::string s(";())!{}[]");
    Tokenizer t(s);

    Tokenizer::Tokens result = t.DivideIntoTokens(a_file);

    Tokenizer::Tokens resultCompare;
    FillTokensResultTokenizer(resultCompare);

    static size_t testNum = 0;
    std::cout << "tokenizer divide into tokens test " <<  ++testNum << ": \t \033[1;31m"
            << ((resultCompare == result) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;

}

static void TestTolower(Tokenizer::Tokens& a_tokens) {
    Manipulator *tolower = new Tolower();
    tolower->Manipulation(a_tokens);

    Tokenizer::Tokens result;
    FillTokensResultTolower(result);

    static size_t testNum = 0;
    std::cout << "tolower test " <<  ++testNum << ": \t\t\t \033[1;31m"
            << ((result == a_tokens) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;

}

static void TestToupper(Tokenizer::Tokens& a_tokens) {
    Manipulator *toupper = new Toupper();
    toupper->Manipulation(a_tokens);

    Tokenizer::Tokens result;
    FillTokensResultToupper(result);

    static size_t testNum = 0;
    std::cout << "toupper test " <<  ++testNum << ": \t\t\t \033[1;31m"
            << ((result == a_tokens) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;

}

static void TestManipulatorHandler(Tokenizer::Tokens& a_tokens) {
    ManipulatorHandler manipulatorHandler(a_tokens);
    Manipulator *tolower = new Tolower();

    manipulatorHandler.AddManipulator(tolower);
    a_tokens = manipulatorHandler.DoAllManipulation();

    Tokenizer::Tokens result;
    FillTokensResultTolower(result);

    static size_t testNum = 0;
    std::cout << "manipulator handler test " <<  ++testNum << ": \t\t \033[1;31m"
            << ((result == a_tokens) ? "SUCCESS" : "FAILED") << "\033[0m" << std::endl;

}

} // experis

int main(int a_argc, char* a_argv[]) {

    std::ifstream file("file.txt");

    //test tokenizer:
    experis::TestTokenizerDivideToTokens(file);
    
    file.close();
    file.open("file.txt");

    std::string s(";())!{}[]");
    experis::Tokenizer tokenizer(s);
    experis::Tokenizer::Tokens result = tokenizer.DivideIntoTokens(file);

    //test tolower:
    experis::TestTolower(result);

    //test toupper:
    experis::TestToupper(result);

    //test manipulator handler:
    experis::TestManipulatorHandler(result);

    file.close();
    
    return 0;
}