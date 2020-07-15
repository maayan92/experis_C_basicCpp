#ifndef __PRIVATE_T_H__
#define __PRIVATE_T_H__

#include "car_t.h"

class private_t:public car_t
{
	public:
	
	// CTOR
	
		private_t();
		
		private_t(unsigned int _capacity, Gear _gearType);
		
		private_t(const private_t& _private);
		
	// DTOR
	
		~private_t() {}
		
	// Mem functions
	
		private_t& Accelerate() { m_speed += 10; }
		
		private_t& ReduceSpeed() { m_speed -= 10; }

		unsigned int GetSpeed()const { return m_speed; }
		
	private:
	
		unsigned int m_speed;
		
		void Initialze();
		
		private_t& operator=(const private_t& _private);
};

#endif
