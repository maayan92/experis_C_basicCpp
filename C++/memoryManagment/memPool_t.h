#ifndef __MEM_POOL_T__
#define __MEM_POOL_T__

#include "memManager_t.h"
#include "memPage_t.h"
#include <vector>
using namespace std;

class memPool_t:public memManager_t
{
	public:
		//Inherited from memManager_t:
		
		//bool IsMemoryEmpty()const;
		
		//unsigned int GetActualSize()const;
		
		//unsigned int GetCurrentPosition()const;

		//bool SetCurrentPosition(unsigned int _position);
		
	// DTOR
	
		virtual ~memPool_t();
		
	// CTOR
	
		memPool_t();
		
	// Mem functions
		
		void SetdNumOfPages(unsigned int _dNumOfPages) { dNumOfPages = _dNumOfPages; }
		
		virtual unsigned int ReadData(void* _readBuffer, unsigned int _size);
		
		virtual unsigned int ReadData(void* _readBuffer, unsigned int _size, unsigned int _position);
		
		virtual unsigned int WriteData(const void* _writeBuffer, unsigned int _size);
		
		virtual unsigned int WriteData(const void* _writeBuffer, unsigned int _size, unsigned int _position);
	
	private:
		
		vector<memPage_t*> m_vector;
		
		static unsigned int dNumOfPages;
		
		memPool_t(const memPool_t& _pool);
		
		memPool_t& operator=(const memPool_t& _pool);
		
		bool CreateNewPage();

		size_t FindPage(unsigned int *_position);
		
		unsigned int ReadDataFromPool(void* _readBuffer, unsigned int _size, unsigned int _position);
		
		unsigned int WriteDataToPool(const void* _writeBuffer, unsigned int _size, unsigned int _position);
		
		unsigned int WriteByPages(const void* _writeBuffer, unsigned int _size, unsigned int _position, size_t _pageNum);
};

#endif
