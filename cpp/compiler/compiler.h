#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class tokenizer;
class analyzer;

class compiler
{

	public:
	
		~compiler() {}
		
		compiler();
		
		void Compilation(const string& _fileName);
		
	private:

		tokenizer* m_tokenize;
		analyzer* m_analyze;
		
		void RunCompiler(ifstream& _codeFile);

};




#endif
