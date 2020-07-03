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
	
	// DTOR
	
		virtual ~array() { delete[] m_array; this->SetNumOfElements(0); }
	
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
		
		//remove element with _value.
		virtual bool Remove(const T& _value);
		
		//remove all elements.
		virtual void RemoveAll() { this->SetNumOfElements(0); }
		
		//use RemoveAndDelete/RemoveAndDeleteAll only when elements of the object are with allocation.
		
		//remove element and delete the pointer from memory.
		virtual bool RemoveAndDelete(const T& _value);
		
		//remove all elements and delete them.
		virtual void RemoveAndDeleteAll();
	
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
		
		// search element in the array, return _element index or -1.
		int SearchElement(const T* _element)const;
		
		//insert a new element at position _index.
		bool InsertByPosition(const T* _element, unsigned int _index);
		
		// move elements in [_index,numOfElements] range one step to the right.
		void ShiftRight(unsigned int _index);
		
		// move elements in [_index+1,numOfElements] range one step to the left.
		void ShiftLeft(unsigned int _index);
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
	
	return *this;
}

// mem function

template<class T>
bool array<T>::Append(const T* _element, unsigned int _index)
{
	return InsertByPosition(_element,_index+1);
}

template<class T>
bool array<T>::Prepend(const T* _element, unsigned int _index)
{
	return InsertByPosition(_element,_index-1);
}


template<class T>
bool array<T>::Contains(const T* _element)const
{
	return (-1 == SearchElement(_element)) ? false : true;
}

template<class T>
const T* array<T>::Find(const T& _value)const
{
	int i;
	
	for(i = 0;i < this->Count();++i)
	{
		if(_value == *m_array[i])
		{
			return m_array[i];
		}
	}
	
	return NULL;
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
	
	if(this->Count() == m_capacity && !Resize())
	{
		throw("realloc failed!");
		return false;
	}
	
	m_array[this->Count()] = (T*)_element;
	
	this->SetNumOfElements(this->Count() + 1);
	
	return true;
}

template<class T>
bool array<T>::Remove(const T& _value)
{
	int index = SearchElement(&_value);
	
	if(-1 == index)
	{
		return false;
	}
	
	ShiftLeft(index);
	this->SetNumOfElements(this->Count() - 1);
	
	return true;
}

template<class T>
bool array<T>::RemoveAndDelete(const T& _value)
{
	int index = SearchElement(&_value);
	
	if(-1 == index)
	{
		return false;
	}
	
	T* temp = m_array[index];
	
	ShiftLeft(index);
	this->SetNumOfElements(this->Count() - 1);
	
	delete temp;
	
	return true;
}

template<class T>
void array<T>::RemoveAndDeleteAll()
{
	int i;
	
	for(i = 0;i < this->Count();++i)
	{
		delete m_array[i];
	}
	
	this->SetNumOfElements(0);
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
	m_capacity = _arr.m_capacity;
	m_reSize = _arr.m_reSize;
	this->SetNumOfElements(_arr.Count());
	
	m_array = new T*[m_capacity];
	memcpy(m_array,_arr.m_array,sizeof(m_array)*this->Count());
}

template<class T>
int array<T>::SearchElement(const T* _element)const
{
	if(!_element)
	{
		return -1;
	}
	
	int i;
	
	for(i = 0;i < this->Count();++i)
	{
		if(*_element == *m_array[i])
		{
			return i;
		}
	}
	
	return -1;
}

template<class T>
bool array<T>::InsertByPosition(const T* _element, unsigned int _index)
{
	if(_index > this->Count() || _index < 0)
	{
		throw("invalid index!");
		return false;
	}
	
	if(!_element)
	{
		throw("invalid element!");
		return false;
	}
	
	if(m_capacity == this->Count() && !Resize())
	{
		throw("realloc failed!");
		return false;
	}
	
	ShiftRight(_index);
	m_array[_index] = (T*)_element;
	
	this->SetNumOfElements(this->Count() + 1);
	
	return true;
}

template<class T>
void array<T>::ShiftRight(unsigned int _index)
{
	int i;
	
	for(i = this->Count();i >= _index; --i)
	{
		m_array[i] = m_array[i-1];
	}
}

template<class T>
void array<T>::ShiftLeft(unsigned int _index)
{
	while(_index < (this->Count() - 1))
	{
		m_array[_index] = m_array[_index+1];
		++_index;
	}
}



#endif
