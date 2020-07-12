#ifndef __ANALYZER_H__
#define __ANALYZER_H__

#include <map>
#include <queue>
#include <set>
#include <string>
#include <iostream>
using namespace std;

class analyzer
{
	public:
	
		virtual ~analyzer() {}
		
		analyzer();
		
		virtual void AnalyzeTokens(queue<string>& _tokens, int _lineNum);
		
		void CheckBrackets();
		
		virtual void ResetAll();
	
	private:
	
		set<string> m_predifineTypes;
		set<string> m_keyWords;
		set<string> m_operators;
		string m_predefineTokens;
		
		set<string> m_variables;
		map<char,int> m_countBrackets;
		
		bool isPreType;
		bool wasIf;
		bool mainFlag;
		int m_countPlus;
		int m_countMinus;
		int m_lineNum;
		
		void Initialize();
		void Reset();
		void CheckTokenCommand(const string& _token);
		bool IsBracket(const string& _token);
		void BracketsClose(char _token);
		void CheckIfLlegalVar(const string& _token);
		void CheckIfVarExist(const string& _token);
		void CheckPreType(const string& _token);
		void PlusOrMinus(int *_counter, int *_reset, bool _isPlus);
};


#endif
