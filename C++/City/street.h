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
		
		street(sT _id);
		
		street(const street& _s);
		
	//operator
		
		street<sT,bT>& operator=(const street& _s);
	
	//Mem functions
	
		void SetStreetID(sT _id);
		
		sT GetStreetID();
		
		void AddBuilding2Street(building<bT> _b);
		
		building<bT>& GetBuilding(bT _idB);
	
	private:
		
		sT m_id;
	
		vector<building<bT> > m_vector;

};

//DTOR

template <class sT, class bT>
street<sT,bT>::~street() {}

//CTOR

template <class sT, class bT>
street<sT,bT>::street(sT _id)
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
void street<sT,bT>::SetStreetID(sT _id)
{
	m_id = _id;
}

template <class sT, class bT>
sT street<sT,bT>::GetStreetID()
{
	return m_id;
}

template <class sT, class bT>
void street<sT,bT>::AddBuilding2Street(building<bT> _b)
{
	m_vector.insert(m_vector.end(),_b);
}

template <class sT, class bT>
building<bT>& street<sT,bT>::GetBuilding(bT _idB)
{
	int bNum = 0;
	
	while(bNum < m_vector.size() && _idB != m_vector[bNum].getBuildingID())
	{
		++bNum;
	}
	
	return (bNum == m_vector.size()) ? m_vector[bNum - 1] : m_vector[bNum];
}



#endif
