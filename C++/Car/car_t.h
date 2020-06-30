#ifndef __CAR_T_H__
#define __CAR_T_H__

#include "String_t.h"

class car_t
{
	public:
		
	// CTOR
		
		car_t();
			
		car_t(unsigned int _capacity);
			
		car_t(const car_t& _car);
		
		enum Gear
		{
			STANDARD,
			AUTOMATIC
		};
		
	// Mem functions
		
		const char* GetCarName();
	
		Gear GetGearType()const { return m_gearType; }
		
		bool operator<(const car_t& _car)const { return (m_capacity < _car.m_capacity); }
		
		bool Compare(const car_t& _car)const { return (m_name == _car.m_name); }

	protected:
		
	// DTOR
		
		~car_t() {}
			
		void SetCarName(const char* _strName);
		
		void SetGearType(Gear _gearType) { m_gearType = _gearType; }

	private:
		
		String_t m_name;
		unsigned int m_capacity;
		Gear m_gearType;
		const unsigned int m_uniqueId;
		
		static unsigned int m_Did;
		static unsigned int m_Dcapacity;
		
		void initialize(unsigned int _capacity, Gear _gearType);
		
		car_t& operator=(const car_t& _car);
};


#endif
