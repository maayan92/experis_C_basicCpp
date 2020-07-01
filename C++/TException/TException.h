#ifndef __T_EXCEPTION__
#define __T_EXCEPTION__

#include "String_t.h"

template <class T>
class TException
{
	public:
	
		TException(T _exception, const String_t _fileName, int _lineNum, const String_t _message);
		
		~TException() {}
		
		T GetException()const { return m_exception; }
		
		const String_t GetExcMessage()const { return m_message; }
		
		const String_t GetFileName()const { return m_fileName; }
		
		int GetLineNumber()const { return m_lineNum; }

	private:
	
		T m_exception;
		String_t m_message;
		String_t m_fileName;
		int m_lineNum;

};

template <class T>
TException<T>::TException(T _exception, const String_t _fileName, int _lineNum, const String_t _message) 
{ 
	m_exception = _exception;
	m_fileName = _fileName; 
	m_lineNum = _lineNum; 
	m_message = _message;
}



#endif
