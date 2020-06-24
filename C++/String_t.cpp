#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctype.h>
#include "String_t.h"
using namespace std;

#define LENGTH 200

String_t::String_t()
{
	buffer = CreateFrom(0);
}

String_t::String_t(const char* _str)
{
	buffer = CreateFrom(_str);
}

String_t::String_t(const String_t& _s)
{
	buffer = CreateFrom(_s.buffer);
}

String_t::~String_t()
{
	delete[] buffer;
}

String_t& String_t::operator=(String_t& _s)
{
	if(this != &_s)
	{
		delete[] buffer;
				
		buffer = CreateFrom(_s.buffer);
	}
	
	return *this;
}

size_t String_t::Length()const
{
	return strlen(buffer);
}

void String_t::SetString(const char* _str)
{
	delete[] buffer;
	
	buffer = CreateFrom(_str);
}

const char* String_t::GetString()const
{
	return buffer;
}

int String_t::Compare(const char* _str)const
{
	int result = strcmp(buffer,_str);
	
	return (0 > result) ? 1 : ((0 < result) ? 2 : 0) ;
}

void String_t::Print()const
{
	cout << buffer << "\n";
}

String_t& String_t::Lower()
{
	int i = 0;
	
	while(buffer[i] != '\0')
	{
		buffer[i] = tolower(buffer[i]);
		++i;
	}
	
	return *this;
}

String_t& String_t::Upper()
{
	int i = 0;
	
	while(buffer[i] != '\0')
	{
		buffer[i] = toupper(buffer[i]);
		++i;
	}
	
	return *this;
}

String_t& String_t::Prepend(const char* _str)
{
	if(_str)
	{
		Concatenation(_str,buffer);
	}

	return *this;
}

String_t& String_t::Prepend(const String_t& _s)
{
	if(_s.buffer)
	{
		Concatenation(_s.buffer,buffer);
	}
	
	return *this;
}

size_t String_t::Contains(const char* _str)const
{
	return (!strstr(buffer,_str)) ? 0 : 1;
}

ostream& operator<<(ostream& os, const String_t& _s)
{
	os << "Buffer value -> " << _s.GetString();
	
	return os;
}

istream& operator>>(istream& _is, String_t& _s)
{
	char *temp = new char[LENGTH];
	_is >> temp;
	
	_s.SetString(temp);
	
	return _is;
}

String_t& String_t::operator+=(const char *_str)
{
	if(_str)
	{
		Concatenation(buffer,_str);
	}
	
	return *this;
}

String_t& String_t::operator+=(String_t& _s)
{
	if(_s.buffer)
	{
		Concatenation(buffer,_s.buffer);
	}
	
	return *this;
}

bool String_t::operator<(const String_t& _s)const
{
	return (0 > strcmp(buffer,_s.buffer)) ? true : false; 
}

bool String_t::operator>(const String_t& _s)const
{
	return (0 < strcmp(buffer,_s.buffer)) ? true : false; 
}

bool String_t::operator<=(const String_t& _s)const
{
	int result = strcmp(buffer,_s.buffer);
	
	return (0 >= result) ? true : false; 
}

bool String_t::operator>=(const String_t& _s)const
{
	int result = strcmp(buffer,_s.buffer);
	
	return (0 <= result) ? true : false; 
}

bool String_t::operator==(const String_t& _s)const
{
	return (0 == strcmp(buffer,_s.buffer)) ? true : false; 
}

bool String_t::operator!=(const String_t& _s)const
{
	return (0 != strcmp(buffer,_s.buffer)) ? true : false; 
}

char String_t::operator[](int _index)const
{
	return (_index < strlen(buffer)) ? buffer[_index] : '\0';
}

char String_t::operator[](int _index)
{
	return (_index < strlen(buffer)) ? buffer[_index] : '\0';
}

int String_t::FirstOccur(char _c)const
{
	return strchr(buffer,_c) - buffer;
}

int String_t::LastOccur(char _c)const
{
	return strrchr(buffer,_c) - buffer;
}

/* PRIVATE */

char* String_t::CreateFrom(const char *_str)
{
	char *temp;
	
	if(!_str)
	{
		temp = new char[1];
		temp[0] = '\0';
	}
	else
	{
		temp = new char[strlen(_str) + 1];
		strcpy(temp,_str);
	}
	
	return temp;
}

void String_t::Concatenation(const char *_str1, const char *_str2)
{
	char *temp = new char[strlen(_str1) + strlen(_str2) + 2];
	
	strcpy(temp,_str1);
	strcat(temp,_str2);
	
	delete[] buffer;
	
	buffer = CreateFrom(temp);
		
	delete[] temp;
}



		
