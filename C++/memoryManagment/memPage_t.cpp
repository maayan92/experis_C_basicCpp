#include <cstdio>
#include <cstring>
#include "memPage_t.h"

unsigned int memPage_t::dCapacity = 6;

// Mem functions

unsigned int memPage_t::ReadData(void* _readBuffer, unsigned int _size)
{
	return ReadDataFromPage(_readBuffer,_size,GetCurrentPosition());
}
		
unsigned int memPage_t::ReadData(void* _readBuffer, unsigned int _size, unsigned int _position)
{
	return (_position > GetActualSize()) ? 0 : ReadDataFromPage(_readBuffer,_size,_position);
}

unsigned int memPage_t::WriteData(const void* _writeBuffer, unsigned int _size)
{
	return WriteDataToPage(_writeBuffer,_size,GetCurrentPosition());
}
		
unsigned int memPage_t::WriteData(const void* _writeBuffer, unsigned int _size, unsigned int _position)
{
	return (_position > GetActualSize()) ? 0 : WriteDataToPage(_writeBuffer,_size,_position);
}

// Private functions

unsigned int memPage_t::ReadDataFromPage(void* _readBuffer, unsigned int _size, unsigned int _position)
{
	unsigned int bytesToRead = GetActualSize() - _position;
	
	bytesToRead = (bytesToRead < _size) ? bytesToRead : _size;
	
	memcpy(_readBuffer,m_buffer + _position,bytesToRead);
	
	SetCurrentPosition(bytesToRead + _position);
	
	return bytesToRead;
}

unsigned int memPage_t::WriteDataToPage(const void* _writeBuffer, unsigned int _size, unsigned int _position)
{
	unsigned int bytesToWrite = m_capacity - _position;
	
	bytesToWrite = (bytesToWrite < _size) ? bytesToWrite : _size;
	
	memcpy(m_buffer + _position,_writeBuffer,bytesToWrite);
	
	if((bytesToWrite + _position) > GetActualSize())
	{
		SetNewActualSize(bytesToWrite + _position);
	}
	
	SetCurrentPosition(bytesToWrite + _position);
	
	return bytesToWrite;
}





	
