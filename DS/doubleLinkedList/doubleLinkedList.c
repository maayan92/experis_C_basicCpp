#include <stdio.h>
#include <stdlib.h>
#include "doubleLinkedList.h"

#define IS_NOT_EXIST(_list) (NULL == _list || _list->m_magicNumber != MAGIC_NUMBER)

typedef struct Node
{
	int m_data;
	struct Node *m_prev;
	struct Node *m_next;
}Node;

struct DoubleLinkedList 
{
	size_t m_magicNumber;
	Node m_head;
	Node m_tail;	
};

List* DLListCreate()
{
	List *list = (List *)malloc(sizeof(List));

	if(NULL == list)
	{
		return NULL;
	}

	(list->m_head).m_prev = NULL;
	(list->m_head).m_next = &(list->m_tail);
	(list->m_tail).m_prev = &(list->m_head);
	(list->m_tail).m_next = NULL;
	list->m_magicNumber = MAGIC_NUMBER;

	return list;
}

static void DestroyNode(Node *_node)
{
	if(NULL != _node)
	{
		free(_node);
		_node = NULL;
	}
} 

void DLListDestroy(List* _list)
{
	if(IS_NOT_EXIST(_list))
	{
		return;
	}
	
	while(_list->m_head.m_next != &(_list->m_tail))
	{
		DestroyNode((_list->m_head).m_next);
		_list->m_head = *((_list->m_head).m_next);
	}

	_list->m_magicNumber = NO_MAGIC_NUMBER;
	free(_list);
}

static ErrCode AddData(List* _list, Node *_node, int _data)
{
	Node *newNode;

	newNode = (Node *)malloc(sizeof(Node));

	if(NULL == newNode)
	{
		return ERR_OVERFLOW;
	}

	newNode->m_data = _data;

	newNode->m_prev = _node;
	newNode->m_next = _node->m_next;
	_node->m_next = newNode;
	newNode->m_next->m_prev = newNode;
	
	return SUCCEEDED;
}

ErrCode DLListPushHead(List* _list, int _data)
{
	if(IS_NOT_EXIST(_list))
	{
		return ERR_NOT_INITIALIZE;
	}

	return AddData(_list,&(_list->m_head),_data);
}

ErrCode DLListPushTail(List* _list, int _data)
{
	if(IS_NOT_EXIST(_list))
	{
		return ERR_NOT_INITIALIZE;
	}

	return AddData(_list,_list->m_tail.m_prev,_data);
}

void RemoveData(List* _list, Node *_node, int *_data)
{
	Node *temp;

	*_data = _node->m_next->m_data;
	temp = _node->m_next;
	_node->m_next = _node->m_next->m_next;
	_node->m_next->m_prev = _node;

	DestroyNode(temp);
	temp = NULL;
}

ErrCode DLListPopHead(List* _list, int *_data)
{

	if(IS_NOT_EXIST(_list) || !_data)
	{
		return ERR_NOT_INITIALIZE;
	}

	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return ERR_UNDERFLOW;
	}

	RemoveData(_list,&(_list->m_head),_data);

	return SUCCEEDED;
}

ErrCode DLListPopTail(List* _list, int *_data)
{

	if(IS_NOT_EXIST(_list) || !_data)
	{
		return ERR_NOT_INITIALIZE;
	}

	if(_list->m_tail.m_prev == &(_list->m_head))
	{
		return ERR_UNDERFLOW;
	}

	RemoveData(_list,_list->m_tail.m_prev->m_prev,_data);
	
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

size_t DLListCountItems(List* _list)
{
	if(IS_NOT_EXIST(_list))
	{
		return 0;
	}
	
	return CountItemsR(_list->m_head.m_next);
}

int DLListIsEmpty(List* _list)
{
	if(IS_NOT_EXIST(_list))
	{
		return false;
	}
	
	return (&(_list->m_tail) == _list->m_head.m_next);
}

static void PrintNodesR(Node *_node)
{
	if(NULL == _node->m_next)
	{
		return;
	} 	

	printf("%d ", _node->m_data);

	PrintNodesR(_node->m_next);
}

void DLListPrint(List *_list)
{
	if(IS_NOT_EXIST(_list))
	{
		return;
	}

	PrintNodesR(_list->m_head.m_next);
}






