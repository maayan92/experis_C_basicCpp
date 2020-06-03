#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define HEAP_MAGIC_NUMBER 0xbeefbee0

#define PARENT(i) (i/2)
#define LEFT(i) (2*i)
#define RIGHT(i) (2*i + 1)

#define IS_NOT_EXIST(_heap) (NULL == _heap || _heap->m_MagicNumber != HEAP_MAGIC_NUMBER)
#define FIND_BIGGER(a,b,c,_compareFun) ((_compareFun(a,b) && _compareFun(a,c)) ? a : ((_compareFun(b,a) && _compareFun(b,c)) ? b : c))

struct Heap
{
	size_t m_MagicNumber;
	Vector *m_vec;
	size_t m_heapSize;
	PtrCompare m_ptrCompare;
};

typedef struct Context
{
	ActionFunction m_userActionFun;
	void* m_userContext;
	size_t m_numOfActions;
}Context;

/*Swap vector value between positions _i to _j*/
static int Swap(Vector *_vec, int _i, int _j);
/*Get the parent, left and right values and check if need to swap, call Swap if needed*/
static int GetAndSwap(Vector *_vec, int _size, PtrCompare _compareFun);
/*Bubble down the parent if one of its childs is bigger*/
static void Heapify(Heap* _heap, int _size);
/*build the heap by heapify*/
static void HeapBuildHeapify(Heap *_heap);
/*Bubble up the child if it is bigger then its parent, go up until its not bigger*/
static void BubbleUp(Heap *_heap);

/*Build the heap*/
Heap* HeapBuild(Vector* _vec, PtrCompare _compareFun)
{
	Heap *heap;

	if(NULL == _vec || NULL == _compareFun)
	{
		return NULL;
	}

	heap = (Heap*)malloc(sizeof(Heap));
	if(NULL == heap)
	{
		return NULL;
	}

	heap->m_heapSize = VectorNumOfelements(_vec);
	heap->m_vec = _vec;
	heap->m_ptrCompare = _compareFun;
	heap->m_MagicNumber = HEAP_MAGIC_NUMBER;

	HeapBuildHeapify(heap);

	return heap;
}

/*Destroy the heap*/
Vector* HeapDestroy(Heap** _heap)
{
	Vector* vec;
	
	if(NULL == _heap || IS_NOT_EXIST((*_heap)))
	{
		return NULL;
	}

	vec = (*_heap)->m_vec;

	(*_heap)->m_MagicNumber = 0;
	(*_heap)->m_vec = NULL;
	
	free(*_heap);
	(*_heap) = NULL;
	
	return vec;
}

/*Insert new data*/
ErrCode HeapInsert(Heap* _heap, void* _data)
{
	ErrCode err;

	if(IS_NOT_EXIST(_heap))
	{
		return ERR_NOT_INITIALIZE;
	}

	if(SUCCEEDED != (err = VectorAddTail(_heap->m_vec,_data)))
	{
		return err;
	}
	
	++_heap->m_heapSize;
	BubbleUp(_heap);

	return SUCCEEDED;
}

/*Get the max value*/
const void* HeapTop(const Heap* _heap)
{
	void *data;
	
	if(IS_NOT_EXIST(_heap))
	{
		return NULL;
	}

	return (SUCCEEDED == VectorGet(_heap->m_vec,1,&data)) ? data : NULL;
}

/*Get and remove the max value*/
void* HeapExtract(Heap* _heap)
{
	void *temp, *data;

	if(IS_NOT_EXIST(_heap))
	{
		return NULL;
	}

	if(SUCCEEDED != VectorGet(_heap->m_vec,1,&data))
	{
		return NULL;
	}
	
	VectorRemoveTail(_heap->m_vec,&temp);
	VectorSet(_heap->m_vec,1,temp);

	--_heap->m_heapSize;

	Heapify(_heap,1);

	return data;
}

/*Get number of items*/
size_t HeapItemsNum(const Heap* _heap)
{
	if(IS_NOT_EXIST(_heap))
	{
		return 0;
	}

	return _heap->m_heapSize;
}

/*Print the heap*/

static int HeapElementsAction(const void *_element, void *_context)
{
	((Context*)_context)->m_userActionFun(_element,((Context*)_context)->m_userContext);
	--((Context*)_context)->m_numOfActions;
	return ((Context*)_context)->m_numOfActions;
}

size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
	Context cnt;

	if(IS_NOT_EXIST(_heap))
	{
		return 0;
	}
	
	cnt.m_userActionFun = _act;
	cnt.m_userContext = _context;
	cnt.m_numOfActions = _heap->m_heapSize;
	
	return VectorForEach(_heap->m_vec,HeapElementsAction,&cnt);
}

void HeapPrint(const Heap* _heap, void(*prtPrintElement)(void*))
{
	if(IS_NOT_EXIST(_heap))
	{
		return;
	}

	PrintArray(_heap->m_vec,prtPrintElement);
}

/* SUB FUNCTIONS */

static int Swap(Vector *_vec, int _i, int _j)
{
	void *data1, *data2;

	VectorGet(_vec,_i,&data1);
	VectorGet(_vec,_j,&data2);

	VectorSet(_vec,_i,data2);
	VectorSet(_vec,_j,data1);

	return 1;
}

static int GetAndSwap(Vector *_vec, int _index, PtrCompare _compareFun)
{
	void *data, *leftD, *rightD, *bigest;

	VectorGet(_vec,_index,&data);
	VectorGet(_vec,LEFT(_index),&leftD);
	
	if(ERR_ILLEGAL_INPUT == VectorGet(_vec,RIGHT(_index),&rightD))
	{
		 return _compareFun(leftD,data) ? Swap(_vec,_index,LEFT(_index)) : 0;
	}

	bigest = FIND_BIGGER(data,leftD,rightD,_compareFun);

	return (leftD == bigest) ? Swap(_vec,_index,LEFT(_index)) : ((rightD == bigest) ? Swap(_vec,_index,RIGHT(_index)) : 0);
}

static void Heapify(Heap* _heap, int _index)
{
	if(_heap->m_heapSize < _index*2)
	{
		return;
	}

	if(!GetAndSwap(_heap->m_vec,_index,_heap->m_ptrCompare))
	{
		if((_index+1)*2 > _heap->m_heapSize || !GetAndSwap(_heap->m_vec,_index+1,_heap->m_ptrCompare))
		{
			return;		
		}
	}
	
	Heapify(_heap,_index+1);
}

static void HeapBuildHeapify(Heap *_heap)
{
	int i;
	
	for(i = _heap->m_heapSize/2;i > 0;--i)
	{
		Heapify(_heap,i);
	}
}

static void BubbleUp(Heap *_heap)
{
	int childIndx = _heap->m_heapSize , parentIndx;
	void *child, *parent;
	
	while(childIndx > 1)
	{
		parentIndx = PARENT(childIndx);
		VectorGet(_heap->m_vec,childIndx,&child);
		VectorGet(_heap->m_vec,parentIndx,&parent);
		
		if(!_heap->m_ptrCompare(child,parent))
		{
			 return;
		}
		
		Swap(_heap->m_vec,parentIndx,childIndx);
		childIndx = parentIndx;
	}
}




