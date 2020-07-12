#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <queue>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class tokenizer
{
	public:
	
		virtual ~tokenizer() {}
	
		tokenizer():m_predefineTokens("()[]{};<>=+-*&"){}
	
		virtual queue<string>& DivideToTokens(string buffer);
		
	private:

		queue<string> m_tokens;
		string m_predefineTokens;
		typedef string::iterator strItr;
		
		tokenizer(const tokenizer& _tokenize);
		tokenizer& operator=(const tokenizer& _tokenize);
		
		static bool checkIfSpace(const char _first, const char _itr) { return (isspace(_first) || _first == _itr); }
};


#endif
