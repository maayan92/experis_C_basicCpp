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

/*Swap vector value between positions _i to _j*/
static int Swap(Vector *_vec, int _i, int _j);
/*Get the parent, left and right values and check if need to swap, call Swap if needed*/
static int GetAndSwap(Vector *_vec, int _size, PtrCompare _compareFun);
/*Bubble down the parent if one of its childs is bigger*/
static void Heapify(Heap* _heap, int _size, PtrCompare _compareFun);
/*Bubble up the child if it is bigger then its parent, go up until its not bigger*/
static void BubbleUp(Heap *_heap, PtrCompare _compareFun);

/*Build the heap*/
Heap* HeapBuild(Vector* _vec, PtrCompare _compareFun)
{
	Heap *heap;

	if(NULL == _vec)
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
	heap->m_MagicNumber = HEAP_MAGIC_NUMBER;
	heap->m_ptrCompare = _compareFun;

	BubbleUp(heap,_compareFun);

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
	BubbleUp(_heap,_heap->m_ptrCompare);

	return SUCCEEDED;
}

/*Get the max value*/
const void* HeapTop(const Heap* _heap)
{
	void *data;
	
	if(IS_NOT_EXIST(_heap) || 0 == _heap->m_heapSize)
	{
		return NULL;
	}

	return (SUCCEEDED == VectorGet(_heap->m_vec,1,&data)) ? data : NULL;
}

/*Get and remove the max value*/
void* HeapExtract(Heap* _heap)
{
	void *temp, *data;

	if(IS_NOT_EXIST(_heap) || 0 == _heap->m_heapSize)
	{
		return NULL;
	}

	VectorGet(_heap->m_vec,1,&data);
	VectorRemoveTail(_heap->m_vec,&temp);
	VectorSet(_heap->m_vec,1,temp);

	--_heap->m_heapSize;

	Heapify(_heap,1,_heap->m_ptrCompare);

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
size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
	if(IS_NOT_EXIST(_heap))
	{
		return 0;
	}
	
	return VectorForEach(_heap->m_vec,_act,_context);
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

static int GetAndSwap(Vector *_vec, int _size, PtrCompare _compareFun)
{
	void *data, *leftD, *rightD, *bigest;

	VectorGet(_vec,_size,&data);
	VectorGet(_vec,LEFT(_size),&leftD);
	
	if(ERR_ILLEGAL_INPUT == VectorGet(_vec,RIGHT(_size),&rightD))
	{
		 return _compareFun(leftD,data) ? Swap(_vec,_size,LEFT(_size)) : 0;
	}

	bigest = FIND_BIGGER(data,leftD,rightD,_compareFun);

	return (leftD == bigest) ? Swap(_vec,_size,LEFT(_size)) : ((rightD == bigest) ? Swap(_vec,_size,RIGHT(_size)) : 0);
}

static void Heapify(Heap* _heap, int _size, PtrCompare _compareFun)
{
	if(_heap->m_heapSize < _size*2)
	{
		return;
	}

	if(!GetAndSwap(_heap->m_vec,_size,_compareFun))
	{
		if((_size+1)*2 > _heap->m_heapSize || !GetAndSwap(_heap->m_vec,_size+1,_compareFun))
		{
			return;		
		}
	}
	
	Heapify(_heap,_size+1,_compareFun);
}

static void BubbleUp(Heap *_heap, PtrCompare _compareFun)
{
	int i;
	
	for(i = _heap->m_heapSize/2;i > 0;--i)
	{
		Heapify(_heap,i,_compareFun);
	}
}




