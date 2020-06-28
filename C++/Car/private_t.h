#ifndef __PRIVATE_T_H__
#define __PRIVATE_T_H__

#include "car_t.h"

class private_t:public car_t
{
	public:
	
	// CTOR
	
		private_t():car_t(){ Initialze(); }
		
		private_t(unsigned int _capacity, Gear _gearType):car_t(_capacity){ Initialze(); SetGearType(_gearType); }
		
		private_t(private_t& _private):car_t(_private){ m_speed = _private.m_speed; }
		
	// DTOR
	
		~private_t() {}
		
	// Mem functions
	
		private_t& Accelerate() { m_speed += 10; }
		
		private_t& ReduceSpeed() { m_speed -= 10; }

		unsigned int GetSpeed() { return m_speed; }
		
	private:
	
		unsigned int m_speed;
		
		void Initialze(){ m_speed = 0; SetCarName("Private"); }
};

#endif
