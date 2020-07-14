#include "string_t.h"
#include <iostream>
#include <new>

unsigned int String::dSize = 32;

String::String()
:m_buffer(initialize(0)){
}

String::String(const char* a_buffer)
:m_buffer(initialize(a_buffer)){
}

String::String(const String& a_str)
:m_buffer(initialize(a_str.m_buffer)){
}

String& String::operator=(const String& a_str){
	
	if(this != &a_str)
	{
		delete []m_buffer;
		m_buffer = initialize(a_str.m_buffer);
	}
	
	return *this;
}

String::operator int(){

	int i, sum = 0;
	
	for(i = 0;i < strlen(m_buffer);++i){
		sum += m_buffer[i];
	}
	
	return sum;
}

std::ostream& operator<<(std::ostream& a_os, const String& a_str){

	a_os << a_str.GetString() << std::endl;
	
	return a_os;
}

// private functions

char* String::initialize(const char* a_buffer){
	
	char* buffer;
	
	if(!a_buffer){
	
		buffer = new(std::nothrow) char[dSize];
		
		if(!buffer){ throw "allocation failed!"; }
		
		buffer[0] = '\0';
	}
	else{
		buffer = new(std::nothrow) char[strlen(a_buffer)+1];
		
		if(!buffer){ throw "allocation failed!"; }
		
		strcpy(buffer,a_buffer);
	}
	
	return buffer;
}






