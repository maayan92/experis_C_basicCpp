#include <stdio.h>
#include "heapMax.h"
#include "dynamicVector.h"

#define INIT_SIZE 6
#define BLOCK_SIZE 2

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

static Vector* CreateAndFill(int *_arr, int _size)
{
	int i;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return NULL;
	}

	for(i = 0;i < _size;++i)
	{
		VectorAddTail(vec,_arr[i]);
	}

	return vec;
}

static void DestroyAll(Heap *_heap, Vector *_vec)
{
	VectorDestroy(_vec);
	HeapDestroy(_heap);
}

static Result CheckHeap(Heap *_heap, int *_arrR, Vector *_vec)
{
	int i = 0, data;

	while(SUCCEEDED == HeapExtractMax(_heap,&data))
	{
		if(data != _arrR[i])
		{
			return FAILED;
		}
		
		++i;
	}

	DestroyAll(_heap,_vec);
	return SUCCEDD;
}

/* BUILD HEAP */

Result TestHeapBuild()
{
	int arr[] = {9,3,4,11,7,8}, removeArr[] = {11,9,8,7,4,3};
	
	Vector *vec = CreateAndFill(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	return CheckHeap(heap,removeArr,vec);
}

Result TestHeapBuild_NULLVec()
{
	Heap *heap = HeapBuild(NULL);
	if(NULL == heap)
	{
		return SUCCEDD;
	}

	HeapDestroy(heap);
	return FAILED;
}

Result TestHeapBuild_EmptyVec()
{
	int data;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(ERR_EMPTY == HeapMax(heap,&data))
	{
		DestroyAll(heap,vec);
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

/* DESTROY TREE */

Result TestHeapDestroy_Full()
{
	int arr[] = {9,3,4,11,7,8};
	
	Vector *vec = CreateAndFill(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}


	DestroyAll(heap,vec);
	if(ERR_NOT_INITIALIZE == HeapInsert(heap,6))
	{		
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

Result TestHeapDestroy_Empty()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		return FAILED;
	}
	
	DestroyAll(heap,vec);
	if(ERR_NOT_INITIALIZE == HeapInsert(heap,6))
	{		
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapDestroy_NULLHeap()
{
	HeapDestroy(NULL);
	return SUCCEDD;
}

Result TestHeapDoubleDestroy()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		return FAILED;
	}

	VectorDestroy(vec);
	HeapDestroy(heap);
	HeapDestroy(heap);

	return SUCCEDD;
}

/* INSERT DATA */

Result TestHeapInsert_ValidToRoot()
{
	int data, arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFill(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(SUCCEEDED != HeapInsert(heap,20) || SUCCEEDED != HeapMax(heap,&data) || 20 != data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapInsert_NewParent()
{
	int data, arr[] = {9,3,4,11,7};

	Vector *vec = CreateAndFill(arr,5);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(SUCCEEDED != HeapInsert(heap,20) || SUCCEEDED != HeapMax(heap,&data) || 20 != data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapInsert_ValidToMiddle()
{
	int arr[] = {9,3,4,11,7,8,2}, removeArr[] = {11,9,8,7,6,4,3,2};
	
	Vector *vec = CreateAndFill(arr,7);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(SUCCEEDED != HeapInsert(heap,6))
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	return CheckHeap(heap,removeArr,vec);
}

Result TestHeapInsert_HeapEmpty()
{
	int data;
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		return FAILED;
	}

	if(SUCCEEDED != HeapInsert(heap,20) || SUCCEEDED != HeapMax(heap,&data) || 20 != data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapInsert_NULLHeap()
{
	if(ERR_NOT_INITIALIZE == HeapInsert(NULL,20))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* GET MAX */

Result TestHeapMax_Valid()
{
	int data, arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFill(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(SUCCEEDED != HeapMax(heap,&data) || 11 != data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapMax_Empty()
{
	int data;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(ERR_EMPTY == HeapMax(heap,&data))
	{
		DestroyAll(heap,vec);
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

Result TestHeapMax_NULLHeap()
{
	int data;

	if(ERR_NOT_INITIALIZE == HeapMax(NULL,&data))
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestHeapMax_NULLPointer()
{
	int *data = NULL;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(ERR_ILLEGAL_INPUT == HeapMax(heap,data))
	{
		DestroyAll(heap,vec);
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

/* REMOVE MAX */

Result TestHeapExtractMax_Valid()
{
	int data, arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFill(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(SUCCEEDED != HeapExtractMax(heap,&data) || 11 != data || SUCCEEDED != HeapMax(heap,&data) || 9 != data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapExtractMax_Empty()
{
	int data;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(ERR_EMPTY == HeapExtractMax(heap,&data))
	{
		DestroyAll(heap,vec);
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

Result TestHeapExtractMax_NULLHeap()
{
	int data;

	if(ERR_NOT_INITIALIZE == HeapExtractMax(NULL,&data))
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestHeapExtractMax_NULLPointer()
{
	int *data = NULL;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(ERR_ILLEGAL_INPUT == HeapExtractMax(heap,data))
	{
		DestroyAll(heap,vec);
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

/* NUMBER OF ITEMS */

Result TestHeapItemsNum_Valid()
{
	int arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFill(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(6 != HeapItemsNum(heap))
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapItemsNum_ValidInsert()
{
	int arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFill(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(6 != HeapItemsNum(heap) || SUCCEEDED != HeapInsert(heap,20) || 7 != HeapItemsNum(heap))
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapItemsNum_ValidRemove()
{
	int data, arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFill(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(6 != HeapItemsNum(heap) || SUCCEEDED != HeapExtractMax(heap,&data) || 5 != HeapItemsNum(heap))
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapItemsNum_Empty()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec);

	if(NULL == heap)
	{
		VectorDestroy(vec);
		return FAILED;
	}

	if(0 == HeapItemsNum(heap))
	{
		DestroyAll(heap,vec);
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

Result TestHeapItemsNum_NULLHeap()
{
	if(0 == HeapItemsNum(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

static void Print(char *_str1, Result(*TestFun)(void))
{
	printf("\n%-40s \t %s \n", _str1,(SUCCEDD == (*TestFun)()) ? "succedded" : "failed");
}

int main()
{

	/*Heap build*/
	/*POS*/
	Print("TestHeapBuild",TestHeapBuild);
	/*NEG*/
	Print("TestHeapBuild_NULLVec",TestHeapBuild_NULLVec);
	Print("TestHeapBuild_EmptyVec",TestHeapBuild_EmptyVec);
	
	/*Heap destroy*/
	Print("TestHeapDestroy_Full",TestHeapDestroy_Full);
	Print("TestHeapDestroy_Empty",TestHeapDestroy_Empty);
	/*NEG*/
	Print("TestHeapDestroy_NULLHeap",TestHeapDestroy_NULLHeap);
	Print("TestHeapDoubleDestroy",TestHeapDoubleDestroy);

	/*Insert data*/
	Print("TestHeapInsert_ValidToRoot",TestHeapInsert_ValidToRoot);
	Print("TestHeapInsert_NewParent",TestHeapInsert_NewParent);
	Print("TestHeapInsert_ValidToMiddle",TestHeapInsert_ValidToMiddle);
	/*NEG*/
	Print("TestHeapInsert_HeapEmpty",TestHeapInsert_HeapEmpty);
	Print("TestHeapInsert_NULLHeap",TestHeapInsert_NULLHeap);

	/*Get max*/
	Print("TestHeapMax_Valid",TestHeapMax_Valid);
	/*NEG*/
	Print("TestHeapMax_Empty",TestHeapMax_Empty);
	Print("TestHeapMax_NULLHeap",TestHeapMax_NULLHeap);
	Print("TestHeapMax_NULLPointer",TestHeapMax_NULLPointer);

	/*Remove max*/
	Print("TestHeapExtractMax_Valid",TestHeapExtractMax_Valid);
	/*NEG*/
	Print("TestHeapExtractMax_Empty",TestHeapExtractMax_Empty);
	Print("TestHeapExtractMax_NULLHeap",TestHeapExtractMax_NULLHeap);
	Print("TestHeapExtractMax_NULLPointer",TestHeapExtractMax_NULLPointer);

	/*Number of items*/
	Print("TestHeapItemsNum_Valid",TestHeapItemsNum_Valid);
	Print("TestHeapItemsNum_ValidInsert",TestHeapItemsNum_ValidInsert);
	Print("TestHeapItemsNum_ValidRemove",TestHeapItemsNum_ValidRemove);
	/*NEG*/
	Print("TestHeapItemsNum_Empty",TestHeapItemsNum_Empty);
	Print("TestHeapItemsNum_NULLHeap",TestHeapItemsNum_NULLHeap);

	return 0;
}




