#include <cstdio>
#include <cstring>
#include "memPool_t.h"

// DTOR

memPool_t::~memPool_t()
{
	int i;
	
	for(i = 0;i < m_vector.size();++i)
	{
		delete m_vector[i];
	}
}

// CTOR

memPool_t::memPool_t()
{
	CreateNewPage();
}

// Mem functions

unsigned int memPool_t::ReadData(void* _readBuffer, unsigned int _size)
{
	return ReadDataFromPool(_readBuffer,_size,GetCurrentPosition());
}
		
unsigned int memPool_t::ReadData(void* _readBuffer, unsigned int _size, unsigned int _position)
{
	return (_position > GetActualSize()) ? 0 : ReadDataFromPool(_readBuffer,_size,_position);
}

unsigned int memPool_t::WriteData(const void* _writeBuffer, unsigned int _size)
{
	return WriteDataToPool(_writeBuffer,_size,GetCurrentPosition());
}
		
unsigned int memPool_t::WriteData(const void* _writeBuffer, unsigned int _size, unsigned int _position)
{
	return (_position > GetActualSize()) ? 0 : WriteDataToPool(_writeBuffer,_size,_position);
}

// Private functions

unsigned int memPool_t::ReadDataFromPool(void* _readBuffer, unsigned int _size, unsigned int _position)
{
	unsigned int currentPos = _position;
	size_t page = FindPage(&_position);
	
	unsigned int BytesRead = m_vector[page++]->ReadData(_readBuffer,_size,_position);
	
	while(BytesRead < _size && page < m_vector.size())
	{
		BytesRead += m_vector[page++]->ReadData(((char*)_readBuffer) + BytesRead,_size - BytesRead,0);
	}
	
	SetCurrentPosition(BytesRead + currentPos);
	
	return BytesRead;
}

unsigned int memPool_t::WriteDataToPool(const void* _writeBuffer, unsigned int _size, unsigned int _position)
{
	unsigned int currentPos = _position;
	size_t page = FindPage(&_position);
	
	unsigned int BytesWritten = WriteByPages(_writeBuffer,_size,_position,page);
	
	if((BytesWritten + _position) > GetActualSize())
	{
		SetNewActualSize(BytesWritten + _position);
	}
	
	SetCurrentPosition(BytesWritten + currentPos);
	
	return BytesWritten;
}

unsigned int memPool_t::WriteByPages(const void* _writeBuffer, unsigned int _size, unsigned int _position, size_t _pageNum)
{
	unsigned int BytesWritten = m_vector[_pageNum]->WriteData(_writeBuffer,_size,_position);
	
	while(BytesWritten < _size)
	{
		if((++_pageNum) == m_vector.size() && !CreateNewPage()) { return BytesWritten; }
		
		BytesWritten += m_vector[_pageNum]->WriteData(((char*)_writeBuffer) + BytesWritten,_size - BytesWritten,0);
	}
	
	return BytesWritten;
}

size_t memPool_t::FindPage(unsigned int *_position)
{
	unsigned int capacity = 0;
	size_t pageNum = 0;
	
	capacity = m_vector[pageNum]->GetCapacity();
	
	while(capacity < *_position && pageNum < m_vector.size())
	{
		*_position -= capacity;
		
		capacity = m_vector[pageNum++]->GetCapacity();
	}
	
	return pageNum;
}

bool memPool_t::CreateNewPage()
{
	memPage_t *page = new memPage_t;
	
	if(!page)
	{
		return false;
	}
	
	m_vector.insert(m_vector.end(),page);
	return true;
}






