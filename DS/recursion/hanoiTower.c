#include <stdio.h>
#include "stack.h"

/*
	Description: create 3 stacks and fill the first stack with values from 1 to _numOfDisks,
	Input:	_from - stack pointer the fun fills , _numOfDisks - amount and values that would be insert.
	Return value: nothing returns.

*/
static void CreateAndFillStack(Stack **_stack, size_t _numOfDisks)
{
	_stack[0] = StackCreate(_numOfDisks,0);
	_stack[1] = StackCreate(_numOfDisks,0);
	_stack[2] = StackCreate(_numOfDisks,0);
	
	if(NULL == _stack[0] || NULL == _stack[1] || NULL == _stack[2])
	{
		StackDestroy(_stack[0]);
		StackDestroy(_stack[1]);
		StackDestroy(_stack[2]);
		printf("error \n");
		return;
	}

	while(_numOfDisks)
	{
		StackPush(_stack[0],_numOfDisks--);
	}
}

/*
	Description: moves all disks(data) from the _from stack to the _to stack, by hanoi game rools.
	Input: _numOfDisks - number of disks to move, _from - the stack with the disks, _to - the stack that should get the disks,
		_via - helper stack.
	Return value: nothing returns.
*/

static void MoveDisksR(size_t _numOfDisks, Stack *_from, Stack *_to, Stack *_via)
{
	int data1, data2;

	if(1 == _numOfDisks)
	{
		if(SUCCEEDED == StackTop(_from,&data1) && SUCCEEDED == StackTop(_to,&data2))
		{
			if(data1 > data2)
			{
				return;
			}
		}
	
		StackPop(_from,&data1);
		StackPush(_to,data1);

		return;
	}

	MoveDisksR(_numOfDisks-1,_from,_via,_to);
	MoveDisksR(1,_from,_to,_via);
	MoveDisksR(_numOfDisks-1,_via,_to,_from);
}

static void PrintAllstack(Stack **_stack)
{
	printf("stack from: \n");
	PrintStack(_stack[0]);
	printf("\nstack to: \n");
	PrintStack(_stack[1]);
	printf("\nstack via: \n");
	PrintStack(_stack[2]);
}

int main()
{
	size_t numOfDisks;
	Stack *stack[3];

	printf("please enter a number of disks: ");
	scanf("%lu",&numOfDisks);

	CreateAndFillStack(stack,numOfDisks);

	printf("\n----before the hanoi tower game----s\n");
	PrintAllstack(stack);
	
	MoveDisksR(numOfDisks,stack[0],stack[1],stack[2]);

	printf("----after the hanoi tower game----\n\n");
	PrintAllstack(stack);
	

	return 0;
}
