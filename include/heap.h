#ifndef __HEAP_MAX_H_
#define __HEAP_MAX_H_

#include "vector.h"
#include "ADTErrors.h"

typedef struct Heap Heap;

/*comparison function for two elements, return true if _a > _b else false*/
typedef int (*PtrCompare)(const void* _a,const void* _b);

/*
	Description: builed the heap.
	Input: _vec - dynamic pointer to vector, 
	Return value: return a pointer to the heap, or NULL if the allocation failed or if _vec is NULL.
*/
Heap* HeapBuild(Vector* _vec, PtrCompare _compareFun);

/*
	Description: destroy the heap, not destroying the vector, heap sould be reset to NULL after calling this function.
	Input: _heap - pointer to the heap.
	Return value: return pointer to the vector, or NULL if the heap doesn't exist.
*/
Vector* HeapDestroy(Heap** _heap);

/*
	Description: insert new data to the heap.
	Input: _heap - pointer to the heap, _data - the new data.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _heap is not exist, ERR_OVERFLOW - if there is a memory overflow,
					 SUCCEEDED - on success.
*/
ErrCode HeapInsert(Heap* _heap, void* _data);

/*
	Description: give the heap max value.
	Input: _heap - pointer to the heap, _data - pointer to the max value.
	Return value: return the top element of the heap, or NULL if the heap isn't exist or if the heap is empty.
*/
const void* HeapTop(const Heap* _heap);

/*
	Description: remove the top value from the heap.
	Input: _heap - pointer to the heap, _data - pointer to the removed data.
	Return value: return the top element of the heap, or NULL if the heap isn't exist or if the heap is empty.
*/
void* HeapExtract(Heap* _heap);

/*
	Description: get the number of items it the heap.
	Input: _heap - pointer to the heap.
	Return value: return the number of items, 0 if there is no items or if the heap doesn't exist.
*/
size_t HeapItemsNum(const Heap* _heap);

/*
	Description: print the heap.
	Input: _heap - pointer to the heap.
	Return value: 
*/
/*HeapPrint for dibbug only*/
void HeapPrint(const Heap* _heap, void(*prtPrintElement)(void*));

/*
	Description: Iterate over all elements in the heap from top to bottom, the user provided _act will be called for each element. 
	Input: _heap - pointer to the heap, _act - the action function, _context - the context of the action performed on the variables.
	Return value: return the number of time the action was called, 0 if the heap doesn't exist.
*/
size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context);





#endif
