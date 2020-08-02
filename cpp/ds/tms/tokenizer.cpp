#include "tokenizer.hpp"
#include <algorithm>

namespace experis {

Tokenizer::Tokenizer(std::string& a_delimiters)
: m_delimiters(a_delimiters) {
}

static bool checkIfSpace(const char _first, const char _itr) { 
    return (isspace(_first) || _first == _itr);
}

Tokenizer::Tokens& Tokenizer::DivideIntoTokens(std::ifstream& a_inputFile) {
	std::string wordFromFile;
	while(getline(a_inputFile, wordFromFile)) {
        DivideLineIntoTokens(wordFromFile);
        m_tokens.push_back("\n");
	}
	return m_tokens;
}

void Tokenizer::DivideLineIntoTokens(std::string& a_wordFromFile) {
    Itr wordItrFrom = a_wordFromFile.begin();
	Itr delimiterItrBegin = m_delimiters.begin(), delimiterItrEnd = m_delimiters.end();

    Itr wordItrTo = find_first_of(wordItrFrom, a_wordFromFile.end(), delimiterItrBegin, delimiterItrEnd, checkIfSpace);
    std::string token;
    while(wordItrTo != a_wordFromFile.end()) {
        token = std::string(wordItrFrom,wordItrTo);
        if(0 < token.size()) { m_tokens.push_back(token); }
		
		m_tokens.push_back(std::string(wordItrTo, wordItrTo + 1));
		
		wordItrFrom = wordItrTo + 1;
		wordItrTo = find_first_of(wordItrFrom, a_wordFromFile.end(), delimiterItrBegin, delimiterItrEnd, checkIfSpace);
    }

    token = std::string(wordItrFrom,wordItrTo);
	if(0 < token.size()) { m_tokens.push_back(token); }
}

void Tokenizer::SetTokensToFile(std::ostream& a_outFile) const {
    for(size_t position = 0 ; position < m_tokens.size() ; ++position) {
        a_outFile <<  m_tokens[position];
    }
}

const Tokenizer::Tokens& Tokenizer::GetTokens() const {
    return m_tokens;
}

} // experis