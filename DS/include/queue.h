#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include "ADTErrors.h"

typedef struct CyclicQueue CyclicQueue;


/*
	Description: create a queue.
	Input: _initialSize - initial size of the queue, should to be positive.
	Return value: return pointer to the queue, or NULL in case it fails, if the input is illegal or there is an overflow.
*/
CyclicQueue * QueueCreate(size_t _initialSize);

/*
	Description: destroy the queue, after calling this function the queue pointer should be reset with NULL.
	Input: _que - queue pointer.
	Return value: nothing returns.
*/
void QueueDestroy(CyclicQueue *_que);

/*
	Description: add new data to the queue.
	Input: _que - queue pointer, _data - the new data that would be inserted to the queue.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _que is NULL, ERR_OVERFLOW - if the queue is full, SUCCEEDED - on success.
*/
ErrCode QueueEnQueue(CyclicQueue *_que, int _data);

/*
	Description: remove data from a the queue.
	Input: _que -queue pointer, _data - pointer to the data that would be removed.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _que is NULL, ERR_UNDERFLOW - if the queue is empty, SUCCEEDED - on success.
*/
ErrCode QueueDeQueue(CyclicQueue *_que, int *_data);

/*
	Description: check if the queue if empty.
	Input: _que - queue pointer.
	Return value: return true is the queue is empty or if the _que if NULL, and false if the queue is not empty.
*/
int QueueIsEmpty(CyclicQueue *_que);

/*
	Description: give the number of elements in the queue.
	Input: _que - queue pointer.
	Return value: return the number of elements in the queue, or NULL if the _que is NULL.
*/
size_t QueueNumOfElements(CyclicQueue *_que);

#endif
