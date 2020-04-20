#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "../dynamicVector/dynamicVector.h"

typedef struct Stack Stack;

enum
{
	false,
	true
};

/*
	Description: create dynamic stack.
	Input: _initialSize - initial size of the stack, _blockSize - block size to increase the stack when it's full, both should to be positive.
	Return value: return pointer to allocated stack, or NULL in case it fails, if the input is illegal or there is an overflow.
*/
Stack* StackCreate(size_t _initialSize, size_t _blockSize);


/*
	Description: destroy the stack, after calling this function the stack pointer should be reset with NULL.
	Input: _stack - dynamic stack pointer.
	Return value: nothing returns.
*/
void StackDestroy(Stack* _stack);

/*
	Description: add new data to the end of the vector array, resize (increases the size) the vector array in case that it's full.
	Input: _stack - dynamic stack pointer, _data - the new data that would be inserted to the end stack.
	Return value: return error code, ERR_NOT_EXIST - if the _stack is NULL, ERR_OVERFLOW - if the resize fails because there is a memory overflow,
					SUCCEEDED - on success.
*/
ErrCode  StackPush(Stack* _stack, int data);

/*
	Description: remove the last data from the vector array, resize (reduces the size) the vector array in case there is too much empty space.
	Input: _stack - dynamic stack pointer, _data - the data that would be removed from the end of the stack.
	Return value: return error code, ERR_NOT_EXIST - if the _stack is NULL or if the stack is empty, ERR_FAILED - if the realloc fails,
					SUCCEEDED - on success.
*/
ErrCode StackPop(Stack* _stack, int* _data);

/*
	Description: gives the number of elements in the stack.
	Input: _stack - dynamic stack pointer.
	Return value: return the number of elements or 0 if the stack is empty or if the _stack is NULL.
*/
size_t StackNumOfelements(Stack* _stack);

/*
	Description: check if the stack is empty.
	Input: _stack - dynamic stack pointer.
	Return value: return true if the stack is empty or if the _stack is NULL, false if the stack is not empty.
*/
int StackIsEmpty(Stack* _stack);

/*
	Description: print the stack.
	Input: _stack - dynamic stack pointer.
	Return value: return error code, ERR_NOT_EXIST - if the _stack is NULL, SUCCEEDED - on success.
*/
ErrCode PrintStack(Stack* _stack);


#endif
