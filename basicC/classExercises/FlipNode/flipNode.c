#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ADTErrors.h"

#define IS_NOT_EXIST(_pers) (NULL == _pers || (*_pers).m_MagicNumber != MAGIC_NUMBER)

typedef struct Node
{
	size_t m_MagicNumber;
	int m_data;
	struct Node *m_next;
}Node;

Node* CreateNode(Node *_head, int _data)
{
	Node *newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if(NULL == newNode)
	{
		return NULL;
	}
	newNode->m_data = _data;
	newNode->m_next = _head;
	newNode->m_MagicNumber = MAGIC_NUMBER;

	return newNode;
}

void DestroyList(Node *_head)
{
	if(IS_NOT_EXIST(_head))
	{
		return;
	}

	DestroyList(_head->m_next);

	_head->m_MagicNumber = NO_MAGIC_NUMBER;
	free(_head);
}

Node* CreateList(int _size)
{
	Node *head = NULL;
	int i;
	time_t t;
	srand((unsigned)time(&t));

	for(i = 0;i < _size;++i)
	{
		head = CreateNode(head,rand()%100);
	}

	return head;
}

Node* Flip(Node* _node)
{
	Node *result;
	if(NULL == _node)
	{
		return _node;
	}

	result = Flip(_node->m_next);

	if(NULL == result)
	{
		return _node;
	}

	_node->m_next->m_next = _node;
	_node->m_next = NULL;

	return result;
}

void PrintListR(Node *_head)
{
	if(IS_NOT_EXIST(_head))
	{
		return;
	}

	printf("%d ",_head->m_data);

	PrintListR(_head->m_next);
}

int main()
{
	Node *head = CreateList(5);

	printf("\n");
	PrintListR(head);
	printf("\n");

	head = Flip(head);
	PrintListR(head);
	printf("\n");

	DestroyList(head);

	return 0;
}












