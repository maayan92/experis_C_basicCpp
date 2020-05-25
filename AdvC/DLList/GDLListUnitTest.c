#include <stdio.h>
#include <stdlib.h>
#include "GDLList.h"
#include "GDLList_Itr.h"

#define SIZE 5

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

static void DestroyElement(void *_data)
{
	free((int*)_data);
}

static void PrintElement(void *_data)
{
	printf("%d \t", *(int*)_data);
}

static int CompareItrData(int* _data, ListItr _itr)
{
	if(*_data == *(int*)ListItrGet(_itr))
	{
		return 1;
	}
	
	return 0;
}

static ListItr FindItr(List *_list, int* _data)
{
	ListItr beginItr = ListItrBegin(_list);
	ListItr endItr = ListItrEnd(_list);
	
	while(!ListItrEquals(beginItr,endItr) && !CompareItrData(_data,beginItr))
	{
		beginItr = ListItrNext(beginItr);
	}
	
	return beginItr;
}


/* CREATE LIST */

Result TestDLListCreate()
{
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

/* DESTROY LIST */

Result TestDLListDestroy_WithVal()
{
	int i, *arr[SIZE];
	
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}
	
	for(i = 0;i < SIZE;++i)
	{
		arr[i] = (int*)malloc(sizeof(int));
		*arr[i] = i*2;
		
		if(SUCCEEDED != DLListPushHead(list,arr[i]))
		{	
			DLListDestroy(list,DestroyElement);
			return FAILED;
		}
	}
	
	DLListDestroy(list,DestroyElement);

	return SUCCEDD;
}

Result TestDLListDestroy_Empty()
{
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}
	
	DLListDestroy(list,DestroyElement);

	return SUCCEDD;
}

Result TestDLListDestroyNULL()
{
	DLListDestroy(NULL,DestroyElement);

	return SUCCEDD;
}

Result TestDLListDoubleDestroy()
{
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	DLListDestroy(list,DestroyElement);
	DLListDestroy(list,DestroyElement);

	return SUCCEDD;
}

/* PUSH HEAD */

Result TestDLListPushHead_ValidOneInt()
{
	List *list = DLListCreate();
	int *dataH, insertD = 5;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&insertD))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopHead(list,(void**)&dataH) || *dataH != insertD)
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPushHead_ValidOneChar()
{
	List *list = DLListCreate();
	char *dataH, insertD = 'a';

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&insertD))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopHead(list,(void**)&dataH) || *dataH != insertD)
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPushHead_Valid()
{
	List *list = DLListCreate();
	int i, *dataH, arr[SIZE];

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < SIZE;++i)
	{
		arr[i] = i;
		
		if(SUCCEEDED != DLListPushHead(list,&arr[i]))
		{	
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}

	for(i = SIZE-1;i >= 0;--i)
	{
		if(SUCCEEDED != DLListPopHead(list,(void**)&dataH) || *dataH != i)
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}	
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPushHead_NULLList()
{
	int insertD = 1;
	
	if(ERR_NOT_INITIALIZE == DLListPushHead(NULL,&insertD))
	{	
		return SUCCEDD;
	}

	return FAILED;
}

Result TestDLListPushHead_NULLData()
{
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}
	
	if(ERR_ILLEGAL_INPUT == DLListPushHead(list,NULL))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}

	DLListDestroy(list,NULL);
	return FAILED;
}

/* PUSH TAIL */

Result TestDLListPushTail_ValidOneInt()
{
	List *list = DLListCreate();
	int *dataT, insertD = 5;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushTail(list,&insertD))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopTail(list,(void**)&dataT) || *dataT != insertD)
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPushTail_ValidOneChar()
{
	List *list = DLListCreate();
	char *dataT, insertD = 'a';

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushTail(list,&insertD))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopTail(list,(void**)&dataT) || *dataT != insertD)
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPushTail_Valid()
{
	List *list = DLListCreate();
	int i, *dataT, arr[SIZE];

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < 4;++i)
	{
		arr[i] = i;
		
		if(SUCCEEDED != DLListPushTail(list,&arr[i]))
		{	
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}

	for(i = 3;i >= 0;--i)
	{
		if(SUCCEEDED != DLListPopTail(list,(void**)&dataT) || *dataT != i)
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPushTail_NULLList()
{
	int insertD = 1;
	
	if(ERR_NOT_INITIALIZE == DLListPushTail(NULL,&insertD))
	{	
		return SUCCEDD;
	}

	return FAILED;
}

Result TestDLListPushTail_NULLData()
{
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}
	
	if(ERR_ILLEGAL_INPUT == DLListPushTail(list,NULL))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}

	DLListDestroy(list,NULL);
	return FAILED;
}

/* REMOVE FROM HEAD */

Result TestDLListPopHead_ValidOne()
{
	List *list = DLListCreate();
	int *dataH, insertD = 5;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushTail(list,&insertD))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopHead(list,(void**)&dataH) || *dataH != insertD)
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPopHead_Valid()
{
	List *list = DLListCreate();
	int i, *dataH, arr[SIZE];

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < SIZE;++i)
	{
		arr[i] = i;
		
		if(SUCCEEDED != DLListPushTail(list,&arr[i]))
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}

	for(i = 0;i < SIZE;++i)
	{
		if(SUCCEEDED != DLListPopHead(list,(void**)&dataH) || *dataH != i)
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPopHead_NULLList()
{
	int data;
	if(ERR_NOT_INITIALIZE == DLListPopHead(NULL,(void**)&data))
	{	
		return SUCCEDD;
	}

	return FAILED;
}

Result TestDLListPopHead_EmptyList()
{
	int data;
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}

	if(ERR_UNDERFLOW == DLListPopHead(list,(void**)&data))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}

	DLListDestroy(list,NULL);
	return FAILED;
}

Result TestDLListPopHead_NULLPointer()
{
	int data = 5;
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushTail(list,&data))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	if(ERR_ILLEGAL_INPUT == DLListPopHead(list,NULL))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}

	DLListDestroy(list,NULL);
	return FAILED;
}

/* REMOVE FROM TAIL */

Result TestDLListPopTail_ValidOne()
{
	List *list = DLListCreate();
	int *dataT, insertD = 5;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&insertD))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopTail(list,(void**)&dataT) || *dataT != insertD)
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPopTail_Valid()
{
	List *list = DLListCreate();
	int i, *dataT, arr[SIZE];

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < SIZE;++i)
	{
		arr[i] = i;
		
		if(SUCCEEDED != DLListPushHead(list,&arr[i]))
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}
		
	}

	for(i = 0;i < SIZE;++i)
	{
		if(SUCCEEDED != DLListPopTail(list,(void**)&dataT) || *dataT != i)
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListPopTail_NULLList()
{
	int data;
	if(ERR_NOT_INITIALIZE == DLListPopTail(NULL,(void**)&data))
	{	
		return SUCCEDD;
	}

	return FAILED;
}

Result TestDLListPopTail_EmptyList()
{
	int *data;
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}

	if(ERR_UNDERFLOW == DLListPopTail(list,(void**)&data))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}

	DLListDestroy(list,NULL);
	return FAILED;
}

Result TestDLListPopTail_NULLPointer()
{
	int data = 5;
	
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushTail(list,&data))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	if(ERR_ILLEGAL_INPUT == DLListPopTail(list,NULL))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}

	DLListDestroy(list,NULL);
	return FAILED;
}

/* COUNT ITEMS */

Result TestDLListCountItems()
{
	List *list = DLListCreate();
	int i, arr[SIZE];
	
	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < SIZE;++i)
	{
		arr[i] = i;
		
		if(SUCCEEDED != DLListPushHead(list,&arr[i]))
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}

	if(i != DLListCountItems(list))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListCountItems0()
{
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}

	if(0 == DLListCountItems(list))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}
	
	DLListDestroy(list,NULL);
	return FAILED;
}

Result TestDLListCountItems_Insert()
{
	int data = 5;
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}

	if(0 == DLListCountItems(list) && SUCCEEDED == DLListPushHead(list,&data) && 1 == DLListCountItems(list))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}
	
	DLListDestroy(list,NULL);
	return FAILED;
}

Result TestDLListCountItems_NULLList()
{
	if(0 == DLListCountItems(NULL))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* IS EMPTY */

Result TestDLListIsEmptyN()
{
	List *list = DLListCreate();
	int i, arr[SIZE];
	
	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < SIZE;++i)
	{
		arr[i] = i;
		
		if(SUCCEEDED != DLListPushHead(list,&arr[i]))
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}

	if(DLListIsEmpty(list))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListIsEmptyY()
{
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	if(DLListIsEmpty(list))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}
	
	DLListDestroy(list,NULL);
	return FAILED;
}

Result TestDLListIsEmpty_InsertRemove()
{
	List *list = DLListCreate();
	int *data, insertD = 1;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&insertD))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	if(SUCCEEDED != DLListPopTail(list,(void**)&data) || *data != insertD)
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(!DLListIsEmpty(list))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestDLListIsEmpty_NULLList()
{
	if(!DLListIsEmpty(NULL))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* ITERATOR */

/*begin*/
Result TestListItrBegin_Valid()
{
	List *list = DLListCreate();
	int arr[2] = {3,4};

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&arr[0]) || SUCCEEDED != DLListPushHead(list,&arr[1]))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(arr[1] != *(int*)ListItrGet(ListItrBegin(list)))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestListItrBegin_NULLList()
{
	if(NULL == ListItrBegin(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/*end*/
Result TestListItrEnd_Valid()
{
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}
	
	if(NULL != ListItrGet(ListItrEnd(list)))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestListItrEnd_NULLList()
{
	if(NULL == ListItrEnd(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/*equals*/
Result TestListItrEquals_True()
{
	List *list = DLListCreate();
	int data = 5;

	if(NULL == list)
	{
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPushHead(list,&data))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(!ListItrEquals(ListItrBegin(list),ListItrBegin(list)))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestListItrEquals_False()
{
	List *list = DLListCreate();
	int arr[2] = {3,4};
	ListItr begin;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&arr[0]) || SUCCEEDED != DLListPushHead(list,&arr[1]))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	begin = ListItrBegin(list);
	if(!ListItrEquals(begin,ListItrNext(begin)))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}

	DLListDestroy(list,NULL);
	return FAILED;
}

/*next*/
Result TestListItrNext_Valid()
{
	List *list = DLListCreate();
	int arr[2] = {3,4};

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&arr[0]) || SUCCEEDED != DLListPushHead(list,&arr[1]))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(arr[0] != *(int*)ListItrGet(ListItrNext(ListItrBegin(list))))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

/*get*/
Result TestListItrGet_Valid()
{
	List *list = DLListCreate();
	int data = 3;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&data))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	if(data != *(int*)ListItrGet(ListItrBegin(list)))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

/*prev*/
Result TestListItrPrev_Valid()
{
	List *list = DLListCreate();
	int arr[2] = {3,4};

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&arr[0]) || SUCCEEDED != DLListPushHead(list,&arr[1]))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	if(arr[0] != *(int*)ListItrGet(ListItrPrev(ListItrEnd(list))))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

/*set*/
Result TestListItrSet_Valid()
{
	List *list = DLListCreate();
	int arr[2] = {3,4}, newData = 2;
	ListItr itr;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&arr[0]) || SUCCEEDED != DLListPushHead(list,&arr[1]))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	itr = ListItrPrev(ListItrEnd(list));
	
	if(arr[0] != *(int*)ListItrSet(itr,&newData) || newData != *(int*)ListItrGet(itr))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

/*insert before*/
Result TestListItrInsertBefore_Valid()
{
	List *list = DLListCreate();
	int arr[2] = {3,4}, newData = 2;
	ListItr itr, newItr;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&arr[0]) || SUCCEEDED != DLListPushHead(list,&arr[1]))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	itr = ListItrPrev(ListItrEnd(list));
	
	if(!(newItr = ListItrInsertBefore(itr,&newData)) || arr[0] != *(int*)ListItrGet(itr) || newData != *(int*)ListItrGet(newItr))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

/*remove*/
Result TestListItrRemove_Valid()
{
	List *list = DLListCreate();
	int arr[3] = {3,2,4};
	ListItr itr;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,&arr[0]) || SUCCEEDED != DLListPushHead(list,&arr[1]) || SUCCEEDED != DLListPushHead(list,&arr[2]))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	itr = ListItrPrev(ListItrPrev(ListItrEnd(list)));
	
	if(arr[1] != *(int*)ListItrRemove(itr))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}



/* FIND DATA */

Result TestFindData_Exist()
{
	List *list = DLListCreate();
	int i, arr[SIZE];

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < SIZE;++i)
	{
		arr[i] = i;
		
		if(SUCCEEDED != DLListPushHead(list,&arr[i]))
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}
	}
	
	i -= 2;
	if(FindItr(list,&(i)) == ListItrEnd(list))
	{
		DLListDestroy(list,NULL);
		return FAILED;
	}

	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestFindData_NotExist()
{
	List *list = DLListCreate();
	int i, arr[SIZE];

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < SIZE;++i)
	{
		arr[i] = i;
		
		if(SUCCEEDED != DLListPushHead(list,&arr[i]))
		{
			DLListDestroy(list,NULL);
			return FAILED;
		}	
	}
	
	if(FindItr(list,&i) == ListItrEnd(list))
	{
		DLListDestroy(list,NULL);
		return SUCCEDD;
	}

	DLListDestroy(list,NULL);
	return FAILED;
}

static void PrintRes(char *_str, Result(*ptrPrint)(void))
{
	static int count = 0;
	++count;
	
	printf("\n%d. %-40s \t %s \n", count, _str, (SUCCEDD == (*ptrPrint)()) ? "succedded" : "failed");
}

int main()
{
	/*Create list*/
	/*POS*/
	printf("\n--- Create list: ---\n");
	PrintRes("TestDLListCreate:",TestDLListCreate);

	/*Destroy list*/
	/*POS*/
	printf("\n--- Destroy list: ---\n");
	PrintRes("TestDLListDestroy_WithVal:",TestDLListDestroy_WithVal);
	PrintRes("TestDLListDestroy_Empty:",TestDLListDestroy_Empty);
	/*NEG*/
	PrintRes("TestDLListDestroyNULL:",TestDLListDestroyNULL);
	PrintRes("TestDLListDoubleDestroy:",TestDLListDoubleDestroy);

	/*Push head*/
	/*POS*/
	printf("\n--- Push head: ---\n");
	PrintRes("TestDLListPushHead_ValidOneInt:",TestDLListPushHead_ValidOneInt);
	PrintRes("TestDLListPushHead_ValidOneChar:",TestDLListPushHead_ValidOneChar);
	PrintRes("TestDLListPushHead_Valid:",TestDLListPushHead_Valid);
	/*NEG*/
	PrintRes("TestDLListPushHead_NULLList:",TestDLListPushHead_NULLList);
	PrintRes("TestDLListPushHead_NULLData:",TestDLListPushHead_NULLData);

	/*Push tail*/
	/*POS*/
	printf("\n--- Push tail: ---\n");
	PrintRes("TestDLListPushTail_ValidOneInt:",TestDLListPushTail_ValidOneInt);
	PrintRes("TestDLListPushTail_ValidOneChar:",TestDLListPushTail_ValidOneChar);
	PrintRes("TestDLListPushTail_Valid:",TestDLListPushTail_Valid);
	/*NEG*/
	PrintRes("TestDLListPushTail_NULLList:",TestDLListPushTail_NULLList);
	PrintRes("TestDLListPushTail_NULLData:",TestDLListPushTail_NULLData);

	/*Pop head*/
	/*POS*/
	printf("\n--- Pop head: ---\n");
	PrintRes("TestDLListPopHead_ValidOne:",TestDLListPopHead_ValidOne);
	PrintRes("TestDLListPopHead_Valid:",TestDLListPopHead_Valid);
	/*NEG*/
	PrintRes("TestDLListPopHead_NULLList:",TestDLListPopHead_NULLList);
	PrintRes("TestDLListPopHead_EmptyList:",TestDLListPopHead_EmptyList);
	PrintRes("TestDLListPopHead_NULLPointer:",TestDLListPopHead_NULLPointer);

	/*Pop tail*/
	/*POS*/
	printf("\n--- Pop tail: ---\n");
	PrintRes("TestDLListPopTail_ValidOne:",TestDLListPopTail_ValidOne);
	PrintRes("TestDLListPopTail_Valid:",TestDLListPopTail_Valid);
	/*NEG*/
	PrintRes("TestDLListPopTail_NULLList:",TestDLListPopTail_NULLList);
	PrintRes("TestDLListPopTail_EmptyList:",TestDLListPopTail_EmptyList);
	PrintRes("TestDLListPopTail_NULLPointer:",TestDLListPopTail_NULLPointer);

	/*Count elements*/
	/*POS*/
	printf("\n--- Count elements: ---\n");
	PrintRes("TestDLListCountItems:",TestDLListCountItems);
	PrintRes("TestDLListCountItems0:",TestDLListCountItems0);
	PrintRes("TestDLListCountItems_Insert:",TestDLListCountItems_Insert);
	/*NEG*/
	PrintRes("TestDLListCountItems_NULLList:",TestDLListCountItems_NULLList);

	/*Is empty*/
	/*POS*/
	printf("\n--- Is empty: ---\n");
	PrintRes("TestDLListIsEmptyN:",TestDLListIsEmptyN);
	PrintRes("TestDLListIsEmptyY:",TestDLListIsEmptyY);
	PrintRes("TestDLListIsEmpty_InsertRemove:",TestDLListIsEmpty_InsertRemove);
	/*NEG*/
	PrintRes("TestDLListIsEmpty_NULLList:",TestDLListIsEmpty_NULLList);
	
	/*Iterators*/
	printf("\n--- Iterators: ---\n");
	/*begin POS*/
	PrintRes("TestListItrBegin_Valid:",TestListItrBegin_Valid);
	/*NEG*/
	PrintRes("TestListItrBegin_NULLList:",TestListItrBegin_NULLList);
	/*end POS*/
	PrintRes("TestListItrEnd_Valid:",TestListItrEnd_Valid);
	/*NEG*/
	PrintRes("TestListItrEnd_NULLList:",TestListItrEnd_NULLList);
	/*equals POS*/
	PrintRes("TestListItrEquals_True:",TestListItrEquals_True);
	/*NEG*/
	PrintRes("TestListItrEquals_False:",TestListItrEquals_False);
	/*next*/
	PrintRes("TestListItrNext_Valid:",TestListItrNext_Valid);
	/*get*/
	PrintRes("TestListItrGet_Valid:",TestListItrGet_Valid);
	/*prev*/
	PrintRes("TestListItrPrev_Valid:",TestListItrPrev_Valid);
	/*set*/
	PrintRes("TestListItrSet_Valid:",TestListItrSet_Valid);
	/*insert before*/
	PrintRes("TestListItrInsertBefore_Valid:",TestListItrInsertBefore_Valid);
	/*remove*/
	PrintRes("TestListItrRemove_Valid:",TestListItrRemove_Valid);
	

	/*Find data*/
	printf("\n--- Find data: ---\n");
	PrintRes("TestFindData_Exist:",TestFindData_Exist);
	PrintRes("TestFindData_NotExist:",TestFindData_NotExist);

	return 0;
}


