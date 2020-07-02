#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <string.h>
#include "container.h"

template<class T>
class array:public container<T>
{
	public:
	
	//inherits from container<T>:
	
		//int Count()const;
		//bool IsEmpty()const;
		//unsigned int GetNumOfElement()const;
	
	// DTOR
	
		~array() { delete[] m_array; this->SetNumOfElements(0); }
	
	// CTOR
	
		array(){ m_array = new T*[dCapacity]; m_capacity = dCapacity; m_reSize = dReSize; }
		
		array(unsigned int _capacity, unsigned int _reSize) { m_array = new T*[_capacity]; m_capacity = _capacity; m_reSize = _reSize; }

		array(const array& _arr);
		
	// operator
		
		array& operator=(const array& _arr);
		
	// mem functions
		
		//insert the _element in one position right of the _index, throw const char* on error.
		virtual bool Append(const T* _element, unsigned int _index);
		
		//insert the _element in one position left of the _index, throw const char* on error.
		virtual bool Prepend(const T* _element, unsigned int _index);
		
		//check if the array contains the _element.
		virtual bool Contains(const T* _element)const;
		
		//find the element with _value.
		virtual const T* Find(const T& _value)const;
		
		//return the index of the _element position in the array, -1 if the _element is not in the array.
		virtual int Index(const T* _element)const;
		
		//insert the _element in the last position, throw const char* on error.
		virtual bool Insert(const T* _element);
		
		/*
		virtual bool Remove(const T& _value); //
		
		virtual bool RemoveAll(); //
		
		virtual bool RemoveAndDelete(); //
		
		virtual bool RemoveAndDeleteAll(); //
		*/
	
	
	private:

		T** m_array;
		unsigned int m_capacity;
		unsigned int m_reSize;
		
		static unsigned int dCapacity;
		static unsigned int dReSize;
		
		// copies all data-memeber from _arr to the object. 
		void CopyAllMembers(const array& _arr);
		
		// resize the array.
		bool Resize();
		
		// move elements in [_index,numOfElements] range one step to the right.
		void ShiftRight(unsigned int _index);
		
		// search element in the array, return _element index or -1.
		int SearchElement(const T* _element)const;
};

template<class T>
unsigned int array<T>::dCapacity = 10;
template<class T>
unsigned int array<T>::dReSize = 5;

// CTOR

template<class T>
array<T>::array(const array& _arr)
{
	CopyAllMembers(_arr);
}

// operator

template<class T>
array<T>& array<T>::operator=(const array& _arr)
{
	delete[] m_array;
	
	CopyAllMembers(_arr);
}

// mem function

template<class T>
bool array<T>::Append(const T* _element, unsigned int _index)
{
	if(_index >= this->GetNumOfElement() || _index < 0)
	{
		throw("invalid index!");
		return false;
	}
	
	if(!_element)
	{
		throw("invalid element!");
		return false;
	}
	
	if(m_capacity == this->GetNumOfElement() && !Resize())
	{
		throw("realloc failed!");
		return false;
	}
	
	ShiftRight(_index+1);
	m_array[_index+1] = (T*)_element;
	
	this->SetNumOfElements(this->GetNumOfElement() + 1);
			
	return true;
}

template<class T>
bool array<T>::Prepend(const T* _element, unsigned int _index)
{
	if((_index-1) > this->GetNumOfElement() || (_index-1) < 0)
	{
		throw("invalid index!");
		return false;
	}
	
	if(!_element)
	{
		throw("invalid element!");
		return false;
	}
	
	if(m_capacity == this->GetNumOfElement() && !Resize())
	{
		throw("realloc failed!");
		return false;
	}
	
	ShiftRight(_index-1);
	m_array[_index-1] = (T*)_element;
	
	this->SetNumOfElements(this->GetNumOfElement() + 1);
			
	return true;
}


template<class T>
bool array<T>::Contains(const T* _element)const
{
	return (SearchElement(_element) == -1) ? false : true;
}

template<class T>
const T* array<T>::Find(const T& _value)const
{
	int index = SearchElement(&_value);
	return (-1 == index) ? NULL : m_array[index];
}

template<class T>
int array<T>::Index(const T* _element)const
{
	return SearchElement(_element);
}		

template<class T>
bool array<T>::Insert(const T* _element)
{
	if(!_element)
	{
		throw("invalid element!");
		return false;
	}
	
	if(this->GetNumOfElement() == m_capacity && !Resize())
	{
		throw("realloc failed!");
		return false;
	}
	
	m_array[this->GetNumOfElement()] = (T*)_element;
	
	this->SetNumOfElements(this->GetNumOfElement() + 1);
	
	return true;
}

// private functions

template<class T>
bool array<T>::Resize()
{
	T** temp = new T*[m_capacity + m_reSize];
	if(!temp)
	{
		return false;
	}
	
	memcpy(temp,m_array,sizeof(m_array)*m_capacity);
	
	delete[] m_array;
	
	m_array = temp;
	m_capacity += m_reSize;
	 
	return true;
}

template<class T>
void array<T>::CopyAllMembers(const array& _arr)
{
	m_array = new T*[_arr.m_capacity];
	memcpy(m_array,_arr.m_array,sizeof(m_array)*m_capacity);
	
	m_capacity = _arr.m_capacity;
	m_reSize = _arr.m_reSize;
}

template<class T>
void array<T>::ShiftRight(unsigned int _index)
{
	int i;
	
	for(i = this->GetNumOfElement();i >= _index; --i)
	{
		m_array[i] = m_array[i-1];
	}
}

template<class T>
int array<T>::SearchElement(const T* _element)const
{
	if(!_element)
	{
		return -1;
	}
	
	int i;
	
	for(i = 0;i < this->GetNumOfElement();++i)
	{
		if(*_element == *m_array[i])
		{
			return i;
		}
	}
	
	return -1;
}

#endif
