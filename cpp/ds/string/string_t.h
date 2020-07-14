#ifndef __STRING_H__
#define __STRING_H__

#include <string.h>
#include <iostream>

class String{
public:

// DTOR
	~String() { delete []m_buffer; }
	
// CTOR
	
	String();
	
	String(const char* a_buffer);
	
	String(const String& a_str);
	
	String& operator=(const String& a_str);
	
	const char* GetString()const { return m_buffer; }
	
	unsigned int Length()const { return strlen(m_buffer); }
	
	bool operator==(const String& a_str)const { return !strcmp(m_buffer,a_str.m_buffer); }
	
	bool operator!=(const String& a_str)const { return strcmp(m_buffer,a_str.m_buffer); }
	
	char& operator[](unsigned int a_index) { return m_buffer[a_index]; }
	
	operator int();
	
private:
	char* m_buffer;
	
	static unsigned int dSize;
	
	char* initialize(const char* a_buffer);
};

std::ostream& operator<<(std::ostream& a_print, const String& a_str);





#endif
