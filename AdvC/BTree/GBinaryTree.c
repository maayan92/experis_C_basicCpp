#include <stdio.h>
#include <stdlib.h>
#include "GBinaryTree.h"

#define TREE_MAGIC_NUMBER 0xbeefbeeb
#define IS_NOT_EXIST(_tree) (NULL == _tree || _tree->m_MagicNumber != TREE_MAGIC_NUMBER)

typedef struct Node Node;

struct Node
{
	void* m_data;
	Node *m_left;
	Node *m_right;
	Node *m_parent;
};

struct Tree
{
	size_t m_MagicNumber;
	Node m_root;
	LessComparator m_lessFun;
};

/*destroy all nodes and the data*/
static void NodeAndDataDestroy(Node *_node, void(*_destroyer)(void*));
/*destroy all nodes only*/
static void NodeDestroy(Node *_node);
/*find the position of the data, or the father of the data if NULL*/
static Node* FindPosition(Node *_node, void* _data, LessComparator _less);
/*create a new node*/
static Node* CreateNode(void* _data, Node *_parent);
/*insert the new node to the tree*/
static BSTreeItr InsertNode(Tree* _tree, void* _data);
/*Do action on every tree elements in Pre-order*/
static BSTreeItr PreOrder(Node *_node, ActionFunction _action, void* _context);
/*Do action on every tree elements in In-order*/
static BSTreeItr InOrder(Node *_node, ActionFunction _action, void* _context);
/*Do action on every tree elements in Post-order*/
static BSTreeItr PostOrder(Node *_node, ActionFunction _action, void* _context);
/*give the smallest data from the left child*/
static Node* GetSmallestLeft(Node *_node);
/*give the biggest data from the right child*/
static Node* GetBiggestRight(Node *_node);
/*get parent next element*/
static Node* GetNextRoot(Node *_node);
/*get parent prev element*/
static Node* GetPrevRoot(Node *_node);
/*set the replacing node in the _node place*/
static void SetTheReplaceNode(Node *_node, Node *_replace);


Tree* TreeCreate(LessComparator _less)
{
	Tree *tree;
	
	if(NULL == _less)
	{
		return NULL;
	}
	
	tree = (Tree*)malloc(sizeof(Tree));
	if(NULL == tree)
	{
		return NULL;
	}
	
	tree->m_root.m_left = &(tree->m_root);
	tree->m_root.m_right = &(tree->m_root);
	tree->m_root.m_parent = NULL;
	tree->m_root.m_data = NULL;
	tree->m_lessFun = _less;
	tree->m_MagicNumber = TREE_MAGIC_NUMBER;
	
	return tree;
}

void TreeDestroy(Tree* _tree, void(*_destroyer)(void*))
{
	if(IS_NOT_EXIST(_tree))
	{
		return;		
	}
	
	_tree->m_MagicNumber = 0;
	
	if(!TREE_ITR_EQUALS(&(_tree->m_root),_tree->m_root.m_left))
	{
		if(NULL == _destroyer)
		{
			NodeDestroy(_tree->m_root.m_left);
		}
		else
		{
			NodeAndDataDestroy(_tree->m_root.m_left,_destroyer);
		}	
	}
	
	free(_tree);
}

BSTreeItr TreeInsert(Tree* _tree, void* _data)
{
	if(IS_NOT_EXIST(_tree))
	{
		return NULL;
	}
	
	if(!_data)
	{
		return (BSTreeItr)&(_tree->m_root);
	}

	if(TREE_ITR_EQUALS(&(_tree->m_root),_tree->m_root.m_left))
	{
		_tree->m_root.m_left = CreateNode(_data,&(_tree->m_root));
		if(!(_tree->m_root.m_left))
		{
			return (BSTreeItr)&(_tree->m_root);
		}

		return _tree->m_root.m_left;
	}

	return InsertNode(_tree,_data);
	
}

/* ITERATORS */

BSTreeItr BSTreeItrBegin(const Tree* _tree)
{
	if(IS_NOT_EXIST(_tree))
	{
		return NULL;
	}
	
	if(TREE_ITR_EQUALS(&(_tree->m_root),_tree->m_root.m_left))
	{
		return (BSTreeItr)&(_tree->m_root);
	}
	
	return GetSmallestLeft(_tree->m_root.m_left->m_left);
}

BSTreeItr BSTreeItrEnd(const Tree* _tree)
{
	if(IS_NOT_EXIST(_tree))
	{
		return NULL;
	}
	
	return (BSTreeItr)&(_tree->m_root);
}

BSTreeItr BSTreeItrNext(BSTreeItr _itr)
{
	Node* temp = GetSmallestLeft(((Node*)_itr)->m_right);
	
	return (!temp) ? GetNextRoot((Node*)_itr) : temp;
}

BSTreeItr BSTreeItrPrev(BSTreeItr _itr)
{	
	Node* temp = GetBiggestRight(((Node*)_itr)->m_left);

	return (!temp) ? GetPrevRoot((Node*)_itr) : temp;
}

void* BSTreeItrRemove(BSTreeItr _itr)
{
	Node *replaceItr = (Node*)BSTreeItrNext(_itr);
	void *data = ((Node*)_itr)->m_data;
	
	if(TREE_ITR_EQUALS(((Node*)_itr)->m_parent,replaceItr))
	{
		replaceItr = (Node*)BSTreeItrPrev(_itr);
	}
	
	if(!((Node*)_itr)->m_left && ! ((Node*)_itr)->m_right)
	{
		replaceItr = NULL;
	}

	SetTheReplaceNode((Node*)_itr,replaceItr);
	
	NodeDestroy(_itr);
	
	return data;
}

static void SetTheReplaceNode(Node *_node, Node *_replace)
{
	if(TREE_ITR_EQUALS(_node->m_parent->m_right,_node))
	{
		_node->m_parent->m_right = _replace;
	}else
	{
		_node->m_parent->m_left = _replace;
	}
	
	if(_replace && !TREE_ITR_EQUALS(_node->m_parent,_replace))
	{
		_replace->m_parent = _node->m_parent;
		
		if(!TREE_ITR_EQUALS(_node->m_left,_replace) && _node->m_left)
		{
			_replace->m_left = _node->m_left;
			_node->m_left->m_parent = _replace;
		}
	}
	
	_node->m_left = NULL;
	_node->m_right = NULL;
}

void* BSTreeItrGet(BSTreeItr _itr)
{
	return ((Node*)_itr)->m_data;
}

BSTreeItr BSTreeForEach(const Tree* _tree, TreeTraverse _mode, ActionFunction _action, void* _context)
{
	BSTreeItr itr;
	
	if(IS_NOT_EXIST(_tree))
	{
		return NULL;
	}

	switch (_mode)
	{
		case PRE_ORDER:
		
			itr = PreOrder(_tree->m_root.m_left,_action,_context);
		
		case POST_ORDER:
		
			itr = PostOrder(_tree->m_root.m_left,_action,_context);
		
		default :
		
			itr = InOrder(_tree->m_root.m_left,_action,_context);
	}
	
	return (!itr) ? BSTreeItrEnd(_tree) : itr;
}


/* SUB FUNCTIONS */

static void NodeDestroy(Node *_node)
{
	if(!_node)
	{
		return;
	}
	
	NodeDestroy(_node->m_left);
	NodeDestroy(_node->m_right);
	free(_node);
}

static void NodeAndDataDestroy(Node *_node, void(*_destroyer)(void*))
{
	if(!_node)
	{
		return;
	}
	
	NodeAndDataDestroy(_node->m_left,_destroyer);
	NodeAndDataDestroy(_node->m_right,_destroyer);
	
	_destroyer(_node->m_data);
	free(_node);
}

static Node* FindPosition(Node *_node, void* _data, LessComparator _less)
{
	Node *temp;
	if(!_node)
	{
		return NULL;
	}
	
	if(_less(_node->m_data,_data))
	{
		temp = FindPosition(_node->m_right,_data,_less);
	}
	else
	{
		temp = (_less(_data,_node->m_data)) ? FindPosition(_node->m_left,_data,_less) : _node;
	}

	if(!temp)
	{
		return _node;
	}
	
	return temp;
}

static Node* CreateNode(void* _data, Node *_parent)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	if(!newNode)
	{
		return NULL;
	}
	
	newNode->m_data = _data;
	newNode->m_right = NULL;
	newNode->m_left = NULL;
	newNode->m_parent = _parent;
	
	return newNode;
}

static BSTreeItr InsertNode(Tree* _tree, void* _data)
{
	Node *temp, *newNode;
	
	temp = FindPosition(_tree->m_root.m_left,_data,_tree->m_lessFun);
	if(!temp || (!_tree->m_lessFun(temp->m_data,_data) && !_tree->m_lessFun(_data,temp->m_data)))
	{
		return (BSTreeItr)&(_tree->m_root);
	}
	
	newNode  = CreateNode(_data,temp);
	if(!newNode)
	{
		return (BSTreeItr)&(_tree->m_root);
	}
	
	if(_tree->m_lessFun(temp->m_data,_data))
	{
		temp->m_right = newNode;
	}
	else
	{
		temp->m_left = newNode;
	}
			
	return newNode;
}

static Node* GetSmallestLeft(Node *_node)
{
	if(!_node || !(_node->m_left))
	{
		return _node;
	}
	
	if(!(_node->m_parent))
	{
		return _node;
	}
	
	return GetSmallestLeft(_node->m_left);
}

static Node* GetBiggestRight(Node *_node)
{
	if(!_node || !(_node->m_right))
	{
		return _node;
	}
	
	if(!(_node->m_parent))
	{
		return _node;
	}
	
	return GetBiggestRight(_node->m_right);
}

static Node* GetNextRoot(Node *_node)
{
	if(!_node || !(_node->m_parent))
	{
		return _node->m_left;
	}
	
	if(!(_node->m_parent))
	{
		return _node;
	}
	
	if(TREE_ITR_EQUALS(_node,_node->m_parent->m_left))
	{
		return _node->m_parent;
	}
	
	return GetNextRoot(_node->m_parent);
}

static Node* GetPrevRoot(Node *_node)
{
	if(!_node)
	{
		return _node->m_left;
	}
	
	if(!(_node->m_parent))
	{
		return _node;
	}
	
	if(TREE_ITR_EQUALS(_node,_node->m_parent->m_right))
	{
		return _node->m_parent;
	}
	
	return GetPrevRoot(_node->m_parent);
}

static BSTreeItr PreOrder(Node *_node, ActionFunction _action, void* _context)
{
	Node *temp = _node;
	
	if(_node)
	{
		if(!_action(_node->m_data,_context))
		{
			return _node;
		}
		
		temp = PreOrder(_node->m_left,_action,_context);
		
		if(!temp)
		{
			PreOrder(_node->m_right,_action,_context);
		}	
	}
	
	return (temp) ? temp : NULL;
}

static BSTreeItr InOrder(Node *_node, ActionFunction _action, void* _context)
{
	Node *temp = _node;
	
	if(_node)
	{
		temp = InOrder(_node->m_left,_action,_context);
		
		if(!temp && !_action(_node->m_data,_context))
		{
			return _node;
		}
		
		if(!temp)
		{
			temp = InOrder(_node->m_right,_action,_context);
		}
	}
	
	return (temp) ? temp : NULL;
}

static BSTreeItr PostOrder(Node *_node, ActionFunction _action, void* _context)
{
	Node *temp = _node;
	
	if(_node)
	{
		temp = PostOrder(_node->m_left,_action,_context);
	
		if(!temp)
		{
			temp = PostOrder(_node->m_right,_action,_context);
		}
		
		if(!temp && !(_action(_node->m_data,_context)))
		{
			return _node;
		}
	}
	
	return (temp) ? temp : NULL;
}


