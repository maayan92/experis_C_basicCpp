#ifndef __CAR_T_H__
#define __CAR_T_H__

#include "String_t.h"

typedef enum
{
	STANDARD,
	AUTOMATIC
}Gear;

class car_t
{
	public:
		
	// CTOR
		
		car_t() : m_uniqueId(m_Did){ initialize(m_Dcapacity,STANDARD); }
			
		car_t(unsigned int _capacity) : m_uniqueId(m_Did){ initialize(_capacity,STANDARD); }
			
		car_t(car_t& _car) : m_uniqueId(m_Did), m_name(_car.m_name){ initialize(_car.m_capacity,_car.m_gearType); }
		
	// Mem functions
		
		const char* GetCarName()const { return m_name.GetString(); }
	
		Gear GetGearType()const { return m_gearType; }
		
		car_t& operator=(car_t& _car) { m_capacity = _car.m_capacity; m_gearType = _car.m_gearType; return *this; }
		
		bool operator<(car_t& _car)const { return (m_capacity < _car.m_capacity) ? true : false; }
		
		bool Compare(car_t& _car)const { return (m_name == _car.m_name); }

	protected:
		
	// DTOR
		
		~car_t() {}
			
		void SetCarName(const char* _strName) { m_name.SetString(_strName); }
		
		void SetGearType(Gear _gearType) { m_gearType = _gearType; }

	private:
		
		String_t m_name;
		unsigned int m_capacity;
		Gear m_gearType;
		const unsigned int m_uniqueId;
		
		static unsigned int m_Did;
		static unsigned int m_Dcapacity;
		
		void initialize(unsigned int _capacity, Gear _gearType) { ++m_Did; m_capacity = _capacity; SetGearType(_gearType); }

};


#endif
