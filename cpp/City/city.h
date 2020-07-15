#ifndef __CITY_H__
#define __CITY_H__

#include "street.h"
#include <vector>
using namespace std;

template <class cT, class sT, class bT>
class city
{
	public:
	
	//DTOR
	
		~city();
		
	//CTOR
	
		city();
		
		city(const cT& _id);
		
		city(city& _c);
		
	//operator
		
		city& operator=(const city& _c);
	
	//Mem functions
	
		// set new id to the city
		void SetCityID(const cT& _id);
		
		// get the city id
		const cT& GetCityID();
		
		// add new street to the city
		void AddStreet(const street<sT,bT>& _s);
		
		// get street from the city by id (throw exception const char* if not found)
		const street<sT,bT>& GetStreet(const sT& _idS);
	
	private:
		
		cT m_id;
		vector<street<sT,bT> > m_vector;
};

//DTOR

template <class cT, class sT, class bT>
city<cT,sT,bT>::~city() {}

//CTOR

template <class cT, class sT, class bT>
city<cT,sT,bT>::city() {}

template <class cT, class sT, class bT>
city<cT,sT,bT>::city(const cT& _id)
{
	m_id = _id;
}

template <class cT, class sT, class bT>
city<cT,sT,bT>::city(city& _c)
{
	m_id = _c.m_id;
	m_vector = _c.m_vector;
}

//operator

template <class cT, class sT, class bT>
city<cT,sT,bT>& city<cT,sT,bT>::operator=(const city& _c)
{
	m_id = _c.m_id;
	m_vector = _c.m_vector;
}

//Mem functions

template <class cT, class sT, class bT>
void city<cT,sT,bT>::SetCityID(const cT& _id)
{
	m_id = _id;
}

template <class cT, class sT, class bT>
const cT& city<cT,sT,bT>::GetCityID()
{
	return m_id;
}

template <class cT, class sT, class bT>
void city<cT,sT,bT>::AddStreet(const street<sT,bT>& _s)
{
	m_vector.insert(m_vector.end(),_s);
}

template <class cT, class sT, class bT>
const street<sT,bT>& city<cT,sT,bT>::GetStreet(const sT& _idS)
{
	int sNum = 0;
	
	while(sNum < m_vector.size() && _idS != m_vector[sNum].GetStreetID())
	{
		++sNum;
	}
	
	if(sNum == m_vector.size())
	{
		throw("street not found!");
	}
	
	return m_vector[sNum];
}



#endif
