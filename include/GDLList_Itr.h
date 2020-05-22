#ifndef __GDLLIST_ITR_H_
#define __GDLLIST_ITR_H_

#include "GDLList.h"

typedef void* ListItr;


/*
	Description: Get itertator to the list's beginning.
	Input: _list - pointer to the list, pointing at first element or at the end if list is empty.
	Return value: return iterator pointing at the list's beginning, or NULL if the list dosen't exist.
*/
ListItr ListItrBegin(const List* _list);

/*
	Description: Get itertator to the list end.
	Input: _list - pointer to the list.
	Return value: return an iterator pointing at the list's end, or NULL if the list dosen't exist.
*/
ListItr ListItrEnd(const List* _list);

/*
	Description: check if iterator _a and iterator _b are equal. 
	Input: _a - a list iterator, _b - a list iterator.
	Return value: retruns none zero if _a and _b iterators refer to same node.
*/
int ListItrEquals(const ListItr _a, const ListItr _b);

/*
	Description: Get itertator to the next element from a given iterator.
	Input: _itr - a list iterator.
	Return value: return the next iterator, or if the iterator is the end iterator it will be return.
*/
ListItr ListItrNext(ListItr _itr);

/*
	Description: Get itertator to the previous element.
	Input: _itr - a list iterator.
	Return value: return the previous iterator, or if _itr is begin iterator it will be returned.
*/
ListItr ListItrPrev(ListItr _itr);

/*
	Description: Get data from the list node the iterator is pointing to.
	Input: _itr - a list iterator.
	Return value: return the data the iterator is pointing at or NULL if pointing to the end.
*/
void* ListItrGet(ListItr _itr);

/*
	Description: Set data at the node where the iterator is pointing at.
	Input: _itr - a list iterator, _element - the data that would be set.
	Return value: return the data from the node to be changed.
*/
void* ListItrSet(ListItr _itr, void* _element);

/*
	Description: Inserts a new node before node the iterator is pointing at.
	Input: _itr - a list iterator, _element - the new data.
	Return value: return an iterator pointing at the element inserted or NULL on error.
*/
ListItr ListItrInsertBefore(ListItr _itr, void* _element);

/*
	Description: Removes the node the iterator is pointing at
	Input: _itr - a list iterator.
	Return value: return the removed data.
*/
void* ListItrRemove(ListItr _itr);



#endif

