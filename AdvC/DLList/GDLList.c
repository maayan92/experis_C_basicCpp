#include <stdio.h>
#include <stdlib.h>
#include "GDLList.h"
#include "GDLList_Itr.h"

#define DLL_MAGIC_NUMBER 0xbeefbeea
#define IS_NOT_EXIST(_list) (NULL == _list || _list->m_magicNumber != DLL_MAGIC_NUMBER)

typedef struct Node
{
	void* m_data;
	struct Node *m_prev;
	struct Node *m_next;
}Node;

struct DoubleLinkedList 
{
	size_t m_magicNumber;
	Node m_head;
	Node m_tail;	
};

/**/
static void DestroyNode(Node *_node);
/**/
static ErrCode AddData(List* _list, Node *_node, void* _data);
/**/
static size_t CountItemsR(Node *_node);
/**/
static void PrintNodesR(Node *_node, ptrElementFun _printElement);
/**/
static void RemoveData(List* _list, Node *_node, void**_data);


List* DLListCreate()
{
	List *list = (List *)malloc(sizeof(List));

	if(NULL == list)
	{
		return NULL;
	}

	(list->m_head).m_data = NULL;
	(list->m_tail).m_data = NULL;
	
	(list->m_head).m_prev = NULL;
	(list->m_head).m_next = &(list->m_tail);
	
	(list->m_tail).m_prev = &(list->m_head);
	(list->m_tail).m_next = NULL;
	list->m_magicNumber = DLL_MAGIC_NUMBER;

	return list;
}

void DLListDestroy(List* _list, ptrElementFun _destroyElement)
{
	if(IS_NOT_EXIST(_list))
	{
		return;
	}
	
	while(_list->m_head.m_next != &(_list->m_tail))
	{
		if(NULL != _destroyElement)
		{
			_destroyElement((_list->m_head).m_next->m_data);
		}
		
		DestroyNode((_list->m_head).m_next);
		_list->m_head = *((_list->m_head).m_next);
	}

	_list->m_magicNumber = 0;
	free(_list);
}

ErrCode DLListPushHead(List* _list, void* _data)
{
	if(IS_NOT_EXIST(_list))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(!_data)
	{
		return ERR_ILLEGAL_INPUT;
	}

	return AddData(_list,&(_list->m_head),_data);
}

ErrCode DLListPushTail(List* _list, void* _data)
{
	if(IS_NOT_EXIST(_list))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(!_data)
	{
		return ERR_ILLEGAL_INPUT;
	}

	return AddData(_list,_list->m_tail.m_prev,_data);
}

ErrCode DLListPopHead(List* _list, void**_data)
{

	if(IS_NOT_EXIST(_list))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(!_data)
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return ERR_UNDERFLOW;
	}

	RemoveData(_list,&(_list->m_head),_data);

	return SUCCEEDED;
}

ErrCode DLListPopTail(List* _list, void**_data)
{

	if(IS_NOT_EXIST(_list))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(!_data)
	{
		return ERR_ILLEGAL_INPUT;
	}

	if(_list->m_tail.m_prev == &(_list->m_head))
	{
		return ERR_UNDERFLOW;
	}

	RemoveData(_list,_list->m_tail.m_prev->m_prev,_data);
	
	return SUCCEEDED;
}

size_t DLListCountItems(const List* _list)
{
	if(IS_NOT_EXIST(_list))
	{
		return 0;
	}
	
	return CountItemsR(_list->m_head.m_next);
}

int DLListIsEmpty(const List* _list)
{
	if(IS_NOT_EXIST(_list))
	{
		return false;
	}
	
	return (&(_list->m_tail) == _list->m_head.m_next);
}

void DLListPrint(const List *_list, ptrElementFun _printElement)
{
	if(IS_NOT_EXIST(_list) || NULL == _printElement)
	{
		return;
	}

	PrintNodesR(_list->m_head.m_next,_printElement);
}

/* ITERATOR FUNCTIONS */

ListItr ListItrBegin(const List* _list)
{
	if(IS_NOT_EXIST(_list))
	{
		return NULL;
	}
	
	return (_list->m_head).m_next;
}

ListItr ListItrEnd(const List* _list)
{
	
	if(IS_NOT_EXIST(_list))
	{
		return NULL;
	}
	
	return (ListItr)(&_list->m_tail);
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
	if(NULL == _a || NULL == _b)
	{
		return false;
	}
	
	return ((Node*)_a == (Node*)_b);
}

ListItr ListItrNext(ListItr _itr)
{
	if(NULL == _itr)
	{
		return NULL;
	}
	
	return (NULL == ((Node*)_itr)->m_next) ? (Node*)_itr : ((Node*)_itr)->m_next;
}

void* ListItrGet(ListItr _itr)
{
	if(NULL == _itr)
	{
		return NULL;
	}
	
	return ((Node*)_itr)->m_data;
}


/* SUB FUNCTIONS */

static void DestroyNode(Node *_node)
{
	if(NULL != _node)
	{	
		free(_node);
		_node = NULL;
	}
} 

static ErrCode AddData(List* _list, Node *_node, void* _data)
{
	Node *newNode;

	newNode = (Node *)malloc(sizeof(Node));

	if(NULL == newNode)
	{
		return ERR_ALLOCATION_FAILED;
	}

	newNode->m_data = _data;

	newNode->m_prev = _node;
	newNode->m_next = _node->m_next;
	_node->m_next = newNode;
	newNode->m_next->m_prev = newNode;
	
	return SUCCEEDED;
}

static size_t CountItemsR(Node *_node)
{
	if(NULL == _node->m_next)
	{
		return 0;
	}

	return CountItemsR(_node->m_next)+1;
}

static void PrintNodesR(Node *_node, ptrElementFun _printElement)
{
	if(NULL == _node->m_next)
	{
		return;
	}

	_printElement(_node->m_data);
	
	PrintNodesR(_node->m_next,_printElement);
}

static void RemoveData(List* _list, Node *_node, void**_data)
{
	Node *temp;

	*_data = _node->m_next->m_data;
	temp = _node->m_next;
	_node->m_next = _node->m_next->m_next;
	_node->m_next->m_prev = _node;

	DestroyNode(temp);
	temp = NULL;
}





