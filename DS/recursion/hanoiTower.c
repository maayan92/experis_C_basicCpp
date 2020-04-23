#include <stdio.h>
#include "stack.h"

/*
	Description: fill the stack with values from 1 to _numOfDisks,
	Input:	_from - stack pointer the fun fills , _numOfDisks - amount and values that would be insert.
	Return value: nothing returns.

*/
static void FillStack(Stack *_from, size_t _numOfDisks)
{
	while(_numOfDisks)
	{
		StackPush(_from,_numOfDisks--);
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

static void PrintAllstack(Stack *_from, Stack *_to, Stack *_via)
{
	printf("stack from: \n");
	PrintStack(_from);
	printf("\nstack to: \n");
	PrintStack(_to);
	printf("\nstack via: \n");
	PrintStack(_via);
}

int main()
{
	size_t numOfDisks;
	Stack *from, *to, *via;

	printf("please enter a number of disks: ");
	scanf("%lu",&numOfDisks);

	from = StackCreate(numOfDisks,0);
	to = StackCreate(numOfDisks,0);
	via = StackCreate(numOfDisks,0);
	
	if(NULL == from || NULL == to || NULL == via)
	{
		StackDestroy(from);
		StackDestroy(to);
		StackDestroy(via);
		printf("error \n");
		return 0;
	}

	FillStack(from,numOfDisks);

	printf("\n----before the hanoi tower game----s\n");
	PrintAllstack(from,to,via);
	
	MoveDisksR(numOfDisks,from,to,via);

	printf("----after the hanoi tower game----\n\n");
	PrintAllstack(from,to,via);
	

	return 0;
}
