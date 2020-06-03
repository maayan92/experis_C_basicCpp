#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "ADTErrors.h"

/*
	Description: Compare two iterators.
	Input: _a - element to compare, _b - element to compare against
	Return value: return none zero if _a == _b.
*/
#define TREE_ITR_EQUALS(_a,_b) (_a == _b)

typedef struct Tree Tree;
typedef void*  BSTreeItr;


/*
	Description: Action function to check if a < b
	Input: _a - element to test, _b - element to test against
	Return value: return none zero if _a < _b.
*/
typedef int (*LessComparator)(void* _left, void* _right);

/*
	Description: Predicate function returns a none zero value if predicate holds for element.
	Input: _element - element to test, _context - context to be used.
	Return value: return none zero if predicate holds.
*/
typedef int (*PredicateFunction)(void * _element, void* _context);

/*
	Description: Action function to operate on an element
	Input: _element - element to test, _context - context to be used.
	Return value: return zero if action fails.
*/
typedef int (*ActionFunction)(void* _element, void* _context);


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

/*
	Description: create new tree.
	Input: _less - A comparison function.
	Return value: return a pointer to the new tree, NULL if the allocation fails or if the function pointer is NULL.
*/
Tree* TreeCreate(LessComparator _less);

/*
	Description: destroy the tree, If supplied with non-NULL destroyer function, frees items in tree.
	Input:	_tree - pointer to the tree, destroyer - A function to destroy the data in the tree (may be NULL if unnecessary).
	Return value: nothing return.
*/
void TreeDestroy(Tree* _tree, void(*_destroyer)(void*));

/*
	Description: insert new data to the tree, if it's not exist already.
	Input: _tree - pointer to the tree, _data - the new data to insert the tree.
	Return value: return iterator pointing to the item added, or iterator to end on failure, or NULL if the tree doesn't exist.
*/
BSTreeItr TreeInsert(Tree* _tree, void* _data);

/**TODO 
 * @brief Search the first element for which the given predicate returns 0
 * iterating using in-order manner over elements
 * O(k * n) where O(k) is the time complexity of the predicate
 *
 * @param _tree : A previously created Tree ADT returned via BSTreeCreate
 * @param _predicate : Predicate function
 * @param _params : Predicate parameters
 * @return an iterator pointing to the first data found, to end of tree if not found or NULL on NULL input
 */
 
 /*
	Description: 
	Input: 
	Return value: 
*/
BSTreeItr BSTreeFindFirst(const Tree* _tree, PredicateFunction _predicate, void* _context);/*TODO*/
/*TODO*/

/*
	Description: Get an in-order itertator to the tree's begin.
	Input: _tree - pointer to the tree.
	Return value: return an iterator pointing at the tree's begin, pointer to the root sentinel if the tree is empty or NULL if tree is empty or not exist.
*/
BSTreeItr BSTreeItrBegin(const Tree* _tree);

/*
	Description: Get itertator to the tree's end (in order).
	Input: _tree - pointer to the tree.
	Return value: return an iterator pointing at the tree's end (pointer to the root sentinel) or NULL if the list dosen't exist.
*/
BSTreeItr BSTreeItrEnd(const Tree* _tree);

/*
	Description: Get itertator to the next element from current iterator.
	Input: _itr - A tree iterator. (should be valid and not NULL)
	Return value: returns an iterator pointing at the next element after _itr, 
			or end iterator (pointer to the root sentinel) if the tree is empty or if there is no next.
*/
BSTreeItr BSTreeItrNext(BSTreeItr _itr);

/*
	Description: Get itertator to the previous element from current iterator.
	Input: _itr - A tree iterator. (should be valid and not NULL)
	Return value: return an iterator pointing at the previous element after _itr, 
			or end iterator (pointer to the root sentinel) if the tree is empty or if there is no prev.
*/
BSTreeItr BSTreeItrPrev(BSTreeItr _itr);


/** 
 * @brief Removes element from tree
 * @details Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(1).
 *
 * @param _it : A tree iterator
 * @return removed item or null on failure
 */
 
/*
	Description: Removes element from tree, and rearranges the tree so that it maintains binary search tree arrangement. O(1)
	Input: _itr - A tree iterator. (should be valid and not NULL)
	Return value: return removed data or null on failure.
*/
void* BSTreeItrRemove(BSTreeItr _itr);/*TODO*/

/*
	Description: Get data pointed to by iterator from tree.
	Input: _itr - A tree iterator. (should be valid and not NULL)
	Return value: return the data the iterator points at.
*/
void* BSTreeItrGet(BSTreeItr _itr);/*TODO*/

 /*
	Description: Performs an action function on every element in tree, by given traversal mode.
	Input: _tree - pointer to the tree, _mode - Traversal mode -> PRE_ORDER, IN_ORDER, POST_ORDER,
		 _action - Action function to call for each element, _context - Parameters for the function.
	Return value: return NULL or an iterator to the specific element where action returned none zero value.
*/
BSTreeItr BSTreeForEach(const Tree* _tree, TreeTraverse _mode, ActionFunction _action, void* _context);/*TODO*/


#endif
