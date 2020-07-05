#ifndef __D_LIST_H__
#define __D_LIST_H__

#include <string.h>
#include "container.h"
#include "TException.h"

template<class T>
class dList:public container<T>
{
	public:
	
	//inherits from container<T>:
	
		//int Count()const;
		//bool IsEmpty()const;
		
	// DTOR
	
		virtual ~dList();
	
	// CTOR
	
		dList() { m_head.m_next = &m_tail; m_tail.m_prev = &m_head; }
		
		dList(const dList& _list);
		
	// operator
		
		dList& operator=(const dList& _list);
		
	// mem functions
		
		//insert the _element in one position right of the _index, throw TException<int> on error.
		virtual bool Append(const T* _element, unsigned int _index);
		
		//insert the _element in one position left of the _index, throw TException<int> on error.
		virtual bool Prepend(const T* _element, unsigned int _index);
		
		//check if the list contains the _element.
		virtual bool Contains(const T* _element)const;
		
		//find the element with _value.
		virtual const T* Find(const T& _value)const;
		
		//return the index of the _element position in the list, -1 if the _element is not in the list.
		virtual int Index(const T* _element)const;
		
		//insert the _element in the last position, throw TException<int> on error.
		virtual bool Insert(const T* _element);
		
		//remove element with _value.
		virtual bool Remove(const T& _value);
		
		//remove all elements.
		virtual void RemoveAll();
		
		//use RemoveAndDelete/RemoveAndDeleteAll only when elements of the object are with allocation.
		
		//remove element and delete the pointer from memory.
		virtual bool RemoveAndDelete(const T& _value);
		
		//remove all elements and delete them.
		virtual void RemoveAndDeleteAll();

	private:
	
		class Node
		{
			public:
			
				friend class dList<T>;
				
				~Node() {}
				
				Node() {}
				Node(const T* _element, const Node* _next, const Node* _prev) 
					{ m_element = (T*)_element; m_next = (Node*)_next; m_prev = (Node*)_prev; }
				Node(const Node* _node) { CopyNode(_node); }
				
				Node* operator=(const Node* _node) { CopyNode(_node); return *this; }
				
			private:
			
				T* m_element;
				Node* m_next;
				Node* m_prev;
				
				void CopyNode(const Node* _node) {m_element = _node->m_element; m_next = _node->m_next; m_prev = _node->m_prev;}
		};
		 
		Node m_head;
		Node m_tail;
		
		//copy all list's elements.
		void CopyAllList(const dList& _list);
		
		//remove all list's elements.
		void RemoveAllNodes();
		
		//remove element with _value from the list.
		Node* RemoveFromList(const T& _value);
		
		//insert _element to _index position, move right all elements till _index position.
		bool InsertByPosition(const T* _element, unsigned int _index);
		
		//set the _element at _index position.
		void SetAtPosition(const T* _element, unsigned int _index);
		
		//insert _element to list after _node.
		void InsetToList(const T* _element, Node* _node);
		
		//seach _element in the list.
		int SearchElement(const T* _element)const;
		
		//find element with _value in the list.
		Node* FindElementByVal(const T& _value)const;
};

// DTOR

template<class T>
dList<T>::~dList()
{
	RemoveAllNodes();
}

// CTOR

template<class T>
dList<T>::dList(const dList& _list):m_head(_list.m_head),m_tail(_list.m_tail)
{
	CopyAllList(_list);
}

template<class T>
dList<T>& dList<T>::operator=(const dList& _list)
{
	if(this != &_list)
	{
		RemoveAllNodes();
		
		CopyAllList(_list);
	}
	
	return *this;
}

// mem functions

template<class T>
bool dList<T>::Append(const T* _element, unsigned int _index)
{
	return InsertByPosition(_element,_index+1);
}

template<class T>
bool dList<T>::Prepend(const T* _element, unsigned int _index)
{
	return InsertByPosition(_element,_index-1);
}

template<class T>
bool dList<T>::Contains(const T* _element)const
{
	return (-1 == SearchElement(_element)) ? false : true;
}

template<class T>
const T* dList<T>::Find(const T& _value)const
{
	Node* find = FindElementByVal(_value);
	
	return (!find) ? NULL : find->m_element;
}

template<class T>
int dList<T>::Index(const T* _element)const
{
	return SearchElement(_element);
}

template<class T>
bool dList<T>::Insert(const T* _element)
{
	if(!_element)
	{
		throw TException<int>(0,__FILE__,__LINE__,"invalid element!");
		return false;
	}
	
	InsetToList(_element,m_tail.m_prev);
	
	return true;
}

template<class T>
bool dList<T>::Remove(const T& _value)
{
	Node* remove = RemoveFromList(_value);
	if(!remove)
	{
		return false;
	}
	
	remove->m_element = NULL;
	delete remove;
	
	return true;
}

template<class T>
void dList<T>::RemoveAll()
{
	RemoveAllNodes();
}

template<class T>
bool dList<T>::RemoveAndDelete(const T& _value)
{
	Node* remove = RemoveFromList(_value);
	if(!remove)
	{
		return false;
	}
	
	delete remove->m_element;
	remove->m_element = NULL;
	
	delete remove;
	
	return true;
}

template<class T>
void dList<T>::RemoveAndDeleteAll()
{
	Node* n(m_head.m_next);
	Node* temp;
	
	while(n != (&m_tail))
	{
		temp = n;
		n = n->m_next;
		
		temp->m_next = NULL;
		temp->m_prev = NULL;
		
		delete temp->m_element;
		delete temp;
	}
	
	this->SetNumOfElements(0);
}

// private functions

template<class T>
void dList<T>::CopyAllList(const dList& _list)
{
	m_head = _list.m_head;
	m_tail = _list.m_tail;
	
	Node* temp = _list.m_head;
	
	while(temp != _list.m_tail)
	{
		InsetToList(temp->m_element,m_tail->m_prev);
		temp = temp->m_next;
	}
	
	SetNumOfElements(_list.Count());
}

template<class T>
void dList<T>::RemoveAllNodes()
{
	Node* n(m_head.m_next);
	
	while(n != (&m_tail))
	{
		Node* temp(n);
		n = n->m_next;
		
		delete temp;
	}
	
	this->SetNumOfElements(0);
}

template<class T>
class dList<T>::Node* dList<T>::RemoveFromList(const T& _value)
{
	Node* remove = FindElementByVal(_value);
	if(!remove)
	{
		return NULL;
	}
	
	remove->m_next->m_prev = remove->m_prev;
	remove->m_prev->m_next = remove->m_next;
	
	remove->m_next = NULL;
	remove->m_prev = NULL;
	
	this->SetNumOfElements(this->Count() - 1);
	
	return remove;
}

template<class T>
bool dList<T>::InsertByPosition(const T* _element, unsigned int _index)
{
	if(_index > this->Count() || _index < 0)
	{
		throw TException<int>(0,__FILE__,__LINE__,"invalid index!");
		return false;
	}
	
	if(!_element)
	{
		throw TException<int>(0,__FILE__,__LINE__,"invalid element!");
		return false;
	}
	
	SetAtPosition(_element,_index);
	
	return true;
}

template<class T>
void dList<T>::SetAtPosition(const T* _element, unsigned int _index)
{
	int i;
	Node* n(&m_head);
	
	for(i = 0;i < _index;++i)
	{
		n = n->m_next;
	}
	
	InsetToList(_element,n);
}

template<class T>
void dList<T>::InsetToList(const T* _element, Node* _node)
{
	Node* newNode = new Node(_element,_node->m_next,_node);
			
	_node->m_next->m_prev = newNode;
	_node->m_next = newNode;
	
	this->SetNumOfElements(this->Count() + 1);
}

template<class T>
int dList<T>::SearchElement(const T* _element)const
{
	Node* n(m_head.m_next);
	int i = 0;
	
	while(n != (&m_tail))
	{
		if(_element == n->m_element)
		{
			return i;
		}
		
		n = n->m_next;
		++i;
	}
	
	return -1;
}

template<class T>
class dList<T>::Node* dList<T>::FindElementByVal(const T& _value)const
{
	Node* n(m_head.m_next);
	
	while(n != (&m_tail))
	{
		if(_value == *n->m_element)
		{
			return n;
		}
		
		n = n->m_next;
	}
	
	return NULL;
}


#endif
