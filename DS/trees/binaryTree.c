#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

#define TREE_MAGIC_NUMBER 0xbeefbeeb
#define IS_NOT_EXIST(_tree) (NULL == _tree || _tree->m_MagicNumber != TREE_MAGIC_NUMBER)

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

/*destroy all nodes*/
static void NodeDestroy(Node *_node);
/*find the position of the data, or the father of the data if NULL*/
static Node* FindPosition(Node *_node, int _data);
/*create a new node*/
static Node* CreateNode(int _data, Node *_parent);
/*insert the new node to the tree*/
static ErrCode InsertNode(Tree* _tree,int _data);
/*print the tree in Pre-order*/
static void PreOrder(Node *_node);
/*print the tree in In-order*/
static void InOrder(Node *_node);
/*print the tree in Post-order*/
static void PostOrder(Node *_node);
/**/
static int IsFullNode(Node *_node);
/**/
static int NodeLevel(Node *_node);
/**/
static int CheckNodes(Node *_node1, Node *_node2);
/**/
static int IsPerfectNode(Node *_node);
/**/
static void MirrorNode(Node *_node);
/**/
static void Swap(Node *_node);


Tree* TreeCreate()
{
	Tree *tree;
	tree = (Tree*)malloc(sizeof(Tree));
	if(NULL == tree)
	{
		return NULL;
	}
	tree->m_root = NULL;
	tree->m_MagicNumber = TREE_MAGIC_NUMBER;
	return tree;
}

void TreeDestroy(Tree* _tree)
{
	if(!IS_NOT_EXIST(_tree))
	{
		NodeDestroy(_tree->m_root);
		_tree->m_MagicNumber = 0;
		free(_tree);
	}
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
		if(NULL == _tree->m_root)
		{
			return ERR_ALLOCATION_FAILED;
		}

		return SUCCEEDED;
	}

	return InsertNode(_tree,_data);
	
}

int TreeIsDataFound(Tree* _tree, int _data)
{
	Node *temp;

	if(IS_NOT_EXIST(_tree))
	{
		return false;
	}

	temp = FindPosition(_tree->m_root,_data);	

	if(NULL != temp && temp->m_data == _data)
	{
		return true;
	}
	return false;
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

int IsFullTree(Tree *_tree)
{
	if(IS_NOT_EXIST(_tree))
	{
		return false;
	}

	return IsFullNode(_tree->m_root);
}


int TreeLevel(Tree *_tree)
{
	if(IS_NOT_EXIST(_tree))
	{
		return -1;
	}

	return NodeLevel(_tree->m_root);
}

int AreSimilar(Tree *_tree1, Tree *_tree2)
{
	if(IS_NOT_EXIST(_tree1) || IS_NOT_EXIST(_tree2))
	{
		return false;
	}

	return CheckNodes(_tree1->m_root,_tree2->m_root);
}

int IsPerfectTree(Tree *_tree)
{
	if(IS_NOT_EXIST(_tree))
	{
		return false;
	}

	if(!_tree->m_root)
	{
		return true;
	}

	return IsPerfectNode(_tree->m_root);
}

ErrCode MirrorTree(Tree *_tree)
{
	if(IS_NOT_EXIST(_tree))
	{
		return ERR_NOT_INITIALIZE;
	}

	MirrorNode(_tree->m_root);

	return SUCCEEDED;
}


/* SUB FUNCTIONS */

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
		return ERR_ALLOCATION_FAILED;
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

static void PreOrder(Node *_node)
{
	if(_node)
	{
		printf("%d ", _node->m_data);
		PreOrder(_node->m_left);
		PreOrder(_node->m_right);		
	}
}

static void InOrder(Node *_node)
{
	if(_node)
	{
		InOrder(_node->m_left);
		printf("%d ", _node->m_data);
		InOrder(_node->m_right);
	}
}

static void PostOrder(Node *_node)
{
	if(_node)
	{
		PostOrder(_node->m_left);
		PostOrder(_node->m_right);
		printf("%d ", _node->m_data);		
	}
}

static int IsFullNode(Node *_node)
{
	if(!_node)
	{
		return true;
	}

	if((!_node->m_left && _node->m_right) || (_node->m_left && !_node->m_right))
	{
		return false;
	}

	return (!IsFullNode(_node->m_left) || !IsFullNode(_node->m_right)) ? false : true;
}

static int NodeLevel(Node *_node)
{
	int l, r;
	if(!_node)
	{
		return -1;
	}

	l = NodeLevel(_node->m_left);
	r = NodeLevel(_node->m_right);

	return (l > r) ? l+1 : r+1;
}

static int CheckNodes(Node *_node1, Node *_node2)
{
	if(!_node1 && !_node2)
	{
		return true;
	}

	if((!_node1 && _node2) || (_node1 && !_node2))
	{
		return false;
	}

	return 	(!CheckNodes(_node1->m_left,_node2->m_left) || !CheckNodes(_node1->m_right,_node2->m_right)) ? false : true;
}

static int IsPerfectNode(Node *_node)
{
	if(!_node)
	{
		return true;
	}

	if((NodeLevel(_node->m_left) != NodeLevel(_node->m_right)))
	{
		return false;
	}
	
	return (IsPerfectNode(_node->m_left) && IsPerfectNode(_node->m_right));
}

static void Swap(Node *_node)
{
	Node *temp = _node->m_left;
	_node->m_left = _node->m_right;
	_node->m_right = temp;
}

static void MirrorNode(Node *_node)
{
	if(!_node)
	{
		return;
	}
	
	MirrorNode(_node->m_left);
	MirrorNode(_node->m_right);

	Swap(_node);
}

