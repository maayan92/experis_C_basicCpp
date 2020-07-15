#ifndef __STRING_H__
#define __STRING_H__

#include <iosfwd>

class String{
public:

// DTOR
	~String() { delete[] m_buffer; }
	
// CTOR
	String();
	String(const char* a_buffer);
	String(const String& a_str);
	String& operator=(const String& a_str);
	
// mem functions
	const char* GetString()const { return m_buffer; }
	unsigned int Length()const;
	
// operators
	bool operator==(const String& a_str)const;
	bool operator!=(const String& a_str)const;
	
	char& operator[](unsigned int a_index) { return m_buffer[a_index]; }
	operator int();
	
private:
	static const unsigned int DEFAULT_CAPACITY = 8;
	
	char* m_buffer;
};

std::ostream& operator<<(std::ostream& a_print, const String& a_str);

#endif
