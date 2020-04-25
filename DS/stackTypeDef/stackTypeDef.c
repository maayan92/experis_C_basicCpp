#include <stdio.h>
#include <stdlib.h>
#include "dynamicVector.h"
#include "stack.h"

Stack* StackCreate(size_t _initialSize, size_t _blockSize)
{

	return  (Stack *)VectorCreate(_initialSize,_blockSize);
}

void StackDestroy(Stack* _stack)
{

	VectorDestroy((Vector *)_stack);

}

ErrCode StackPush(Stack* _stack, int data)	
{

	return  VectorAddTail((Vector *)_stack,data);

}

ErrCode StackPop(Stack* _stack, int* _data)
{

	return VectorRemoveTail((Vector *)_stack,_data);

}

size_t StackNumOfelements(Stack* _stack)
{

	return VectorNumOfelements((Vector *)_stack);

}

int StackIsEmpty(Stack* _stack)
{

	return !VectorNumOfelements((Vector *)_stack);

}	 

ErrCode PrintStack(Stack* _stack)
{

	return PrintArray((Vector *)_stack);

}




