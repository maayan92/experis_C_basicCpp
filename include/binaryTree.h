#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "ADTErrors.h"

typedef enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
} TreeTraverse;

enum
{	
	false,
	true
};

typedef struct Tree Tree;

/*
	Description: create new tree.
	Input: no inputs.
	Return value: return a pointer to the new tree, or NULL if there is an overflow.
*/
Tree* TreeCreate();

/*
	Description: destroy the tree.
	Input:	_tree - pointer to the tree.
	Return value: nothing return.
*/
void TreeDestroy(Tree* _tree);

/*
	Description: insert new data to the tree.
	Input: _tree - pointer to the tree, _data - the new data to insert the tree.
	Return value: return error code, ERR_NOT_INITIALIZE - if the tree is NULL, ERR_ILLEGAL_INPUT - if the new data is already in the tree,
					ERR_OVERFLOW - if there is an overflow, SUCCEEDED - on success.
*/
ErrCode TreeInsert(Tree* _tree, int _data);

/*
	Description: check if a data is in the tree.
	Input: _tree - pointer to the tree, _data - the data to check if it's exist in the tree.
	Return value: return true - if the data is in the tree, false - if the data doesn't exist in the tree or if the tree is NULL.
*/
int TreeIsDataFound(Tree* _tree, int _data);

/*
	Description: print the tree in three ways.
	Input: _tree - pointer to the tree, _traverseMode - the mode that says how to print the tree.
	Return value: return error code, ERR_NOT_INITIALIZE - if the tree is NULL, SUCCEEDED - on success.
*/
ErrCode TreePrint(Tree* _tree, TreeTraverse _traverseMode);

int IsFullTree(Tree *_tree);

int TreeLevel(Tree *_tree);

int AreSimilar(Tree *_tree1, Tree *_tree2);

int IsPerfectTree(Tree *_tree);

#endif
