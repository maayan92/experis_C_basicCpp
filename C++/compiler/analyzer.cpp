#include "analyzer.h"
#include <ctype.h>

analyzer::analyzer():m_predefineTokens("()[]{};<>=+-*&")
{
	wasIf = false;
	mainFlag = false;
	Reset();
	
	Initialize();
	m_countBrackets.insert(pair<char,int>('(',0));
	m_countBrackets.insert(pair<char,int>('[',0));
	m_countBrackets.insert(pair<char,int>('{',0));
}

void analyzer::AnalyzeTokens(queue<string>& _tokens, int _lineNum)
{
	size_t i = 0;
	m_lineNum = _lineNum;
	
	if(_tokens.empty())
	{
		return;
	}

	if(!mainFlag && 0 != _tokens.front().compare("main"))
	{
		cout << "\033[1;31mline " << m_lineNum << "\t- error, no 'main' before\033[0m" << endl;
		mainFlag = true;
	}
	
	string token = _tokens.front();

	while(!_tokens.empty())
	{
		CheckTokenCommand(token);
		
		_tokens.pop();
		
		token = _tokens.front();
	}
}

void analyzer::CheckBrackets()
{
	if(m_countBrackets['(']) cout << endl << "\033[1;31m// error – " << m_countBrackets['('] << " '(' " << "not closed\033[0m";
	if(m_countBrackets['[']) cout << endl << "\033[1;31m// error – " << m_countBrackets['['] << " '[' " << "not closed\033[0m";
	if(m_countBrackets['{']) cout << endl << "\033[1;31m// error – " << m_countBrackets['{'] << " '{' " << "not closed\033[0m";
	
	cout << endl;
}

void analyzer::ResetAll()
{
	wasIf = false;
	mainFlag = false;
	Reset();
	
	m_countBrackets['('] = 0;
	m_countBrackets['['] = 0;
	m_countBrackets['{'] = 0;
}

void analyzer::CheckTokenCommand(const string& _token)
{
	if(m_predifineTypes.find(_token) != m_predifineTypes.end())
	{
		if(isPreType)
		{
			cout << "\033[1;31mline " << m_lineNum << "\t- error, multiple type declaration\033[0m" << endl;
			isPreType = false;
		}
		else { isPreType = true; }
		return;
	}
		
	if(IsBracket(_token)){ CheckPreType(_token); return; }
	
	if(!_token.compare("if"))
	{
		CheckPreType(_token);
		wasIf = true; 
		Reset();
		return;
	}
	
	if(!_token.compare("else"))
	{
		CheckPreType(_token);
		if(!wasIf){ cout << "\033[1;31mline " << m_lineNum << "\t- error, 'else' without 'if'\033[0m" << endl; }
		
		Reset();
		return;
	}
	
	if(!_token.compare("+"))
	{
		CheckPreType(_token);
		PlusOrMinus(&m_countPlus,&m_countMinus,true);
		return;
	}
	if(!_token.compare("-"))
	{
		CheckPreType(_token);
		PlusOrMinus(&m_countMinus,&m_countPlus,false);
		return;
	}
	
	if(isPreType){ CheckIfLlegalVar(_token); }
	else{ CheckIfVarExist(_token); }
					
	Reset();
}

void analyzer::PlusOrMinus(int *_counter, int *_reset, bool _isPlus)
{
	++(*_counter);
					
	if(3 == *_counter)
	{
		cout << "\033[1;31mline " << m_lineNum << "\t- error, no operator " << (_isPlus ? "+++" : "---") << "\033[0m" << endl;
		(*_counter) = 0;
	}
					
	(*_reset) = 0;
}

void analyzer::CheckPreType(const string& _token)
{
	if(isPreType)
	{
		cout << "\033[1;31mline " << m_lineNum << "\t- error, illegal variable\033[0m" << endl;
		isPreType = false;
	}
}

void analyzer::CheckIfLlegalVar(const string& _token)
{
	if(('_' == _token[0] || isalpha(_token[0])) && m_keyWords.find(_token) == m_keyWords.end())
	{
		if(m_variables.find(_token) == m_variables.end()){ m_variables.insert(_token); }
		
		else{ cout << "\033[1;31mline " << m_lineNum << "\t- error, " << _token << " has already declared\033[0m" << endl; }
	}
	else
	{
		cout << "\033[1;31mline " << m_lineNum << "\t- error, '" << _token << "' illegal variable name\033[0m" << endl;
	}
}

void analyzer::CheckIfVarExist(const string& _token)
{
	if(m_keyWords.find(_token) == m_keyWords.end() && m_operators.find(_token) == m_operators.end() && m_predefineTokens.find(_token[0]) == string::npos)
	{
		if('_' == _token[0] || isalpha(_token[0]))
		{
			if(m_variables.find(_token) == m_variables.end())
			{
				cout << "\033[1;31mline " << m_lineNum << "\t- error, '" << _token << "' was not declared\033[0m" << endl;
			}
		}
		else
		{
			cout << "\033[1;31mline " << m_lineNum << "\t- error, '" << _token << "' unknown word\033[0m" << endl;
		}
	}
	
}

bool analyzer::IsBracket(const string& _token)
{
	switch(_token[0])
	{
		case '(': m_countBrackets['(']++; break;
			
		case ')': BracketsClose('('); break;
			
		case '[': m_countBrackets['[']++; break;
			
		case ']': BracketsClose('['); break;
			
		case '{': m_countBrackets['{']++; break;
			
		case '}': BracketsClose('{'); break;
	
		default: return false;
	}
	
	return true;
}

void analyzer::BracketsClose(char _token)
{
	if(0 == m_countBrackets[_token])
	{
		cout << "\033[1;31mline " << m_lineNum << "\t- error, illegal '" 
			<< (('(' == _token) ? ")" : (('[' == _token) ? "]" : "}")) << "'\033[0m" << endl;
	}
	
	else{ m_countBrackets[_token]--; }
}

void analyzer::Reset()
{
	isPreType = false;
	m_countPlus = 0;
	m_countMinus = 0;
}


void analyzer::Initialize()
{
	string strKeyWords[] = {"if","else","for","while","class","private","public","protected","main","const","virtual"};
	m_keyWords = set<string>(strKeyWords,strKeyWords + sizeof(strKeyWords)/sizeof(strKeyWords[0]));
	
	
	string strOperators[] = {"++","--","==","->","=","+","-","*","&","<<",">>"};
	m_operators = set<string>(strOperators,strOperators + sizeof(strOperators)/sizeof(strOperators[0]));
	
	
	string strPredifineTypes[] = {"char","short","int","long","float","double","void"};
	m_predifineTypes = set<string>(strPredifineTypes,strPredifineTypes + sizeof(strPredifineTypes)/sizeof(strPredifineTypes[0]));
}






