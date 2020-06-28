#ifndef __BUS_T_H__
#define __BUS_T_H__

#include "car_t.h"

class bus_t:public car_t
{
	public:
	
	// CTOR
	
		bus_t():car_t(){ m_lineNumber = 0; m_numOfSeats = m_DnumOfSeats; SetCarName("Bus"); }
		
		inline bus_t(int _lineNumber, unsigned int _numOfSeats, unsigned int _capacity, Gear _gearType);
		
		bus_t(bus_t& _bus):car_t(_bus) {}
		
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
};

	inline bus_t::bus_t(int _lineNumber, unsigned int _numOfSeats, unsigned int _capacity, Gear _gearType)
	:car_t(_capacity){
	
		m_lineNumber = _lineNumber;
		m_numOfSeats = _numOfSeats;
		SetCarName("Bus");
		SetGearType(_gearType);
	}

#endif
