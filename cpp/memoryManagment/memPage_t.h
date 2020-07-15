#ifndef __MEM_PAGE_T__
#define __MEM_PAGE_T__

#include "memManager_t.h"

class memPage_t:public memManager_t
{
	public:
		//Inherited from memManager_t:
		
		//bool IsMemoryEmpty()const;
		
		//unsigned int GetActualSize()const;
		
		//unsigned int GetCurrentPosition()const;

		//bool SetCurrentPosition(unsigned int _position);
		
	// DTOR
	
		virtual ~memPage_t() { delete[] m_buffer; }
		
	// CTOR
	
		memPage_t() { m_capacity = dCapacity; m_buffer = new char[m_capacity]; }
		
		memPage_t(unsigned int _capacity) { m_capacity = _capacity; m_buffer = new char[m_capacity]; }
		
	// Mem functions
		
		unsigned int GetCapacity() { return m_capacity; }
		
		unsigned int GetDefaultCapacity() { return dCapacity; }
		
		unsigned int SetDefaultCapacity(unsigned int _capacity) { dCapacity = _capacity; }
		
		virtual unsigned int ReadData(void* _readBuffer, unsigned int _size);
		
		virtual unsigned int ReadData(void* _readBuffer, unsigned int _size, unsigned int _position);
		
		virtual unsigned int WriteData(const void* _writeBuffer, unsigned int _size);
		
		virtual unsigned int WriteData(const void* _writeBuffer, unsigned int _size, unsigned int _position);
		
	private:

		char* m_buffer;
		unsigned int m_capacity;
		
		static unsigned int dCapacity;

		memPage_t(const memPage_t& _page);
		
		memPage_t& operator=(const memPage_t& _page);
		
		unsigned int ReadDataFromPage(void* _readBuffer, unsigned int _size, unsigned int _position);
		
		unsigned int WriteDataToPage(const void* _writeBuffer, unsigned int _size, unsigned int _position);
};

#endif
