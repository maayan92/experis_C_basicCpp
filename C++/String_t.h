#ifndef __STRING_T_H__
#define __STRING_T_H__

#include <iostream>
using namespace std;

class String_t
{
	public:
		
		/*
			Description: destructor.
		*/
		~String_t();
		/*
			Description: default constructor.
		*/
		String_t();
		/*
			Description: constructor, create the object with initialization.
			Input: _str - the initial value of buffer.
		*/
		String_t(const char* _str);
		/*
			Description: copy constructor.
			Input: _s - the object to copy.
		*/
		String_t(const String_t& _s);
		/*
			Description: copy all _s members to this mambers.
			Input: _s - the object to copy.
			Return:
		*/
		String_t& operator=(String_t& _s);
		/*
			Description: get the length of buffer.
			Return:
		*/
		size_t Length()const;
		/*
			Description: set the buffer to _str.
			Input: _str - the new value to buffer.
		*/
		void SetString(const char* _str);
		/*
			Description: get the buffer.
			Return:
		*/
		const char* GetString()const;
		/*
			Description: compare the string _str to the object buffer. 
			Input:
			Return: return 0 if they are equal, 1 if 
		*/
		int Compare(const char* _str)const;
		/*
			Description: print the buffer.
		*/
		void Print()const;
		
		
		String_t& Lower();
		
		String_t& Upper();
		
		String_t& Prepend(const char* _str);
		
		String_t& Prepend(const String_t& _s);
		
		size_t Contains(const char* _str)const;
		
		String_t& operator+=(const char *_str);

		String_t& operator+=(String_t& _s);
		
		bool operator<(const String_t& _s)const;
		
		bool operator>(const String_t& _s)const;
		
		bool operator<=(const String_t& _s)const;
		
		bool operator>=(const String_t& _s)const;
		
		bool operator==(const String_t& _s)const;
		
		bool operator!=(const String_t& _s)const;
		
		char operator[](int _index)const;
		
		char operator[](int _index);
		
		int FirstOccur(char _c)const;
		
		int LastOccur(char _c)const;
		
		
		
	private:
	
		char *buffer;
		
		char* CreateFrom(const char *_str);
		
		void Concatenation(const char *_str1, const char *_str2);
};

	ostream& operator<<(ostream& os, const String_t& _s);
		
	istream& operator>>(istream& _is, String_t& _s);




#endif
