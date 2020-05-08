#include <stdio.h>
#include <stdlib.h>

#include "heapMax.h"

#define HEAP_MAGIC_NUMBER 0xbeefbee0

#define PARENT(i) (i/2)
#define LEFT(i) (2*i)
#define RIGHT(i) (2*i + 1)

#define IS_NOT_EXIST(_heap) (NULL == _heap || _heap->m_MagicNumber != HEAP_MAGIC_NUMBER)
#define FIND_BIGGER(a,b,c) ((a > b && a > c) ? a : ((b > a && b > c) ? b : c))

struct Heap
{
	size_t m_MagicNumber;
	Vector *m_vec;
	size_t m_heapSize;
};

/*Swap vector value between positions _i to _j*/
static int Swap(Vector *_vec, int _i, int _j);
/*Get the parent, left and right values and check if need to swap, call Swap if needed*/
static int GetAndSwap(Vector *_vec, int _size);
/*Bubble down the parent if one of its childs is bigger*/
static void Heapify(Heap* _heap, int _size);
/*Bubble up the child if it is bigger then its parent, go up until its not bigger*/
static void BubbleUp(Heap *_heap);

/*Build the heap*/
Heap* HeapBuild(Vector* _vec)
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

	BubbleUp(heap);

	return heap;
}

/*Destroy the heap*/
void HeapDestroy(Heap* _heap)
{
	if(IS_NOT_EXIST(_heap))
	{
		return;
	}

	_heap->m_MagicNumber = 0;
	free(_heap);
}

/*Insert new data*/
ErrCode HeapInsert(Heap* _heap, int _data)
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
	
	++(_heap->m_heapSize);
	BubbleUp(_heap);

	return SUCCEEDED;
}

/*Get the max value*/
ErrCode HeapMax(Heap* _heap, int* _data)
{
	if(IS_NOT_EXIST(_heap))
	{
		return ERR_NOT_INITIALIZE;
	}

	if(NULL == _data)
	{
		return ERR_ILLEGAL_INPUT;
	}

	if(0 == _heap->m_heapSize)
	{
		return ERR_EMPTY;
	}

	return VectorGet(_heap->m_vec,1,_data);
}

/*Get and remove the max value*/
ErrCode HeapExtractMax(Heap* _heap, int* _data)
{
	int temp;

	if(IS_NOT_EXIST(_heap))
	{
		return ERR_NOT_INITIALIZE;
	}

	if(NULL == _data)
	{
		return ERR_ILLEGAL_INPUT;
	}

	if(0 == _heap->m_heapSize)
	{
		return ERR_EMPTY;
	}

	VectorGet(_heap->m_vec,1,_data);
	VectorRemoveTail(_heap->m_vec,&temp);
	VectorSet(_heap->m_vec,1,temp);

	--(_heap->m_heapSize);

	Heapify(_heap,1);

	return SUCCEEDED;
}

/*Get number of items*/
int HeapItemsNum(Heap* _heap)
{
	if(IS_NOT_EXIST(_heap))
	{
		return 0;
	}

	return _heap->m_heapSize;
}

/*Print the heap*/
void HeapPrint(Heap* _heap)
{
	if(IS_NOT_EXIST(_heap))
	{
		return;
	}

	PrintArray(_heap->m_vec);
}

/* SUB FUNCTIONS */

static int Swap(Vector *_vec, int _i, int _j)
{
	int data1, data2;

	VectorGet(_vec,_i,&data1);
	VectorGet(_vec,_j,&data2);

	VectorSet(_vec,_i,data2);
	VectorSet(_vec,_j,data1);

	return 1;
}

static int GetAndSwap(Vector *_vec, int _size)
{
	int data, leftD, rightD, bigest;

	VectorGet(_vec,_size,&data);
	VectorGet(_vec,LEFT(_size),&leftD);
	
	if(ERR_ILLEGAL_INPUT == VectorGet(_vec,RIGHT(_size),&rightD))
	{
		 return (data < leftD) ? Swap(_vec,_size,LEFT(_size)) : 0;
	}

	bigest = FIND_BIGGER(data,leftD,rightD);

	return (leftD == bigest) ? Swap(_vec,_size,LEFT(_size)) : ((rightD == bigest) ? Swap(_vec,_size,RIGHT(_size)) : 0);
}

static void Heapify(Heap* _heap, int _size)
{
	if(_heap->m_heapSize < _size*2)
	{
		return;
	}

	if(!GetAndSwap(_heap->m_vec,_size))
	{
		return;
	}
	
	Heapify(_heap,_size+1);
}

static void BubbleUp(Heap *_heap)
{
	int i;
	
	for(i = _heap->m_heapSize/2;i > 0;--i)
	{
		Heapify(_heap,i);
	}
}




