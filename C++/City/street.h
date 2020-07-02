#ifndef __STREET_H__
#define __STREET_H__

#include "building.h"
#include <vector>
using namespace std;

template <class sT, class bT>
class street
{
	public:
	
	//DTOR
	
		~street();
		
	//CTOR
	
		street();
		
		street(const sT& _id);
		
		street(const street& _s);
		
	//operator
		
		street& operator=(const street& _s);
	
	//Mem functions
	
		// set new id to the street
		void SetStreetID(const sT& _id);
		
		// get the street id
		const sT& GetStreetID();
		
		// add new building to the street
		void AddBuilding2Street(const building<bT>& _b);
		
		// get building from the street by id (throw exception const char* if not found)
		const building<bT>& GetBuilding(const bT& _idB);
	
	private:
		
		sT m_id;
		vector<building<bT> > m_vector;
};

//DTOR

template <class sT, class bT>
street<sT,bT>::~street() {}

//CTOR

template <class sT, class bT>
street<sT,bT>::street() {}

template <class sT, class bT>
street<sT,bT>::street(const sT& _id)
{
	m_id = _id;
}

template <class sT, class bT>
street<sT,bT>::street(const street& _s)
{
	m_id = _s.m_id;
	m_vector = _s.m_vector;
}

//operator

template <class sT, class bT>
street<sT,bT>& street<sT,bT>::operator=(const street& _s)
{
	m_id = _s.m_id;
	m_vector = _s.m_vector;
}

//Mem functions

template <class sT, class bT>
void street<sT,bT>::SetStreetID(const sT& _id)
{
	m_id = _id;
}

template <class sT, class bT>
const sT& street<sT,bT>::GetStreetID()
{
	return m_id;
}

template <class sT, class bT>
void street<sT,bT>::AddBuilding2Street(const building<bT>& _b)
{
	m_vector.insert(m_vector.end(),_b);
}

template <class sT, class bT>
const building<bT>& street<sT,bT>::GetBuilding(const bT& _idB)
{
	int bNum = 0;
	
	while(bNum < m_vector.size() && _idB != m_vector[bNum].GetBuildingID())
	{
		++bNum;
	}
	
	if(bNum == m_vector.size())
	{
		throw("building not found!");
	}
	
	return m_vector[bNum];
}



#endif
