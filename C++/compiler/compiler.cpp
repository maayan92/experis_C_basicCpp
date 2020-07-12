#include "compiler.h"
#include "tokenizer.h"
#include "analyzer.h"
#include <queue>
#include <fstream>

compiler::compiler()
{
	m_analyze = new analyzer();
	m_tokenize = new tokenizer();
}

void compiler::Compilation(const string& _fileName)
{
	ifstream codeFile(_fileName.c_str());
	
	if(codeFile.fail())
	{
		cout << "file " << _fileName << " not found" << endl;
		return;
	}
	
	RunCompiler(codeFile);
}

/////////////////
void PrintQueue(queue<string>& tokens)
{
	while(!tokens.empty())
	{
		cout << tokens.front() << " ";
		tokens.pop();
	}
	cout << endl;
}
////////////////

void compiler::RunCompiler(ifstream& _codeFile)
{
	string buffer;
	int lineNum = 1;
	
	while(getline(_codeFile,buffer))
	{
		queue<string>& tokens = m_tokenize->DivideToTokens(buffer);
		
		//PrintQueue(tokens);
		
		m_analyze->AnalyzeTokens(tokens,lineNum);
		++lineNum;
	}
	m_analyze->CheckBrackets();
	m_analyze->ResetAll();
}





