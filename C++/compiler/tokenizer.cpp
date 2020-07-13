#include "tokenizer.h"
#include <algorithm>

queue<string>& tokenizer::DivideToTokens(const string& buffer)
{
	string token;
	
	strItr itr, fromItr = buffer.begin();
	strItr tokenItrB = m_predefineTokens.begin(), tokenItrE = m_predefineTokens.end();
	
	itr = find_first_of(fromItr,buffer.end(),tokenItrB,tokenItrE,checkIfSpace);
	while(itr != buffer.end())
	{
		token = string(fromItr,itr);
		if(0 < token.size()){ m_tokens.push(token); }
		
		if(!isspace(*itr))
		{
			m_tokens.push(string(itr,itr+1));
		}
		
		fromItr = itr + 1;
		itr = find_first_of(fromItr,buffer.end(),tokenItrB,tokenItrE,checkIfSpace);
	}
	
	token = string(fromItr,itr);
	if(0 < token.size()){ m_tokens.push(token); }
	
	return m_tokens;
}


