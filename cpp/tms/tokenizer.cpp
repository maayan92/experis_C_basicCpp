#include "tokenizer.hpp"
#include <algorithm>
#include <ctype.h>

namespace experis {

static bool isDelimiter(const char a_element) {
    return isspace(a_element) || (0 == isalnum(a_element));
}

Tokenizer::Tokens& Tokenizer::DivideIntoTokens(std::istream& a_inputFile) {
	std::string wordFromFile;
	while(getline(a_inputFile, wordFromFile)) {
        DivideLineIntoTokens(wordFromFile);
        m_tokens.push_back("\n");
	}
	return m_tokens;
}

void Tokenizer::DivideLineIntoTokens(std::string& a_wordFromFile) {
    Itr wordItrFrom = a_wordFromFile.begin();

    Itr wordItrTo = std::find_if(wordItrFrom, a_wordFromFile.end(), isDelimiter);
    std::string token;
    while(wordItrTo != a_wordFromFile.end()) {
        token = std::string(wordItrFrom,wordItrTo);
        if(0 < token.size()) { m_tokens.push_back(token); }
		
		m_tokens.push_back(std::string(wordItrTo, wordItrTo + 1));
		
		wordItrFrom = wordItrTo + 1;
		wordItrTo = std::find_if(wordItrFrom, a_wordFromFile.end(), isDelimiter);
    }

    token = std::string(wordItrFrom,wordItrTo);
	if(0 < token.size()) { m_tokens.push_back(token); }
}

const Tokenizer::Tokens& Tokenizer::GetTokens() const {
    return m_tokens;
}

} // experis