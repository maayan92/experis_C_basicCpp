#ifndef _DLLIST_H
#define _DLLIST_H

#include "ADTErrors.h"

typedef struct DoubleLinkedList List;

/*pointer to a function that do action on an element, input - the data*/
typedef void(*ptrElementFun)(void*);

enum{ false, true };

/*
	Description: create a new double linked list.
	Input: no input.
	Return value: return a pointer to the new list, or NULL if the allocation failed.
*/
List* DLListCreate();

/*
	Description: destroying the double linked list, after calling this function the list pointer should be reset with NULL.
	Input: _list - pointer to the list, 
		_destroyElement - pointer to a function that destroy the elements, should be NULL If no dynamic memory is assigned to the data.
	Return value: nothing returns.

*/
void DLListDestroy(List* _list, ptrElementFun _destroyElement);

/*
	Description: insert new data to the head of the list.
	Input: _list - pointer to the list, _data - void pointer to the new data that would insert to the list.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _list is NULL, ERR_ALLOCATION_FAILED - if the allocation failed,
					ERR_ILLEGAL_INPUT - if _data is NULL, SUCCEEDED - on success.
*/
ErrCode DLListPushHead(List* _list, void* _data);

/*
	Description: insert new data to the tail of the list.
	Input: _list - pointer to the list, _data - void pointer to the new data that would insert to the list.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _list is NULL, ERR_ALLOCATION_FAILED - if the allocation failed,
					ERR_ILLEGAL_INPUT - if _data is NULL, SUCCEEDED - on success.
*/
ErrCode DLListPushTail(List* _list, void* _data);

/*
	Description: remove data from the head of the list.
	Input: _list - pointer to the list, _data - a pointer to the head data that would remove, NULL if the _list is NULL. 
	Return value: return error code, ERR_NOT_INITIALIZE - if the _list is NULL, ERR_UNDERFLOW - if the list is empty,
					ERR_ILLEGAL_INPUT - if _data is NULL, SUCCEEDED - on success.
*/
ErrCode DLListPopHead(List* _list, void**_data);

/*
	Description: remove data from the tail of the list.
	Input: _list - pointer to the list, _data - a pointer to the tail data that would remove, NULL if the _list is NULL.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _list is NULL, ERR_UNDERFLOW - if the list is empty,
					ERR_ILLEGAL_INPUT - if _data is NULL, SUCCEEDED - on success.
*/
ErrCode DLListPopTail(List* _list, void**_data);

/*
	Description: count the number of data in the list, O(n).
	Input: _list - pointer to the list.
	Return value: return the number of data in the list, 0 if there is no data or if the _list is NULL.
*/
size_t DLListCountItems(const List* _list);

/*
	Description: check if the list if empty.
	Input: _list - pointer to the list.
	Return value: return true if the list is empty, false if the list is not empty or if the _list is NULL.
*/
int DLListIsEmpty(const List* _list);

/*
	Description: print the data from the list
	Input: _list - pointer to the list. 
	Return value: nothing returns.
*/
/* DLListPrint is only for debug */
void DLListPrint(const List *_list, ptrElementFun _printElement);


#endif
