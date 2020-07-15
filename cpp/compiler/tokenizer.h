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
	
		virtual queue<string>& DivideToTokens(const string& buffer);

	protected:		

		bool checkIfSpace(const char _first, const char _itr) { return (isspace(_first) || _first == _itr); }

	private:

		queue<string> m_tokens;
		string m_predefineTokens;
		typedef string::const_iterator strItr;
		
		tokenizer(const tokenizer& _tokenize);
		tokenizer& operator=(const tokenizer& _tokenize);
		
};


#endif
