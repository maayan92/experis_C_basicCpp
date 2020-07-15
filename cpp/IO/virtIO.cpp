#include "virtIO.h"

// DTOR

virtIO::~virtIO()
{
	CloseFile();
}

// mem functions

bool virtIO::Open(const String_t& _name, const String_t& _mode)
{
	if(m_file)
	{
		m_status = bad_access_e;
		return false;
	}
	
	m_name = _name;
	m_mode = _mode;
	
	m_file = fopen(m_name.GetString(),m_mode.GetString());
	if(!m_file)
	{
		m_status = cant_open_file_e;
		return false;
	}
	
	m_status = ok_e;
	return true;
}

long int virtIO::GetFileLength()const
{
	long int size = 0;
	
	if(m_file)
	{
		long curPos = ftell(m_file);
		fseek(m_file,0,SEEK_END);
		size = ftell(m_file);
		fseek(m_file,curPos,SEEK_SET);
	}
	
	return size;
}

bool virtIO::SetPosition(long int _position)
{
	if(0 > _position || _position > GetFileLength())
	{
		return false;
	}
	
	return (!m_file) ? false : !fseek(m_file,_position,SEEK_SET);
}

bool virtIO::SetStatus(status _status)
{
	return (_status > readErr_e || _status < ok_e) ? false : m_status = _status, true;
}








