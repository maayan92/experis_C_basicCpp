#include "string_t.h"
#include <iostream>
#include <string.h>
#include <new>

// private functions

static const size_t SIZEOF_NULL_TERMINATOR = sizeof('\0');

static char* initialize(const char* a_buffer) {

	size_t memNeeded = strlen(a_buffer) + SIZEOF_NULL_TERMINATOR;
	char* buffer = new(std::nothrow) char[memNeeded];
		
	if(!buffer){ throw "allocation failed!"; }
		
	memcpy(buffer, a_buffer, memNeeded);
	return buffer;
}

// CTOR

String::String()
: m_buffer(initialize("")) {
}

String::String(const char* a_buffer)
: m_buffer(initialize(a_buffer ? a_buffer : "")) {
}

String::String(const String& a_str)
: m_buffer(initialize(a_str.m_buffer ? a_str.m_buffer : "")) {
}

String& String::operator=(const String& a_str) {
	
	if(this != &a_str) {
		delete []m_buffer;
		m_buffer = initialize(a_str.m_buffer);
	}
	
	return *this;
}

unsigned int String::Length()const {
	return strlen(m_buffer);
}

bool String::operator==(const String& a_str)const {
	return (0 == strcmp(m_buffer, a_str.m_buffer));
}

bool String::operator!=(const String& a_str)const {
	return (0 != strcmp(m_buffer, a_str.m_buffer));
}

String::operator int() {

	int i, sum = 0;
	
	for(i = 0; i < strlen(m_buffer) ; ++i) {
		sum += m_buffer[i];
	}
	
	return sum;
}

std::ostream& operator<<(std::ostream& a_os, const String& a_str) {

	a_os << a_str.GetString() << std::endl;
	
	return a_os;
}





