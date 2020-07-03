#ifndef __D_LIST_H__
#define __D_LIST_H__

#include <string.h>
#include "container.h"

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
		
		dList(const dList& _list) {} // TODO
		
	// operator
		
		dList& operator=(const dList& _list) {} // TODO
		
	// mem functions
		
		virtual bool Append(const T* _element, unsigned int _index);
		
		virtual bool Prepend(const T* _element, unsigned int _index);
		
		virtual bool Contains(const T* _element)const;
		
		virtual const T* Find(const T& _value)const;
		
		virtual int Index(const T* _element)const;
		
		virtual bool Insert(const T* _element);
		
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
				Node(const T* _element, const Node* _next, const Node* _prev) { m_element = (T*)_element; m_next = (Node*)_next; m_prev = (Node*)_prev; }
				Node(const Node* _node) { CopyNode(_node); }
				
				Node* operator=(const Node* _node) { CopyNode(_node); return *this; }
				
				//const T* GetData()const { return m_element; }
				
				//void SetNext(const Node* _next) { m_next = (Node*)_next; }
				//Node* GetNext()const { return m_next; }
				
				//void SetPrev(const Node* _prev) { m_prev = (Node*)_prev; }
				//Node* GetPrev()const { return m_prev; }
				
			private:
			
				T* m_element;
				Node* m_next;
				Node* m_prev;
				
				void CopyNode(const Node* _node) {m_element = _node->m_element; m_next = _node->m_next; m_prev = _node->m_prev;}
		};
		 
		Node m_head;
		Node m_tail;
		
		void RemoveAllElements();
		
		bool InsertByPosition(const T* _element, unsigned int _index);
		
		void SetAtPosition(const T* _element, unsigned int _index);
		
		void InsetToList(const T* _element, Node* _node);
		
		int SearchElement(const T* _element)const;

		Node* FindElementByVal(const T& _value)const;
		
		Node* RemoveFromList(const T& _value);
};

template<class T>
dList<T>::~dList()
{
	RemoveAllElements();
}

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
	return FindElementByVal(_value)->m_element;
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
	RemoveAllElements();
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
	
	while(n != (&m_tail))
	{
		Node* temp(n);
		n = n->m_next;
		
		temp->m_next = NULL;
		temp->m_prev = NULL;
		
		delete temp->m_element;
		delete temp;
	}
}

// private functions

template<class T>
void dList<T>::RemoveAllElements()
{
	Node* n(m_head.m_next);
	
	while(n != (&m_tail))
	{
		Node* temp(n);
		n = n->m_next;
		
		delete temp;
	}
}

template<class T>
bool dList<T>::InsertByPosition(const T* _element, unsigned int _index)
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
	int i = 0;
	
	while(n != (&m_tail))
	{
		if(_value == *n->m_element)
		{
			return n;
		}
		
		n = n->m_next;
		++i;
	}
	
	return NULL;
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
	
	return remove;
}


#endif
