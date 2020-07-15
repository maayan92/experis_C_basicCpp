#include <cstdio>
#include <cstring>
#include "bus_t.h"

unsigned int bus_t::m_DnumOfSeats = 64;

bus_t::bus_t()
{
	Initialize(0,m_DnumOfSeats);
}

bus_t::bus_t(int _lineNumber, unsigned int _numOfSeats, unsigned int _capacity, Gear _gearType):car_t(_capacity)
{
	Initialize(_lineNumber,_numOfSeats);
	SetGearType(_gearType);
}

bus_t::bus_t(const bus_t& _bus):car_t(_bus)
{
	m_numOfSeats = _bus.m_numOfSeats;
}

void bus_t::Initialize(int _lineNumber, unsigned int _numOfSeats)
{
	m_lineNumber = _lineNumber;
	m_numOfSeats = _numOfSeats;
	SetCarName("Bus");
}
