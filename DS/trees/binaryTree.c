#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

#define IS_NOT_EXIST(_tree) (NULL == _tree || _tree->m_MagicNumber != MAGIC_NUMBER)

typedef struct Node Node;

struct Node
{
	int m_data;
	Node *m_left;
	Node *m_right;
	Node *m_parent;
};

struct Tree
{
	size_t m_MagicNumber;
	Node *m_root;
};

Tree* TreeCreate()
{
	Tree *tree;

	tree = (Tree*)malloc(sizeof(Tree));
	if(NULL == tree)
	{
		return NULL;
	}

	tree->m_root = NULL;
	tree->m_MagicNumber = MAGIC_NUMBER;

	return tree;
}

static void NodeDestroy(Node *_node)
{
	if(NULL == _node)
	{
		return;
	}

	NodeDestroy(_node->m_left);
	NodeDestroy(_node->m_right);

	free(_node);
}

void TreeDestroy(Tree* _tree)
{
	if(!IS_NOT_EXIST(_tree))
	{
		NodeDestroy(_tree->m_root);

		_tree->m_MagicNumber = NO_MAGIC_NUMBER;
		free(_tree);
	}
}

static Node* FindPosition(Node *_node, int _data)
{
	Node *temp;

	if(NULL == _node || _node->m_data == _data)
	{
		return _node;
	}
	
	temp = (_data > _node->m_data) ? FindPosition(_node->m_right,_data) : FindPosition(_node->m_left,_data);

	if(NULL == temp)
	{
		return _node;
	}

	return temp;
}

static Node* CreateNode(int _data, Node *_parent)
{
	Node *newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if(NULL == newNode)
	{
		return NULL;
	}

	newNode->m_data = _data;
	newNode->m_right = NULL;
	newNode->m_left = NULL;
	newNode->m_parent = _parent;
	
	return newNode;
}

static ErrCode InsertNode(Tree* _tree,int _data)
{
	Node *temp, *newNode;

	temp = FindPosition(_tree->m_root,_data);
	if(temp->m_data == _data)
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	newNode  = CreateNode(_data,temp);
	if(NULL == newNode)
	{
		return ERR_OVERFLOW;
	}

	if(_data > temp->m_data)
	{
		temp->m_right = newNode;
	}
	else
	{
		temp->m_left = newNode;
	}	

	return SUCCEEDED;
}

ErrCode TreeInsert(Tree* _tree, int _data)
{
	if(IS_NOT_EXIST(_tree))
	{
		return ERR_NOT_INITIALIZE;
	}

	if(NULL == _tree->m_root)
	{
		_tree->m_root = CreateNode(_data,NULL);
		return SUCCEEDED;
	}

	return InsertNode(_tree,_data);
	
}

int TreeIsDataFound(Tree* _tree, int _data)
{
	if(IS_NOT_EXIST(_tree))
	{
		return false;
	}

	if(FindPosition(_tree->m_root,_data)->m_data == _data)
	{
		return true;
	}

	return false;
}

static void PreOrder(Node *_node)
{
	if(NULL == _node)
	{
		return;
	}
	
	printf("%d ", _node->m_data);

	PreOrder(_node->m_left);
	PreOrder(_node->m_right);

}

static void InOrder(Node *_node)
{
	if(NULL == _node)
	{
		return;
	}
	
	InOrder(_node->m_left);

	printf("%d ", _node->m_data);

	InOrder(_node->m_right);

}

static void PostOrder(Node *_node)
{
	if(NULL == _node)
	{
		return;
	}

	PostOrder(_node->m_left);

	PostOrder(_node->m_right);

	printf("%d ", _node->m_data);
}

ErrCode TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
	if(IS_NOT_EXIST(_tree))
	{
		return ERR_NOT_INITIALIZE;
	}

	switch (_traverseMode)
	{
		case PRE_ORDER:

			PreOrder(_tree->m_root);
			break;

		case POST_ORDER:

			PostOrder(_tree->m_root);
			break;

		default :

			InOrder(_tree->m_root);
			break;
	}
	printf("\n");

	return SUCCEEDED;
}




