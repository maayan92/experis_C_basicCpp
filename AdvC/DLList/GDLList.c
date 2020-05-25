#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

/*create a new node*/
static Node* CreateNode(void* _data);
/*destroy the node*/
static void* DestroyNode(Node *_node);
/*add new data to the list*/
static Node* AddData(Node *_node, void* _data);
/*count the items in the list*/
static size_t CountItemsR(Node *_node);
/*print the elements of the list*/
static void PrintNodesR(Node *_node, ptrElementFun _printElement);
/*remove the data from the list*/
static void* RemoveData(Node *_node);


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
	
	_list->m_magicNumber = 0;

	while(_list->m_head.m_next != &(_list->m_tail))
	{
		if(NULL != _destroyElement)
		{
			_destroyElement((_list->m_head).m_next->m_data);
		}
		
		_list->m_head.m_next = (_list->m_head).m_next->m_next;
		DestroyNode((_list->m_head).m_next->m_prev);
		(_list->m_head).m_next->m_prev = &(_list->m_head);
	}

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

	return (NULL == AddData(&(_list->m_head),_data)) ? ERR_ALLOCATION_FAILED : SUCCEEDED;
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

	return (NULL == AddData(_list->m_tail.m_prev,_data)) ? ERR_ALLOCATION_FAILED : SUCCEEDED;
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

	(*_data) = RemoveData(&(_list->m_head));

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

	(*_data) = RemoveData(_list->m_tail.m_prev->m_prev);
	
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
	
	return _list->m_head.m_next;
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
	return ((Node*)_a == (Node*)_b);
}

ListItr ListItrNext(ListItr _itr)
{
	return (NULL == ((Node*)_itr)->m_next) ? (Node*)_itr : ((Node*)_itr)->m_next;
}

ListItr ListItrPrev(ListItr _itr)
{
	return (NULL == ((Node*)_itr)->m_prev) ? (Node*)_itr : ((Node*)_itr)->m_prev;
}

void* ListItrGet(ListItr _itr)
{
	return ((Node*)_itr)->m_data;
}

void* ListItrSet(ListItr _itr, void* _data)
{
	void* data = ((Node*)_itr)->m_data;
	((Node*)_itr)->m_data = _data;
	
	return data;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _data)
{
	if(NULL == ((Node*)_itr)->m_prev)
	{
		return NULL;
	}
	
	return AddData(((Node*)_itr)->m_prev,_data);
}

void* ListItrRemove(ListItr _itr)
{
	return (NULL == ((Node*)_itr)->m_next) ? NULL : RemoveData(((Node*)_itr)->m_prev);
}

/* SUB FUNCTIONS */


static Node* CreateNode(void* _data)
{
	Node *newNode;

	newNode = (Node *)malloc(sizeof(Node));

	if(NULL == newNode)
	{
		return NULL;
	}
	
	newNode->m_data = _data;
	
	return newNode; 
}

static void* DestroyNode(Node *_node)
{
	void* tData;
	
	assert(_node);
	
	tData = _node->m_data;
	free(_node);
	
	return tData;
}

static Node* AddData(Node *_node, void* _data)
{
	Node* newNode;
	if(!(newNode = CreateNode(_data)))
	{
		return NULL;
	}
	
	newNode->m_prev = _node;
	newNode->m_next = _node->m_next;
	_node->m_next = newNode;
	newNode->m_next->m_prev = newNode;
	
	return newNode;
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

static void* RemoveData(Node *_node)
{
	Node *temp;
	void* data;

	temp = _node->m_next;
	_node->m_next = _node->m_next->m_next;
	_node->m_next->m_prev = _node;

	data = DestroyNode(temp);
	temp = NULL;
	
	return data;
}





