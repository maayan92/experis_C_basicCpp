#ifndef __HEAP_MAX_H_
#define __HEAP_MAX_H_

#include "dynamicVector.h"
#include "ADTErrors.h"

typedef struct Heap Heap;

/*
	Description: builed the heap.
	Input: _vec - dynamic pointer to vector, 
	Return value: return a pointer to the heap, or NULL if the allocation failed or if _vec is NULL.
*/
Heap* HeapBuild(Vector* _vec);

/*
	Description: destroy the heap, not destroying the vector, heap sould be reset to NULL after calling this function.
	Input: _heap - pointer to the heap.
	Return value: nothing returns.
*/
void HeapDestroy(Heap* _heap);

/*
	Description: insert new data to the heap.
	Input: _heap - pointer to the heap, _data - the new data.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _heap is not exist, ERR_OVERFLOW - if there is a memory overflow,
					 SUCCEEDED - on success.
*/
ErrCode HeapInsert(Heap* _heap, int _data);

/*
	Description: give the heap max value.
	Input: _heap - pointer to the heap, _data - pointer to the max value.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _heap is not exist, ERR_ILLEGAL_INPUT - if _data pointer is NULL, 
					ERR_EMPTY - if the heap if empty, SUCCEEDED - on success.
*/
ErrCode HeapMax(Heap* _heap, int* _data);

/*
	Description: remove the max value from the heap.
	Input: _heap - pointer to the heap, _data - pointer to the removed data.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _heap is not exist, ERR_ILLEGAL_INPUT - if _data pointer is NULL,
					ERR_EMPTY - if the heap if empty, SUCCEEDED - on success.
*/
ErrCode HeapExtractMax(Heap* _heap, int* _data);

/*
	Description: get the number of items it the heap.
	Input: _heap - pointer to the heap.
	Return value: return the number of items, 0 if there is no items or if the heap doesn't exist.
*/
int HeapItemsNum(Heap* _heap);

/*
	Description: print the heap.
	Input: _heap - pointer to the heap.
	Return value: 
*/
/*HeapPrint for dibbug only*/
void HeapPrint(Heap* _heap);



#endif
