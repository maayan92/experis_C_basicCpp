#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "String_t.h"
using namespace std;

String_t::String_t()
{
	buffer = NULL;
}

String_t::String_t(const char* _str)
{
	if(!_str)
	{
		buffer = NULL;
		return;
	}
	
	buffer = CreateFrom(_str);
}

String_t::String_t(const String_t& _s)
{
	if(!_s.buffer)
	{
		buffer = NULL;
		return;
	}
	
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
				
		buffer = (!_s.buffer) ? NULL : CreateFrom(_s.buffer);
	}
	
	return *this;
}

size_t String_t::Length()const
{
	if(!buffer)
	{
		return 0;
	}
	
	return strlen(buffer);
}

void String_t::SetString(const char* _str)
{
	if(!_str)
	{
		buffer = NULL;
		return;
	}
	if(!buffer)
	{
		buffer = CreateFrom(_str);
		return;
	}
	
	strcpy(buffer,_str);
}

const char* String_t::GetString()const
{
	return buffer;
}

int String_t::Compare(const char* _str)const
{
	int result = strcmp(buffer,_str);
	
	if(0 < result)
	{
		return 1;
	}
	
	if(0 > result)
	{
		return 2;
	}
	
	return 0;
}

void String_t::Print()const
{
	cout << buffer << "\n";
}

/* PRIVATE */

char* String_t::CreateFrom(const char *_str)
{
	char *temp = new char[strlen(_str) + 1];
	
	strcpy(temp,_str);
	
	return temp;
}





		
