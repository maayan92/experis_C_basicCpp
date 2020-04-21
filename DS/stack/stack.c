#include <stdio.h>
#include <stdlib.h>
#include "dynamicVector.h"
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

		free(_stack);
	}
}

ErrCode StackPush(Stack* _stack, int data)
{
	if(NULL == _stack)
	{
		return ERR_NOT_INITIALIZE;
	}

	return  VectorAddTail(_stack->m_vec,data);

}

ErrCode StackPop(Stack* _stack, int* _data)
{
	if(NULL == _stack)
	{
		return ERR_NOT_INITIALIZE;
	}

	return VectorRemoveTail(_stack->m_vec,_data);

}

ErrCode StackTop(Stack* _stack, int* _data)
{
	if(NULL == _stack)
	{
		return ERR_NOT_INITIALIZE;
	}

	return VectorGet(_stack->m_vec,StackNumOfelements(_stack),_data);

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

	return !VectorNumOfelements(_stack->m_vec);
}	 

ErrCode PrintStack(Stack* _stack)
{
	if(NULL == _stack)
	{
		return ERR_NOT_INITIALIZE;
	}

	return PrintArray(_stack->m_vec);
}










