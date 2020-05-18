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
					ERR_ALLOCATION_FAILED - if there is an overflow, SUCCEEDED - on success.
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

/*
	Description: check if the tree is a full.
	Input: _tree - pointer to the tree.
	Return value: return true is the tree is full, false if the tree is not full or if the tree is not exist.
*/
int IsFullTree(Tree *_tree);

/*
	Description: get the level of the tree.
	Input: _tree - pointer to the tree.
	Return value: return the number of levels in the tree, or -1 if the tree is not exist.
*/
int TreeLevel(Tree *_tree);

/*
	Description: check if the trees are similar in the levels.
	Input: _tree1 - pointer to the first tree, _tree2 - pointer to the second tree.
	Return value: return true is the trees are similar, false if the trees are not similar or if at least one of the trees are not exist.
*/
int AreSimilar(Tree *_tree1, Tree *_tree2);

/*
	Description: check if the tree is perfect.
	Input: _tree - pointer to the first tree.
	Return value: return true is the tree is perfect, false if the tree is not perfect or if the tree is not exist.
*/
int IsPerfectTree(Tree *_tree);

/*
	Description: change the tree to its mirror tree.
	Input: _tree - pointer to the first tree.
	Return value: return error code, ERR_NOT_INITIALIZE - if the tree is NULL, SUCCEEDED - on success.
*/
ErrCode MirrorTree(Tree *_tree);


#endif
