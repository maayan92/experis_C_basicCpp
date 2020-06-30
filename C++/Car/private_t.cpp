#include <cstdio>
#include <cstring>
#include "private_t.h"

private_t::private_t():car_t()
{
	Initialze();
}
		
private_t::private_t(unsigned int _capacity, Gear _gearType):car_t(_capacity)
{
	Initialze();
	SetGearType(_gearType);
}
		
private_t::private_t(const private_t& _private):car_t(_private)
{
	m_speed = _private.m_speed;
}

// SUB FUNCTIONS

void private_t::Initialze()
{
	m_speed = 0;
	SetCarName("Private");
}
