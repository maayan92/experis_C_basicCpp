#ifndef __BUILDING_H__
#define __BUILDING_H__

template <class T>
class building
{
	public:
	
	//DTOR
	
		~building();
		
	//CTOR
	
		building(T _id);
		
		building(const building& _b);
		
	//operator
		
		building<T>& operator=(const building& _b);
		
	//Mem functions
	
		void setBuidingID(T _id);
		
		T getBuildingID()const;

	private:
	
		T m_id;
		
};

//DTOR

template <class T>
building<T>::~building() {}

//CTOR

template <class T>
building<T>::building(T _id)
{
	m_id = _id;
}

template <class T>
building<T>::building(const building& _b)
{
	m_id = _b.m_id;
}

//operator

template <class T>
building<T>& building<T>::operator=(const building& _b)
{
	m_id = _b.m_id;
}

//Mem functions

template <class T>
void building<T>::setBuidingID(T _id)
{
	m_id = _id;
}

template <class T>
T building<T>::getBuildingID()const
{
	return m_id;
}



#endif
