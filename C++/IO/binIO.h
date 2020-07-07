#ifndef __BIN_IO__
#define __BIN_IO__

#include "String_t.h"
#include "virtIO.h"
#include "TException.h"
#include <stdlib.h>

class binIO:public virtIO
{
	public:
		
	// DTOR
		
		~binIO() {}
		
	// CTOR
		
		binIO() { m_readWrite = NO_R_NO_W; }
		
		binIO(const String_t& _name, const String_t& _mode){ Open(_name,_mode); m_readWrite = NO_R_NO_W; }
		
		enum Flag
		{
			NO_R_NO_W,
			READ,
			WRITE
		};
		
	// write to file
		 
		virtual binIO& operator<<(int _value) { return WriteToFile(_value); }
		virtual binIO& operator<<(float _value) { return WriteToFile(_value); }
		virtual binIO& operator<<(char _value) { return WriteToFile(_value); }
		virtual binIO& operator<<(short _value) { return WriteToFile(_value); }
		virtual binIO& operator<<(long _value) { return WriteToFile(_value); }
		virtual binIO& operator<<(double _value) { return WriteToFile(_value); }
		virtual binIO& operator<<(unsigned int _value) { return WriteToFile(_value); }
		virtual binIO& operator<<(unsigned char _value) { return WriteToFile(_value); }
		virtual binIO& operator<<(unsigned short _value) { return WriteToFile(_value); }
		virtual binIO& operator<<(unsigned long _value) { return WriteToFile(_value); }

	// read from file
		
		virtual binIO& operator>>(int& _value) { return ReadFromFile(_value); }
		virtual binIO& operator>>(float& _value) { return ReadFromFile(_value); }
		virtual binIO& operator>>(char& _value) { return ReadFromFile(_value); }
		virtual binIO& operator>>(short& _value) { return ReadFromFile(_value); }
		virtual binIO& operator>>(long& _value) { return ReadFromFile(_value); }
		virtual binIO& operator>>(double& _value) { return ReadFromFile(_value); }
		virtual binIO& operator>>(unsigned int& _value) { return ReadFromFile(_value); }
		virtual binIO& operator>>(unsigned char& _value) { return ReadFromFile(_value); }
		virtual binIO& operator>>(unsigned short& _value) { return ReadFromFile(_value); }
		virtual binIO& operator>>(unsigned long& _value) { return ReadFromFile(_value); }
		
	// mem functions
		
		//write
    		binIO& operator<<(const void* _buf);
    		
    		//read
		binIO& operator>>(void* _buf);
		
		//write or read to/from file
		void operator,(unsigned int len);
	
	private:
	
		void* m_buffer;
		Flag m_readWrite;

		binIO(const binIO& _bin);
		binIO& operator=(const binIO& _bin);
		
		template<class T>
		binIO& WriteToFile(const T& _value);
		template<class T>
		binIO& ReadFromFile(T& _value);
		
		template<class T>
		void Write(T* _value, int _len);
		template<class T>
		void Read(T* _value, int _len);
};

// mem functions

binIO& binIO::operator<<(const void* _buf)
{
	if(_buf)
	{
		m_buffer = (void*)_buf;
		m_readWrite = WRITE;
	}
	
	return *this;
}

binIO& binIO::operator>>(void* _buf)
{
	if(_buf)
	{
		m_buffer = _buf;
		m_readWrite = READ;
	}
	
	return *this;
}

void binIO::operator,(unsigned int _len)
{
	if(WRITE == m_readWrite)
	{
		Write(m_buffer,_len);
	}
	
	else if(READ == m_readWrite)
	{
		Read(m_buffer,_len);
	}
	
	m_readWrite = NO_R_NO_W;
}

// private functions

template<class T>
binIO& binIO::WriteToFile(const T& _value)
{
	Write(&_value,sizeof(T));
	return *this;
}
		
template<class T>
binIO& binIO::ReadFromFile(T& _value)
{
	Read(&_value,sizeof(T));
	return *this;
}

template<class T>
void binIO::Write(T* _value, int _len)
{
	if(!this->GetFile())
	{
		SetStatus(writeErr_e);
		throw TException<status>(writeErr_e,__FILE__,__LINE__,"file is not open!");
	}
	
	if(GetFileMode() == "rb")
	{
		SetStatus(writeErr_e);
		throw TException<status>(writeErr_e,__FILE__,__LINE__,"wrong mode for write!");
	}
	
	fwrite(_value,_len,1,GetFile());
	SetStatus(ok_e);
}

template<class T>
void binIO::Read(T* _value, int _len)
{
	if(!this->GetFile())
	{
		SetStatus(readErr_e);
		throw TException<status>(readErr_e,__FILE__,__LINE__,"file is not open!");
	}
	
	if(GetFileMode() == "ab" || GetFileMode() == "wb")
	{
		SetStatus(readErr_e);
		throw TException<status>(readErr_e,__FILE__,__LINE__,"wrong mode for read!");
	}
	
	fread(_value,_len,1,GetFile());
	SetStatus(ok_e);
}




#endif
