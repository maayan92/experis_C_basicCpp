#ifndef __BUILDING_H__
#define __BUILDING_H__

template <class T>
class building
{
	public:
	
	//DTOR
	
		~building();
		
	//CTOR
	
		building();
	
		building(const T& _id);
		
		building(const building& _b);
		
	//operator
		
		building& operator=(const building& _b);
		
	//Mem functions
	
		// set new id to the building 
		void SetBuidingID(const T& _id);
		
		// get the building id
		const T& GetBuildingID()const;

	private:
	
		T m_id;
};

//DTOR

template <class T>
building<T>::~building() {}

//CTOR

template <class T>
building<T>::building() {}

template <class T>
building<T>::building(const T& _id)
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
void building<T>::SetBuidingID(const T& _id)
{
	m_id = _id;
}

template <class T>
const T& building<T>::GetBuildingID()const
{
	return m_id;
}



#endif
