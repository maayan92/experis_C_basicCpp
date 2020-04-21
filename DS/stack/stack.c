#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


struct Stack
{
	Vector *m_vec;
};


Stack* StackCreate(size_t _initialSize, size_t _blockSize)
{

	Stack *stack;

	stack = (Stack*)malloc(sizeof(Stack));

	if(NULL == stack)
	{
		return NULL;
	}
	
	stack->m_vec = VectorCreate(_initialSize,_blockSize);

	if(NULL == stack->m_vec)
	{
		free(stack);
		stack = NULL;
	}

	return stack;
}

void StackDestroy(Stack* _stack)
{
	if(NULL != _stack)
	{
		VectorDestroy(_stack->m_vec);
	
		_stack->m_vec = NULL;

		free(_stack);
	}
}

ErrCode StackPush(Stack* _stack, int data)
{
	if(NULL == _stack)
	{
		return ERR_NOT_EXIST;
	}

	return  VectorAddTail(_stack->m_vec,data);

}

ErrCode StackPop(Stack* _stack, int* _data)
{
	if(NULL == _stack)
	{
		return ERR_NOT_EXIST;
	}

	return VectorRemoveTail(_stack->m_vec,_data);

}

size_t StackNumOfelements(Stack* _stack)
{
	if(NULL == _stack)
	{
		return 0;
	}

	return VectorNumOfelements(_stack->m_vec);

}

int StackIsEmpty(Stack* _stack)
{
	if(NULL == _stack)
	{
		return 0;
	}

	return VectorNumOfelements(_stack->m_vec) ? false : true;
}

ErrCode PrintStack(Stack* _stack)
{
	if(NULL == _stack)
	{
		return ERR_NOT_EXIST;
	}

	return PrintArray(_stack->m_vec);
}









