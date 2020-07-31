#include "tokenizer.hpp"

int main() {

    std::ifstream file("file.txt");

    std::string s(";)!}");
    experis::Tokenizer t(s);

    experis::Tokenizer::Tokens result = t.DivideIntoTokens(file);

    while(!result.empty()) {
        std::cout << result.front();
        result.pop();
    }
    std::cout << std::endl;

    return 0;
}