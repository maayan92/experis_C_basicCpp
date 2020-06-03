#include <stdio.h>
#include "heap.h"

#define INIT_SIZE 6
#define BLOCK_SIZE 2

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

typedef enum
{
	RED,
	BLUE,
	GREEN
}Color;

static Vector* CreateAndFillInt(int *_arr, int _size)
{
	int i;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return NULL;
	}

	for(i = 0;i < _size;++i)
	{
		VectorAddTail(vec,&_arr[i]);
	}

	return 	vec;
}

static Vector* CreateAndFillChar(char *_arr, int _size)
{
	int i;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return NULL;
	}

	for(i = 0;i < _size;++i)
	{
		VectorAddTail(vec,&_arr[i]);
	}

	return 	vec;
}


static void DestroyAll(Heap *_heap, Vector *_vec)
{
	VectorDestroy(_vec,NULL);
	HeapDestroy(&_heap);
}

static int CompareValuesChar(const void *_data1, const void *_data2)
{
	if(*(char*)_data1 > *(char*)_data2)
	{
		return 1;
	}
	
	return 0;
}

static int CompareValuesInt(const void *_data1, const void *_data2)
{
	if(*(int*)_data1 > *(int*)_data2)
	{
		return 1;
	}
	
	return 0;
}

static Result CheckHeapInt(Heap *_heap, int *_arrR, Vector *_vec)
{
	int i = 0;
	int *data;

	while(NULL != (data = (int*)HeapExtract(_heap)))
	{
		if(*(int*)data != _arrR[i])
		{
			return FAILED;
		}
		
		++i;
	}

	DestroyAll(_heap,_vec);
	return SUCCEDD;
}

static Result CheckHeapChar(Heap *_heap, char *_arrR, Vector *_vec)
{
	int i = 0;
	char *data;

	while(NULL != (data = (char*)HeapExtract(_heap)))
	{
		if(*(char*)data != _arrR[i])
		{
			return FAILED;
		}
		
		++i;
	}

	DestroyAll(_heap,_vec);
	return SUCCEDD;
}

static int PrintElements(const void* _data, void* _context)
{
	switch(*(Color*)_context)
	{
		case RED:
			printf("\x1B[31m %d \x1B[0m\t", *(int*)_data);	
			return 1;

		case BLUE:
			printf("\x1B[34m%d\x1B[0m\t", *(int*)_data);	
			return 1;
		
		default:
			printf("\x1B[32m%d\x1B[0m\t", *(int*)_data);
			return 1;
	}
	
	return 0;
}

static int Power(int _data, int _context)
{
	--_context;
	while(--_context)
	{
		_data *= _data;
	}
	
	return _data;
}

static int PrintPower(const void* _data, void* _context)
{
	int pow = Power(*(int*)_data,*(int*)_context);
	
	printf("the power of %d in %d is %d\n", *(int*)_data, *(int*)_context, pow);
	
	return 1;
}

/* BUILD HEAP */

/*int values*/
Result TestHeapBuild_ValidInt()
{
	int arr[] = {3,8,11,4,9,7}, removeArr[] = {11,9,8,7,4,3};
	Heap *heap;
	
	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}
	
	heap = HeapBuild(vec,CompareValuesInt);
	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	return CheckHeapInt(heap,removeArr,vec);
}

/*char values*/
Result TestHeapBuild_ValidChar()
{
	char arr[] = {'a','g','t','b','h','e'}, removeArr[] = {'t','h','g','e','b','a'};
	Heap *heap;
	
	Vector *vec = CreateAndFillChar(arr,INIT_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}

	heap = HeapBuild(vec,CompareValuesChar);
	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	return CheckHeapChar(heap,removeArr,vec);
}

Result TestHeapBuild_NULLVec()
{
	Heap *heap = HeapBuild(NULL,CompareValuesInt);
	if(NULL == heap)
	{
		return SUCCEDD;
	}

	HeapDestroy(&heap);
	return FAILED;
}

Result TestHeapBuild_EmptyVec()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(NULL == HeapTop(heap))
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
	int insertD = 6, arr[] = {9,3,4,11,7,8};
	
	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	DestroyAll(heap,vec);
	if(ERR_NOT_INITIALIZE == HeapInsert(heap,&insertD))
	{		
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

Result TestHeapDestroy_Empty()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);
	int insertD = 6;

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}
	
	DestroyAll(heap,vec);
	if(ERR_NOT_INITIALIZE == HeapInsert(heap,&insertD))
	{		
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapDestroy_NULLHeap()
{
	if(NULL == HeapDestroy(NULL))
	{
		return SUCCEDD;	
	}
	
	return FAILED;
}

Result TestHeapDoubleDestroy()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		return FAILED;
	}

	VectorDestroy(vec,NULL);
	HeapDestroy(&heap);
	HeapDestroy(&heap);

	return SUCCEDD;
}

/* INSERT DATA */

Result TestHeapInsert_ValidToRoot()
{
	int *data, insertD = 20, arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(SUCCEEDED != HeapInsert(heap,&insertD) || NULL == (data = (int*)HeapTop(heap)) || insertD != *data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapInsert_NewParent()
{
	int *data, insertD = 20, arr[] = {9,3,4,11,7};

	Vector *vec = CreateAndFillInt(arr,5);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(SUCCEEDED != HeapInsert(heap,&insertD) || NULL == (data = (int*)HeapTop(heap)) || insertD != *data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapInsert_ValidToMiddle()
{
	int data = 6, arr[] = {9,3,4,11,7,8,2}, removeArr[] = {11,9,8,7,6,4,3,2};
	
	Vector *vec = CreateAndFillInt(arr,7);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(SUCCEEDED != HeapInsert(heap,&data))
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	return CheckHeapInt(heap,removeArr,vec);
}

Result TestHeapInsert_HeapEmpty()
{
	int *data, insertD = 20;
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(SUCCEEDED != HeapInsert(heap,&insertD) || NULL == (data = (int*)HeapTop(heap)) || insertD != *data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapInsert_NULLHeap()
{
	int data = 20;
	
	if(ERR_NOT_INITIALIZE == HeapInsert(NULL,&data))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* GET */

Result TestHeapTop_Valid()
{
	int *data, topD = 11, arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(NULL == (data = (int*)HeapTop(heap)) || topD != *data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapTop_Empty()
{
	int *data;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(NULL == (data = (int*)HeapTop(heap)))
	{
		DestroyAll(heap,vec);
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

Result TestHeapTop_NULLHeap()
{
	int *data;

	if(NULL == (data = (int*)HeapTop(NULL)))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* REMOVE */

Result TestHeapExtract_Valid()
{
	int *data, ExData = 11, topD = 9, arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(NULL == (data = (int*)HeapExtract(heap)) || ExData != *data || NULL == (data = (int*)HeapTop(heap)) || topD != *data)
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapExtract_Empty()
{
	int *data;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(NULL == (data = (int*)HeapExtract(heap)))
	{
		DestroyAll(heap,vec);
		return SUCCEDD;
	}

	DestroyAll(heap,vec);
	return FAILED;
}

Result TestHeapExtract_NULLHeap()
{
	int *data;

	if(NULL == (data = (int*)HeapExtract(NULL)))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* NUMBER OF ITEMS */

Result TestHeapItemsNum_Valid()
{
	int arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
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
	int arr[] = {9,3,4,11,7,8}, data = 20;

	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(6 != HeapItemsNum(heap) || SUCCEEDED != HeapInsert(heap,&data) || 7 != HeapItemsNum(heap))
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	DestroyAll(heap,vec);
	return SUCCEDD;
}

Result TestHeapItemsNum_ValidRemove()
{
	int *data, arr[] = {9,3,4,11,7,8};

	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(6 != HeapItemsNum(heap) || NULL == (data = (int*)HeapExtract(heap)) || 5 != HeapItemsNum(heap))
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
	Heap *heap = HeapBuild(vec,CompareValuesInt);

	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
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

/* FOR EACH */

Result TestHeapForEach_PrintInColor()
{
	int arr[] = {3,8,11,4,9,7}, removeArr[] = {11,9,8,7,4,3};
	Heap *heap;
	Color c = RED;
	
	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}
	
	heap = HeapBuild(vec,CompareValuesInt);
	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}
	
	if(6 != HeapForEach(heap,PrintElements,&c))
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	return CheckHeapInt(heap,removeArr,vec);
}

Result TestHeapForEach_PrintPower()
{
	int arr[] = {3,8,11,4,9,7}, removeArr[] = {11,9,8,7,4,3};
	Heap *heap;
	int pow = 3;
	
	Vector *vec = CreateAndFillInt(arr,INIT_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}
	
	heap = HeapBuild(vec,CompareValuesInt);
	if(NULL == heap)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}	
	
	if(6 != HeapForEach(heap,PrintPower,&pow))
	{
		DestroyAll(heap,vec);
		return FAILED;
	}

	return CheckHeapInt(heap,removeArr,vec);
}


static void Print(char *_str1, Result(*TestFun)(void))
{
	static int count = 0;
	++count;
	printf("\n%d %-40s \t %s \n",count, _str1,(SUCCEDD == (*TestFun)()) ? "succedded" : "failed");
}

int main()
{

	/*Heap build*/
	printf("\nHeap build: \n");
	/*POS*/
	Print("TestHeapBuild_ValidInt",TestHeapBuild_ValidInt);
	Print("TestHeapBuild_ValidChar",TestHeapBuild_ValidChar);
	/*NEG*/
	Print("TestHeapBuild_NULLVec",TestHeapBuild_NULLVec);
	Print("TestHeapBuild_EmptyVec",TestHeapBuild_EmptyVec);
	
	/*Heap destroy*/
	printf("\nHeap destroy: \n");
	Print("TestHeapDestroy_Full",TestHeapDestroy_Full);
	Print("TestHeapDestroy_Empty",TestHeapDestroy_Empty);
	/*NEG*/
	Print("TestHeapDestroy_NULLHeap",TestHeapDestroy_NULLHeap);
	Print("TestHeapDoubleDestroy",TestHeapDoubleDestroy);

	/*Insert data*/
	printf("\nInsert data: \n");
	/*POS*/
	Print("TestHeapInsert_ValidToRoot",TestHeapInsert_ValidToRoot);
	Print("TestHeapInsert_NewParent",TestHeapInsert_NewParent);
	Print("TestHeapInsert_ValidToMiddle",TestHeapInsert_ValidToMiddle);
	/*NEG*/
	Print("TestHeapInsert_HeapEmpty",TestHeapInsert_HeapEmpty);
	Print("TestHeapInsert_NULLHeap",TestHeapInsert_NULLHeap);

	/*Get top*/
	printf("\nGet top: \n");
	/*POS*/
	Print("TestHeapTop_Valid",TestHeapTop_Valid);
	/*NEG*/
	Print("TestHeapTop_Empty",TestHeapTop_Empty);
	Print("TestHeapTop_NULLHeap",TestHeapTop_NULLHeap);

	/*Remove top*/
	printf("\nRemove top: \n");
	Print("TestHeapExtract_Valid",TestHeapExtract_Valid);
	/*NEG*/
	Print("TestHeapExtract_Empty",TestHeapExtract_Empty);
	Print("TestHeapExtract_NULLHeap",TestHeapExtract_NULLHeap);

	/*Number of items*/
	printf("\nRemove top: \n");
	Print("TestHeapItemsNum_Valid",TestHeapItemsNum_Valid);
	Print("TestHeapItemsNum_ValidInsert",TestHeapItemsNum_ValidInsert);
	Print("TestHeapItemsNum_ValidRemove",TestHeapItemsNum_ValidRemove);
	/*NEG*/
	Print("TestHeapItemsNum_Empty",TestHeapItemsNum_Empty);
	Print("TestHeapItemsNum_NULLHeap",TestHeapItemsNum_NULLHeap);

	/**/
	Print("TestHeapForEach_PrintInColor",TestHeapForEach_PrintInColor);
	Print("TestHeapForEach_PrintPower",TestHeapForEach_PrintPower);



	return 0;
}




