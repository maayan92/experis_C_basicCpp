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
	
		~tContainer() {}
	
	// CTOR
	
		tContainer() {}
		
	// mem functions
		
		bool IsEmpty()const { return m_container.empty(); }
		
		size_t NumOfElements()const { return m_container.size(); }
		
		void InsertNemElement(const T* _element);
		
		const T* GetFirstElement()const { return (m_container.begin() == m_container.end()) ? 0 : *m_container.begin(); }
		
		const T* GetLastElement()const { return (m_container.rbegin() == m_container.rend()) ? 0 : *m_container.rbegin(); }
		
		const T* Find(const T& _value);
		
		T* RemoveByValue(const T& _value);
		
		void RemoveAll();
		
		bool RemoveAndDeleteByValue(const T& _value);
		
		void RemoveAndDeleteAll();
		
		const T* operator[](size_t _position);
	
	private:
		
		container m_container;
		typedef typename container::iterator iter;
		
		tContainer(const tContainer& _cont);
		tContainer& operator=(const tContainer& _cont);
		
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
const T* tContainer<T,container>::Find(const T& _value)
{
	iter m_iter = find_if(m_container.begin(), m_container.end(), Equal<T>(_value));
	
	return (m_iter == m_container.end()) ? 0 : *m_iter;
}

template<typename T, typename container>
T* tContainer<T,container>::RemoveByValue(const T& _value)
{
	iter m_iter = find_if(m_container.begin(), m_container.end(), Equal<T>(_value));
	
	if(m_iter != m_container.end())
	{
		T* element = *m_iter;
		m_container.erase(m_iter);
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
	iter m_iter = find_if(m_container.begin(), m_container.end(), Equal<T>(_value));
	
	if(m_iter != m_container.end())
	{
		T* element = *m_iter;
		m_container.erase(m_iter);
		delete element;
		
		return true;
	}
	
	return false;
}

template<typename T, typename container>
void tContainer<T,container>::RemoveAndDeleteAll()
{
	iter m_iter = m_container.begin();
	T* element;
	
	while(m_iter != m_container.end())
	{
		element = *m_iter;
		m_container.erase(m_iter);
		delete element;
		
		m_iter = m_container.begin();
	}
}

template<typename T, typename container>
const T* tContainer<T,container>::operator[](size_t _position)
{

	if(_position >= m_container.size())
	{
		return 0;
	}
	
	iter m_iter = m_container.begin();
	advance(m_iter, _position);
	
	return *m_iter;
}





#endif
