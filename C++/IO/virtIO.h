#ifndef __VIRT_IO__
#define __VIRT_IO__

#include "String_t.h"
#include <stdio.h>
#include "TException.h"

class virtIO
{
	public:
	
		virtual ~virtIO() = 0;
	
		virtIO();
		
		enum status
		{
			ok_e,
			cant_open_file_e,
			bad_access_e,
			writeErr_e,
                   	readErr_e
		};
		
		// write to file
		
		virtual virtIO& operator<<(int _value) = 0;
		virtual virtIO& operator<<(float _value) = 0;
		virtual virtIO& operator<<(char _value) = 0;
		virtual virtIO& operator<<(short _value) = 0;
		virtual virtIO& operator<<(long _value) = 0;
		virtual virtIO& operator<<(double _value) = 0;
		virtual virtIO& operator<<(unsigned int _value) = 0;
		virtual virtIO& operator<<(unsigned char _value) = 0;
		virtual virtIO& operator<<(unsigned short _value) = 0;
		virtual virtIO& operator<<(unsigned long _value) = 0;
		
		// read from file
		
		virtual virtIO& operator>>(int& _value) = 0;
		virtual virtIO& operator>>(float& _value) = 0;
		virtual virtIO& operator>>(char& _value) = 0;
		virtual virtIO& operator>>(short& _value) = 0;
		virtual virtIO& operator>>(long& _value) = 0;
		virtual virtIO& operator>>(double& _value) = 0;
		virtual virtIO& operator>>(unsigned int& _value) = 0;
		virtual virtIO& operator>>(unsigned char& _value) = 0;
		virtual virtIO& operator>>(unsigned short& _value) = 0;
		virtual virtIO& operator>>(unsigned long& _value) = 0;

		void CloseFile() { if(m_file){ fclose(m_file); m_file = NULL; } }
	
		bool Open(const String_t& _name, const String_t& _mode);
		
		const String_t& GetFileName()const { return m_name; }
		
		const String_t& GetFileMode()const { return m_mode; }
		
		long int GetFileLength()const;
		
		long int GetPosition()const { return (!m_file) ? 0 : ftell(m_file); }
		
		bool SetPosition(long int _position);
		
		status GetStatus()const { return m_status; }
		
		bool SetStatus(status _status);
	
	protected:
	
		FILE* GetFile()const { return m_file; }
	
		void SetFileName(String_t _name) { m_name = _name; }
	
	private:
		FILE *m_file;
		String_t m_name;
		String_t m_mode;
		status m_status;

		virtIO(const virtIO& _virt);
		virtIO& operator=(const virtIO& _virt);
};




#endif
