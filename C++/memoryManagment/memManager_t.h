#ifndef __MEM_MANAGER_T__
#define __MEM_MANAGER_T__

class memManager_t
{
	public:

	// CTOR
	
		memManager_t() { m_actualSize = m_position = 0; }
		
	// Mem functions
		
		bool IsMemoryEmpty()const { return (0 == m_actualSize); }
		
		unsigned int GetActualSize()const { return m_actualSize; }
		
		unsigned int GetCurrentPosition()const { return m_position; }

		bool SetCurrentPosition(unsigned int _position);

		virtual unsigned int ReadData(void* _readBuffer, unsigned int _size) = 0;
		
		virtual unsigned int ReadData(void* _readBuffer, unsigned int _size, unsigned int _position) = 0;
		
		virtual unsigned int WriteData(const void* _writeBuffer, unsigned int _size) = 0;
		
		virtual unsigned int WriteData(const void* _writeBuffer, unsigned int _size, unsigned int _position) = 0;
	
	protected:
	
	// DTOR	
		virtual ~memManager_t() = 0;
		
		void SetNewActualSize(unsigned int _actualSize) { m_actualSize = _actualSize; }
	
	private:
	
		unsigned int m_actualSize;
		unsigned int m_position;
		
		memManager_t(const memManager_t& _manager);
		
		memManager_t& operator=(const memManager_t& _page);
};

#endif
