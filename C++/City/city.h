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
		
		city(cT _id);
		
		city(city& _c);
		
	//operator
		
		city<cT,sT,bT>& operator=(const city& _c);
	
	//Mem functions
	
		void SetCityID(cT _id);
		
		cT GetCityID();
		
		void AddStreet(street<sT,bT> _s);
		
		street<sT,bT>& GetStreet(sT _idS);
	
	private:
		
		cT m_id;
	
		vector<street<sT,bT> > m_vector;

};

//DTOR

template <class cT, class sT, class bT>
city<cT,sT,bT>::~city() {}

//CTOR

template <class cT, class sT, class bT>
city<cT,sT,bT>::city(cT _id)
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
void city<cT,sT,bT>::SetCityID(cT _id)
{
	m_id = _id;
}

template <class cT, class sT, class bT>
cT city<cT,sT,bT>::GetCityID()
{
	return m_id;
}

template <class cT, class sT, class bT>
void city<cT,sT,bT>::AddStreet(street<sT,bT> _s)
{
	m_vector.insert(m_vector.end(),_s);
}

template <class cT, class sT, class bT>
street<sT,bT>& city<cT,sT,bT>::GetStreet(sT _idS)
{
	int sNum = 0;
	
	while(sNum < m_vector.size() && _idS != m_vector[sNum].GetStreetID())
	{
		++sNum;
	}
	
	return (sNum == m_vector.size()) ? m_vector[sNum - 1] : m_vector[sNum];
}



#endif
