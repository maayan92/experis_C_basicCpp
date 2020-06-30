#include <cstdio>
#include <cstring>
#include "car_t.h"

unsigned int car_t::m_Did = 1;
unsigned int car_t::m_Dcapacity = 1500;

car_t::car_t():m_uniqueId(m_Did)
{
	initialize(m_Dcapacity,STANDARD);
}

car_t::car_t(unsigned int _capacity):m_uniqueId(m_Did)
{
	initialize(_capacity,STANDARD);
}
		
car_t::car_t(const car_t& _car):m_uniqueId(m_Did), m_name(_car.m_name)
{
	initialize(_car.m_capacity,_car.m_gearType);
}

const char* car_t::GetCarName()
{
	return m_name.GetString();
} 

void car_t::SetCarName(const char* _strName)
{
	m_name.SetString(_strName);
}

// SUB FUNCTIONS

void car_t::initialize(unsigned int _capacity, Gear _gearType)
{ 
	++m_Did;
	m_capacity = _capacity;
	SetGearType(_gearType);
}


