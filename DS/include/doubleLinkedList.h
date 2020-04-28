#ifndef _DLLIST_H
#define _DLLIST_H

#include <stdio.h>
#include "ADTErrors.h"

typedef struct DoubleLinkedList List;

enum{ false, true };

/*
	Description: create a new double linked list.
	Input: no input.
	Return value: return a pointer to the new list, or NULL if the allocation failed.
*/
List* DLListCreate();

/*
	Description: destroying the double linked list, after calling this function the list pointer should be reset with NULL.
	Input: _head - the head pointer of the list.
	Return value: nothing returns.

*/
void DLListDestroy(List* _list);

/*
	Description: insert new data to the head of the list.
	Input: _list - pointer to the list, _data - new data that would insert to the list.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _list is NULL, ERR_OVERFLOW - if the memory is overflow, SUCCEEDED - on success.
*/
ErrCode DLListPushHead(List* _list, int _data);

/*
	Description: insert new data to the tail of the list.
	Input: _list - pointer to the list, _data - new data that would insert to the list.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _list is NULL, ERR_OVERFLOW - if the memory is overflow, SUCCEEDED - on success.
*/
ErrCode DLListPushTail(List* _list, int _data);

/*
	Description: remove data from the head of the list.
	Input: _list - pointer to the list, _data - a pointer to the head data that would remove, NULL if the _list is NULL. 
	Return value: return error code, ERR_NOT_INITIALIZE - if the _list is NULL, ERR_UNDERFLOW - if the list is empty, SUCCEEDED - on success.
*/
ErrCode DLListPopHead(List* _list, int *_data);

/*
	Description: remove data from the tail of the list.
	Input: _list - pointer to the list, _data - a pointer to the tail data that would remove, NULL if the _list is NULL. 
	Return value: return error code, ERR_NOT_INITIALIZE - if the _list is NULL, ERR_UNDERFLOW - if the list is empty, SUCCEEDED - on success.
*/
ErrCode DLListPopTail(List* _list, int *_data);

/*
	Description: count the number of data in the list.
	Input: _list - pointer to the list. 
	Return value: return the number of data in the list, 0 if there is no data or if the _list is NULL.
*/
size_t DLListCountItems(List* _list);

/*
	Description: check if the list if empty.
	Input: _list - pointer to the list. 
	Return value: return true if the list is empty or false if the list is not empty or if the _list is NULL.
*/
int DLListIsEmpty(List* _list);

/*
	Description: print the data from the list
	Input: _list - pointer to the list. 
	Return value: nothing returns.
*/
/* DLListPrint is only for debug */
void DLListPrint(List *_list);


#endif
