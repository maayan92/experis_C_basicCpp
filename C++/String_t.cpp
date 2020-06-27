#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctype.h>
#include "String_t.h"
using namespace std;

unsigned int String_t::m_dCapacy = 8;
unsigned int String_t::numOfStrings = 0;
bool String_t::m_caseSens = true;

// Operators

String_t& String_t::operator=(String_t& _s)
{
	if(this != &_s)
	{
		delete[] m_buffer;
				
		m_buffer = CreateFrom(_s.m_buffer);
	}
	
	return *this;
}

String_t& String_t::operator+=(const char *_str)
{
	if(_str)
	{
		Concatenation(m_buffer,_str);
	}
	
	return *this;
}

String_t& String_t::operator+=(String_t& _s)
{
	Concatenation(m_buffer,_s.m_buffer);
	
	return *this;
}

ostream& operator<<(ostream& os, const String_t& _s)
{
	os << "string value -> " << _s.GetString();
	
	return os;
}

istream& operator>>(istream& _is, String_t& _s)
{
	char *temp = new char[_s.GetMemCapacity()];//TODO
	_is >> temp;
	
	_s.SetString(temp);
	
	return _is;
}

bool String_t::operator<(const String_t& _s)const
{
	int result = (true == m_caseSens) ? strcmp(m_buffer,_s.m_buffer) : strcasecmp(m_buffer,_s.m_buffer);
	
	return (0 > result) ? true : false; 
}

bool String_t::operator>(const String_t& _s)const
{
	int result = (true == m_caseSens) ? strcmp(m_buffer,_s.m_buffer) : strcasecmp(m_buffer,_s.m_buffer);
	
	return (0 < result) ? true : false;
}

bool String_t::operator<=(const String_t& _s)const
{
	int result = (true == m_caseSens) ? strcmp(m_buffer,_s.m_buffer) : strcasecmp(m_buffer,_s.m_buffer);
	
	return (0 >= result) ? true : false; 
}

bool String_t::operator>=(const String_t& _s)const
{
	int result = (true == m_caseSens) ? strcmp(m_buffer,_s.m_buffer) : strcasecmp(m_buffer,_s.m_buffer);
	
	return (0 <= result) ? true : false; 
}

bool String_t::operator==(const String_t& _s)const
{
	int result = (true == m_caseSens) ? strcmp(m_buffer,_s.m_buffer) : strcasecmp(m_buffer,_s.m_buffer);
	
	return (0 == result) ? true : false; 
}

bool String_t::operator!=(const String_t& _s)const
{
	int result = (true == m_caseSens) ? strcmp(m_buffer,_s.m_buffer) : strcasecmp(m_buffer,_s.m_buffer);
	
	return (0 != result) ? true : false;
}

char String_t::operator[](int _index)const
{
	return (_index < strlen(m_buffer)) ? m_buffer[_index] : '\0';
}

char& String_t::operator[](int _index)
{
	size_t size = strlen(m_buffer);
	
	return (_index < size) ? m_buffer[_index] : m_buffer[size];
}

// Mem functions

void String_t::SetString(const char* _str)
{
	delete[] m_buffer;
	
	m_buffer = CreateFrom(_str);
}

int String_t::Compare(const char* _str)const
{
	int result = strcmp(m_buffer,_str);
	
	return (0 > result) ? 1 : ((0 < result) ? 2 : 0) ;
}

void String_t::Print()const
{
	cout << m_buffer << "\n";
}

String_t& String_t::Lower()
{
	int i = 0;
	
	while(m_buffer[i] != '\0')
	{
		m_buffer[i] = tolower(m_buffer[i]);
		++i;
	}
	
	return *this;
}

String_t& String_t::Upper()
{
	int i = 0;
	
	while(m_buffer[i] != '\0')
	{
		m_buffer[i] = toupper(m_buffer[i]);
		++i;
	}
	
	return *this;
}

String_t& String_t::Prepend(const char* _str)
{
	if(_str)
	{
		Concatenation(_str,m_buffer);
	}

	return *this;
}

String_t& String_t::Prepend(const String_t& _s)
{
	Concatenation(_s.m_buffer,m_buffer);
	
	return *this;
}

size_t String_t::Contains(const char* _str)const
{
	return (!strstr(m_buffer,_str)) ? 0 : 1;
}

int String_t::FirstOccur(char _c)const
{
	return strchr(m_buffer,_c) - m_buffer;
}

int String_t::LastOccur(char _c)const
{
	return strrchr(m_buffer,_c) - m_buffer;
}

String_t String_t::operator()(int _start, int _len)
{
	int size = strlen(m_buffer);
	String_t s;

	strncpy(s.m_buffer,m_buffer + _start,_len);
	
	return s;
}

/* PRIVATE */

void String_t::Initialize(const char *_str)
{
	m_capacity = m_dCapacy;
	m_buffer = CreateFrom(_str);
	++numOfStrings;
}

char* String_t::CreateFrom(const char *_str)
{
	char *temp;
	
	if(!_str)
	{
		temp = new char[m_capacity];
		temp[0] = '\0';
	}
	else
	{
		this->SetBiggerCapacity(strlen(_str) + 1);
		
		temp = new char[m_capacity];
		strcpy(temp,_str);
	}
	
	return temp;
}

void String_t::Concatenation(const char *_str1, const char *_str2)
{
	this->SetBiggerCapacity(strlen(_str1) + strlen(_str2) + 1);

	char *temp = new char[m_capacity];
	
	strcpy(temp,_str1);
	strcat(temp,_str2);
	
	delete[] m_buffer;
	
	m_buffer = CreateFrom(temp);
		
	delete[] temp;
}

void String_t::SetBiggerCapacity(unsigned int _size)
{
	while(m_capacity < _size)
	{
		m_capacity *= 2;
	}
}








		
