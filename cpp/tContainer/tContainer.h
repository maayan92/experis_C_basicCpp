#ifndef __T_CONTAINER__
#define __T_CONTAINER__

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <typeinfo>
using namespace std;

template<typename T>
class Equal
{
	public:
	
		~Equal() {}
		
		Equal(const T& _val):m_val(_val) {}
		
		bool operator()(const T* _element)const { return *_element == m_val; }

	private:
	
		T m_val;

};


template<typename T, typename container>
class tContainer
{
	public:
	
	// DTOR
	
		~tContainer() { m_container.clear(); }
	
	// CTOR
	
		tContainer() {}
		
	// mem functions
		
		bool IsEmpty()const { return m_container.empty(); }
		
		size_t NumOfElements()const { return m_container.size(); }
		
		void InsertNemElement(const T* _element);
		
		const T* GetFirstElement()const { return (m_container.begin() == m_container.end()) ? 0 : *m_container.begin(); }
		
		const T* GetLastElement()const { return (m_container.rbegin() == m_container.rend()) ? 0 : *m_container.rbegin(); }
		
		const T* Find(const T& _value)const;
		
		T* RemoveByValue(const T& _value);
		
		void RemoveAll();
		
		bool RemoveAndDeleteByValue(const T& _value);
		
		void RemoveAndDeleteAll();
		
		const T* operator[](size_t _position);
	
	private:
		
		container m_container;
		typedef typename container::iterator iter;
		typedef typename container::const_iterator c_iter;
		
		tContainer(const tContainer& _cont);
		tContainer& operator=(const tContainer& _cont);
		
		const T* GetElementByPosition(size_t _position);
};

// mem functions

template<typename T, typename container>
void tContainer<T,container>::InsertNemElement(const T* _element)//throw exception
{
	if(_element)
	{
		m_container.push_back((T*)_element);
	}
}

template<typename T, typename container>
const T* tContainer<T,container>::Find(const T& _value)const
{
	c_iter itr = find_if(m_container.begin(), m_container.end(), Equal<T>(_value));
	
	return (itr == m_container.end()) ? 0 : *itr;
}

template<typename T, typename container>
T* tContainer<T,container>::RemoveByValue(const T& _value)
{
	iter itr = find_if(m_container.begin(), m_container.end(), Equal<T>(_value));
	
	if(itr != m_container.end())
	{
		T* element = *itr;
		m_container.erase(itr);
		return element;
	}
	
	return 0;
}

template<typename T, typename container>
void tContainer<T,container>::RemoveAll()
{
	m_container.clear();
}

template<typename T, typename container>
bool tContainer<T,container>::RemoveAndDeleteByValue(const T& _value)
{
	iter itr = find_if(m_container.begin(), m_container.end(), Equal<T>(_value));
	
	if(itr != m_container.end())
	{
		T* element = *itr;
		m_container.erase(itr);
		delete element;
		
		return true;
	}
	
	return false;
}

template<typename T, typename container>
void tContainer<T,container>::RemoveAndDeleteAll()
{
	iter itr = m_container.begin();
	T* element;
	
	while(itr != m_container.end())
	{
		element = *itr;
		m_container.erase(itr);
		delete element;
		
		itr = m_container.begin();
	}
}

template<typename T, typename container>
const T* tContainer<T,container>::operator[](size_t _position)
{

	if(_position >= m_container.size() || _position < 0)
	{
		return 0;
	}

	if(typeid(m_container) == typeid(vector<T*>))
	{
		return (*(vector<T*>*)&m_container)[_position];
	}
	
	return GetElementByPosition(_position);
}

template<typename T, typename container>
const T* tContainer<T,container>::GetElementByPosition(size_t _position)
{
	size_t i = 0;
	iter itr = m_container.begin();
	
	while(i < _position)
	{
		itr++;
		++i;
	}
	
	return *itr;
}




#endif
