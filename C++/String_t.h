#ifndef __STRING_T_H__
#define __STRING_T_H__

#include <iostream>
using namespace std;

class String_t
{
	public:
	
	// DTOR
		
		~String_t() { delete[] m_buffer; --numOfStrings; }
		
	// CTOR

		/*default constructor*/
		String_t() { Initialize(0); }
		
		/*Description: constructor with initialization value*/
		String_t(const char* _str) { Initialize(_str); }
		
		/*copy constructor*/
		String_t(const String_t& _s) { Initialize(_s.m_buffer); }
		
	// Member functions
		
		/*get the length of buffer*/
		size_t Length()const { return strlen(m_buffer); }
		
		/*set _str to the buffer*/
		void SetString(const char* _str);
		
		/*get the buffer*/
		const char* GetString()const { return m_buffer; }
		
		/*compare the string _str to the object buffer*/
		int Compare(const char* _str)const;
		
		/*print the buffer*/
		void Print()const;
		
		/*change upper chars to lower chars*/
		String_t& Lower();
		
		/*change lower chars to upper chars*/
		String_t& Upper();
		
		/*concatenate _str to the beginning of the buffer*/
		String_t& Prepend(const char* _str);
		
		/*concatenate _s's buffer to the beginning of the buffer*/
		String_t& Prepend(const String_t& _s);
		
		/*check if substring _str is in the buffer*/
		size_t Contains(const char* _str)const;
		
		/*get the first occurrence of char _c in the buffer*/
		int FirstOccur(char _c)const;
		
		/*get the last occurrence of char _c in the buffer*/
		int LastOccur(char _c)const;
		
	// Operators
		
		/*Copy all _s members to this members*/
		String_t& operator=(String_t& _s);
		
		/*Add _str to the buffer*/
		String_t& operator+=(const char *_str);
		
		/*Add _s's bubffer to the buffer*/
		String_t& operator+=(String_t& _s);
		
		/*Return true if my buffer is < than _s's buffer*/
		bool operator<(const String_t& _s)const;
		
		/*Return true if my buffer is > than _s's buffer*/
		bool operator>(const String_t& _s)const;
		
		/*Return true if my buffer is <= than _s's buffer*/
		bool operator<=(const String_t& _s)const;
		
		/*Return true if my buffer is >= than _s's buffer*/
		bool operator>=(const String_t& _s)const;
		
		/*Return true if my buffer is == to _s's buffer*/
		bool operator==(const String_t& _s)const;
		
		/*Return true if my buffer is != from _s's buffer*/
		bool operator!=(const String_t& _s)const;
		
		/*return the char in _index position*/
		char operator[](int _index)const;
		
		/*set char at position _index*/
		char& operator[](int _index);
		
		unsigned int GetMemCapacity()const{ return m_capacity; }
		
		String_t operator()(int _start, int _len);
		
	// Static functions
		
		static void SetDCapacity(unsigned int _newCapacity) { m_dCapacy = _newCapacity; }
		
		static unsigned int GetDCapacity() { return m_dCapacy; }
		
		static bool GetCaseSens(){ return m_caseSens; }
		
		inline static bool SetCaseSens(bool _newCaseSens);
		
	private:
	
		char *m_buffer;
		unsigned int m_capacity;
		
		static bool m_caseSens;
		static unsigned int m_dCapacy;
		static unsigned int numOfStrings;
		
		// sub functions
		
		void Initialize(const char *_str);
		
		char* CreateFrom(const char *_str);
		
		void Concatenation(const char *_str1, const char *_str2);

		void SetBiggerCapacity(unsigned int _size);
};

	// stream operators
	
	ostream& operator<<(ostream& os, const String_t& _s);
		
	istream& operator>>(istream& _is, String_t& _s);
	
	inline bool String_t::SetCaseSens(bool _newCaseSens) 
	{ 
		bool temp = String_t::m_caseSens;
		String_t::m_caseSens = _newCaseSens;
		return temp;				 
	}




#endif
