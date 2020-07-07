#ifndef __ASCII_IO__
#define __ASCII_IO__

#include "String_t.h"
#include "virtIO.h"
#include "TException.h"

class asciiIO:public virtIO
{
	public:
		
	// DTOR
	
		virtual ~asciiIO() {}
		
	// CTOR
		
		asciiIO() {}
		
		asciiIO(const String_t& _name, const String_t& _mode) { Open(_name,_mode); }

	// write to file
		 
		virtual asciiIO& operator<<(int _value) { return WriteToFile(_value,"%d"); }
		virtual asciiIO& operator<<(float _value) { return WriteToFile(_value,"%f"); }
		virtual asciiIO& operator<<(char _value) { return WriteToFile(_value,"%c"); }
		virtual asciiIO& operator<<(short _value) { return WriteToFile(_value,"%hi"); }
		virtual asciiIO& operator<<(long _value) { return WriteToFile(_value,"%li"); }
		virtual asciiIO& operator<<(double _value) { return WriteToFile(_value,"%lf"); }
		virtual asciiIO& operator<<(unsigned int _value) { return WriteToFile(_value,"%u"); }
		virtual asciiIO& operator<<(unsigned char _value) { return WriteToFile(_value,"%c"); }
		virtual asciiIO& operator<<(unsigned short _value) { return WriteToFile(_value,"%hu"); }
		virtual asciiIO& operator<<(unsigned long _value) { return WriteToFile(_value,"%lu"); }

	// read from file
		
		virtual asciiIO& operator>>(int& _value) { return ReadFromFile(_value,"%d"); }
		virtual asciiIO& operator>>(float& _value) { return ReadFromFile(_value,"%f"); }
		virtual asciiIO& operator>>(char& _value) { return ReadFromFile(_value,"%c"); }
		virtual asciiIO& operator>>(short& _value) { return ReadFromFile(_value,"%hi"); }
		virtual asciiIO& operator>>(long& _value) { return ReadFromFile(_value,"%li"); }
		virtual asciiIO& operator>>(double& _value) { return ReadFromFile(_value,"%lf"); }
		virtual asciiIO& operator>>(unsigned int& _value) { return ReadFromFile(_value,"%u"); }
		virtual asciiIO& operator>>(unsigned char& _value) { return ReadFromFile(_value,"%c"); }
		virtual asciiIO& operator>>(unsigned short& _value) { return ReadFromFile(_value,"%hu"); }
		virtual asciiIO& operator>>(unsigned long& _value) { return ReadFromFile(_value,"%lu"); }
	
	private:

		asciiIO(const asciiIO& _bin);
		asciiIO& operator=(const asciiIO& _ascii);
		
		template<class T>
		asciiIO& WriteToFile(const T& _value, const String_t& _format);
		
		template<class T>
		asciiIO& ReadFromFile(T& _value, const String_t& _format);
};

// private functions

template<class T>
asciiIO& asciiIO::WriteToFile(const T& _value, const String_t& _format)
{
	if(!this->GetFile())
	{
		SetStatus(writeErr_e);
		throw TException<status>(writeErr_e,__FILE__,__LINE__,"file is not open!");
	}
	
	if(GetFileMode() == "r")
	{
		SetStatus(writeErr_e);
		throw TException<status>(writeErr_e,__FILE__,__LINE__,"wrong mode for write!");
	}
	
	fprintf(this->GetFile(),_format.GetString(),_value);
	SetStatus(ok_e);
	
	return *this;
}
		
template<class T>
asciiIO& asciiIO::ReadFromFile(T& _value, const String_t& _format)
{
	if(!this->GetFile())
	{
		SetStatus(readErr_e);
		throw TException<status>(readErr_e,__FILE__,__LINE__,"file is not open!");
	}
	
	if(GetFileMode() == "a" || GetFileMode() == "w")
	{
		SetStatus(readErr_e);
		throw TException<status>(readErr_e,__FILE__,__LINE__,"wrong mode for read!");
	}
	
	fscanf(this->GetFile(),_format.GetString(),&_value);
	SetStatus(ok_e);
	
	return *this;
}




#endif
