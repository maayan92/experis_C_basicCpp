#ifndef __BUS_T_H__
#define __BUS_T_H__

#include "car_t.h"

class bus_t:public car_t
{
	public:
	
	// CTOR
	
		bus_t();
		
		bus_t(int _lineNumber, unsigned int _numOfSeats, unsigned int _capacity, Gear _gearType);
		
		bus_t(const bus_t& _bus);
		
	// DTOR
	
		~bus_t() {}
		
	// Mem functions
		
		int GetLineNum()const { return m_lineNumber; }
		
		bus_t& SetLineNum(int _lineNumber) { m_lineNumber = _lineNumber; return *this; }
		
		unsigned int GetNumOfSeats()const { return m_numOfSeats; }
		
	private:
	
		int m_lineNumber;
		unsigned int m_numOfSeats;
		
		static unsigned int m_DnumOfSeats;
		
		void Initialize(int _lineNumber, unsigned int _numOfSeats);
		
		bus_t& operator=(const bus_t& _bus);
};


#endif
