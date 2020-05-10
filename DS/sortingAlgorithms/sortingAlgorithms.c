#include <stdio.h>
#include "sortingAlgorithms.h"
#include "stack.h"

/*swap if needed*/
static int Swap(Vector *_vec, int data1, int data2, int _i, int _j);
/*get the values and swap if needed*/
static int GetAndSwap(Vector *_vec, int _i, int _j);
/*move value to the right or to the left*/
static int ShakeToLOrToR(Vector *_vec, int *_j, int _i, int _fromStart);
/*move bigger values of _pivot to the last and smaller values of _pivot to the right*/
static int Partition(Vector *_vec, int _pivot, size_t _begin, size_t _end);
/*quick sort in the recurtion way*/
static void QuickRec(Vector* _vec, size_t _begin, size_t _end);
/*push values to the stack*/
static void PushToStack(Stack *_stack, int _begin, int _end, int _pivotIndex);
/*sort the vector with the stack help*/
static void SortWithStack(Stack *_stack, Vector* _vec, int _begin, int _end);
/*quick sort int the iterative way*/
static ErrCode QuickIter(Vector* _vec, int _begin, int _end);
/*move the value of index _i to its right position*/
static void MoveToPosition(Vector *_vec,int _j, int _gap);
/*sort the vector by gaps*/
static void SortByGap(Vector* _vec, int _gap);


ErrCode BubbleSort(Vector *_vec)
{
	int i, j, swapped = 1;

	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZE;
	}

	for(i = 1;i < VectorNumOfelements(_vec) && swapped;++i)
	{
		swapped = 0;

		for(j = 1;j <= VectorNumOfelements(_vec)-i;++j)
		{
			if(GetAndSwap(_vec,j,j+1))
			{
				swapped = 1;
			}
		}
	}

	return SUCCEEDED;
} 

ErrCode ShakeSort(Vector *_vec)
{
	int i, j, swapped = 1;

	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZE;
	}

	for(i = 1;i <= VectorNumOfelements(_vec) && swapped;++i)
	{
		j = i;

		if(ShakeToLOrToR(_vec,&j,i,1))
		{
			swapped = 1;
		}

		--j;
		if(ShakeToLOrToR(_vec,&j,i,0))
		{
			swapped = 1;
		}
	}

	return SUCCEEDED;
}


ErrCode QuickSortIter(Vector* _vec)
{
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZE;
	}

	if(1 >= VectorNumOfelements(_vec))
	{
		return SUCCEEDED;
	}

	return QuickIter(_vec,1,VectorNumOfelements(_vec));
}

ErrCode QuickSortRec(Vector *_vec)
{
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZE;
	}

	QuickRec(_vec,1,VectorNumOfelements(_vec));
	
	return SUCCEEDED;
}

ErrCode InsertionSort(Vector* _vec)
{
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZE;
	}

	SortByGap(_vec,1);

	return SUCCEEDED;
}

ErrCode ShellSort(Vector* _vec)
{
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZE;
	}

	SortByGap(_vec,VectorNumOfelements(_vec)/2);

	return SUCCEEDED;
}

/* SUB FUNCTIONS */

static int Swap(Vector *_vec, int data1, int data2, int _i, int _j)
{
	if(data1 > data2)
	{
		VectorSet(_vec,_i,data2);
		VectorSet(_vec,_j,data1);		
		return 1;
	}

	return 0;
}

static int GetAndSwap(Vector *_vec, int _i, int _j)
{
	int data1, data2;

	VectorGet(_vec,_i,&data1);
	VectorGet(_vec,_j,&data2);

	return Swap(_vec,data1,data2,_i,_j);
}

static int ShakeToLOrToR(Vector *_vec, int *_j, int _i, int _fromStart)
{
	int swapped = 0;

	while((*_j) >= _i && (*_j) <= VectorNumOfelements(_vec)-_i)
	{
		if(GetAndSwap(_vec,(*_j),(*_j)+1))
		{
			swapped = 1;
		}

		(_fromStart) ? ++(*_j) : --(*_j);
	}

	return swapped;
}

static int Partition(Vector *_vec, int _pivot, size_t _begin, size_t _end)
{
	int dataS, dataB, pivotIndex = _begin-1;

	while(_begin < _end)
	{
		VectorGet(_vec,_begin,&dataS);
		VectorGet(_vec,_end,&dataB);

		while(dataS <= _pivot && _begin < _end)
		{
			++_begin;
			VectorGet(_vec,_begin,&dataS);
		}
	
		while(dataB > _pivot && _begin <= _end)
		{
			--_end;
			VectorGet(_vec,_end,&dataB);
		}

		if(_begin < _end)
		{
			Swap(_vec,dataS,dataB,_begin,_end);
		}
	}

	VectorGet(_vec,_end,&dataB);
	Swap(_vec,_pivot,dataB,pivotIndex,_end);

	return _end;
}

static void QuickRec(Vector* _vec, size_t _begin, size_t _end)
{
	int pivot, pivotIndex;

	if(_begin >= _end)
	{
		return;
	}

	VectorGet(_vec,_begin,&pivot);

	pivotIndex = Partition(_vec,pivot,_begin+1,_end);

	QuickRec(_vec,_begin,pivotIndex-1);
	QuickRec(_vec,pivotIndex+1,_end);
}


static void PushToStack(Stack *_stack, int _begin, int _end, int _pivotIndex)
{
	if(_begin < _pivotIndex)
	{
		StackPush(_stack,_begin);
		StackPush(_stack,_pivotIndex-1);
	}
	if(_end > _pivotIndex)
	{
		StackPush(_stack,_pivotIndex+1);
		StackPush(_stack,_end);
	}	
}

static void SortWithStack(Stack *_stack, Vector* _vec, int _begin, int _end)
{
	int pivot, pivotIndex;

	VectorGet(_vec,_begin,&pivot);
	pivotIndex = Partition(_vec,pivot,_begin+1,_end);

	PushToStack(_stack,_begin,_end,pivotIndex);

	while(!StackIsEmpty(_stack))
	{
		StackPop(_stack,&_end);
		StackPop(_stack,&_begin);

		VectorGet(_vec,_begin,&pivot);
		pivotIndex = Partition(_vec,pivot,_begin+1,_end);

		PushToStack(_stack,_begin,_end,pivotIndex);
	}
}

static ErrCode QuickIter(Vector* _vec, int _begin, int _end)
{
	Stack *stack;

	stack = StackCreate(VectorNumOfelements(_vec),0);
	if(NULL == stack)
	{
		return ERR_ALLOCATION_FAILED;
	}

	SortWithStack(stack,_vec,_begin,_end);

	StackDestroy(stack);
	return SUCCEEDED;
}

static void MoveToPosition(Vector *_vec,int _j, int _gap)
{

	while(_j > 0 && (_j-_gap) > 0 && GetAndSwap(_vec,_j-_gap,_j))
	{
		_j -= _gap;
	}

}

static void SortByGap(Vector* _vec, int _gap)
{
	int i;

	while(_gap)
	{
		for(i = 1;i < VectorNumOfelements(_vec);++i)
		{
			MoveToPosition(_vec,i+_gap,_gap);
		}

		_gap /= 2;
	}
}









