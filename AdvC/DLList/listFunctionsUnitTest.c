#include <stdio.h>
#include <assert.h>

#include "listFunctions.h"

#define SIZE 5

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

static int EqualData(void* _a, void* _b)
{
	if(*(int*)_a == *(int*)_b)
	{
		return 1;
	}
	
	return 0;
}

static int Compare(void* _a, void* _b)
{
	if(*(int*)_a < *(int*)_b)
	{
		return 1;
	}
	
	return 0;
}

static void PrintElement(void *_data)
{
	printf("%d \t", *(int*)_data);
}

static List* CreateAndFill(int *_arr, int _size)
{
	int i;
	List *list = DLListCreate();

	if(NULL == list)
	{
		return NULL;
	}

	for(i = 0;i < _size;++i)
	{	
		if(SUCCEEDED != DLListPushHead(list,&_arr[i]))
		{	
			DLListDestroy(list,NULL);
			return NULL;
		}
	}

	return list;
}

static int checkResult(ListItr _end, int *_arr, int _firstIndx, int _lastIndx)
{
	
	for(;_firstIndx <= _lastIndx;++_firstIndx)
	{		
		if(*(int*)ListItrGet(_end) != _arr[_firstIndx])
		{	
			return 0;
		}
		
		_end = ListItrPrev(_end);
	}
	
	return 1;
}


/* FIND FIRST */

Result TestListItrFindFirst_Exist()
{
	int arr[SIZE] = {1,6,3,2,9}, insertD = 3;
	ListItr itrBegin, itrEnd;
	
	List *list = CreateAndFill(arr,SIZE);

	if(NULL == list)
	{
		return FAILED;
	}
	
	itrBegin = ListItrNext(ListItrBegin(list));
	itrEnd = ListItrPrev(ListItrEnd(list));

	if(insertD != *(int*)ListItrGet(ListItrFindFirst(itrBegin,itrEnd,EqualData,&insertD)))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestListItrFindFirst_NotExist()
{
	int arr[SIZE] = {1,6,3,2,9}, insertD = 2;
	ListItr itrBegin, itrEnd;
	List *list = CreateAndFill(arr,SIZE);

	if(NULL == list)
	{
		return FAILED;
	}
	
	itrBegin = ListItrBegin(list);
	itrEnd = ListItrPrev(ListItrPrev(ListItrEnd(list)));

	if(insertD != *(int*)ListItrGet(ListItrFindFirst(itrBegin,itrEnd,EqualData,&insertD)))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestListItrFindFirst_Empty()
{
	int insertD = 2;
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}
	
	if(ListItrEnd(list) != ListItrFindFirst(ListItrBegin(list),ListItrEnd(list),EqualData,&insertD))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

/* COUNT IF NOT ZERO */

Result TestListItrCountIf_Exist()
{
	int arr[SIZE] = {1,2,3,2,2}, insertD = 2;
	ListItr itrBegin, itrEnd;
	
	List *list = CreateAndFill(arr,SIZE);

	if(NULL == list)
	{
		return FAILED;
	}
	
	itrBegin = ListItrNext(ListItrBegin(list));
	itrEnd = ListItrPrev(ListItrEnd(list));

	if(2 != ListItrCountIf(itrBegin,itrEnd,EqualData,&insertD))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestListItrCountIf_NotExist()
{
	int arr[SIZE] = {1,2,3,2,9}, insertD = 4;
	ListItr itrBegin, itrEnd;
	List *list = CreateAndFill(arr,SIZE);

	if(NULL == list)
	{
		return FAILED;
	}
	
	itrBegin = ListItrBegin(list);
	itrEnd = ListItrPrev(ListItrPrev(ListItrEnd(list)));

	if(0 != ListItrCountIf(itrBegin,itrEnd,EqualData,&insertD))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestListItrCountIf_Empty()
{
	int insertD = 2;
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	if(0 != ListItrCountIf(ListItrBegin(list),ListItrEnd(list),EqualData,&insertD))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

/* SORT */

Result TestListItrSort_Valid()
{
	int arr[7] = {1,8,3,2,6,9,7}, arrAfter[7] = {1,8,2,3,6,9,7};
	ListItr itrBegin, itrEnd;
	
	List *list = CreateAndFill(arr,7);

	if(NULL == list)
	{
		return FAILED;
	}
	
	itrBegin = ListItrNext(ListItrBegin(list));
	itrEnd = ListItrPrev(ListItrPrev(ListItrEnd(list)));

	ListItrSort(itrBegin,itrEnd,Compare);

	if(!checkResult(ListItrPrev(ListItrEnd(list)),arrAfter,2,6))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestListItrSort_Empty()
{
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}
	
	ListItrSort(ListItrBegin(list),ListItrEnd(list),Compare);
	
	if(ListItrEnd(list) != ListItrBegin(list))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}


/* SPLICE */

Result TestListItrSplice_Valid()
{
	int arr[7] = {1,8,3,2,6,9,7};
	ListItr itrBegin, itrEnd, dest;	
	
	List *list = CreateAndFill(arr,7);

	if(NULL == list)
	{
		return FAILED;
	}
	
	itrBegin = ListItrNext(ListItrNext(ListItrBegin(list)));
	itrEnd = ListItrPrev(ListItrEnd(list));
	
	dest = ListItrSplice(ListItrBegin(list),itrBegin,itrEnd);

	if(7 != *(int*)ListItrGet(dest) || !checkResult(ListItrPrev(dest),arr,1,4))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

Result TestListItrSplice_Empty()
{
	ListItr dest;
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	dest = ListItrSplice(ListItrBegin(list),ListItrBegin(list),ListItrEnd(list));

	if(!ListItrEquals(dest,ListItrBegin(list)))
	{	
		DLListDestroy(list,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	return SUCCEDD;
}

/* MERGE */

Result TestListItrMerge_Valid()
{
	#define T_SIZE 9
	
	int arr1[T_SIZE] = {10,8,5,3,9,7,4,2,1}, arrAfter[T_SIZE-1] = {10,8,7,5,4,3,2,1};
	ListItr itrEnd1, dest;
	List *list2, *list1 = CreateAndFill(arr1,T_SIZE);

	if(NULL == list1)
	{
		return FAILED;
	}
	
	list2 = DLListCreate();
	if(NULL == list2)
	{
		return FAILED;
	}

	itrEnd1 = ListItrPrev(ListItrPrev(ListItrPrev(ListItrPrev(ListItrEnd(list1)))));

	dest = ListItrMerge(ListItrEnd(list2),ListItrBegin(list1),ListItrPrev(itrEnd1),itrEnd1,ListItrEnd(list1),Compare);

	if(!checkResult(ListItrPrev(dest),arrAfter,0,7))
	{	
		DLListDestroy(list1,NULL);
		DLListDestroy(list2,NULL);
		return FAILED;
	}
	
	DLListDestroy(list1,NULL);
	DLListDestroy(list2,NULL);
	return SUCCEDD;
}

Result TestListItrMerge_Empty()
{	
	ListItr dest;
	List *list2, *list1 = DLListCreate();

	if(NULL == list1)
	{
		return FAILED;
	}
	
	list2 = DLListCreate();
	if(NULL == list2)
	{
		return FAILED;
	}

	dest = ListItrMerge(ListItrEnd(list2),ListItrBegin(list1),ListItrBegin(list1),ListItrBegin(list1),ListItrBegin(list1),Compare);

	if(!ListItrEquals(dest,ListItrBegin(list2)))
	{	
		DLListDestroy(list1,NULL);
		DLListDestroy(list2,NULL);
		return FAILED;
	}
	
	DLListDestroy(list1,NULL);
	DLListDestroy(list2,NULL);
	return SUCCEDD;
}

/* CUT */

Result TestListItrCut_Valid()
{
	int arr[SIZE] = {1,2,3,2,9};
	ListItr itrEnd;
	List *ResList, *list = CreateAndFill(arr,SIZE);

	if(NULL == list)
	{
		return FAILED;
	}
	
	itrEnd = ListItrPrev(ListItrEnd(list));

	ResList = ListItrCut(ListItrBegin(list),itrEnd);
	
	if(!checkResult(ListItrPrev(ListItrEnd(ResList)),arr,1,4))
	{	
		DLListDestroy(list,NULL);
		DLListDestroy(ResList,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	DLListDestroy(ResList,NULL);
	return SUCCEDD;
}

Result TestListItrCut_Empty()
{
	List *ResList, *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	ResList = ListItrCut(ListItrBegin(list),ListItrEnd(list));
	
	if(!ResList || !ListItrEquals(ListItrBegin(ResList),ListItrEnd(ResList)))
	{	
		DLListDestroy(list,NULL);
		DLListDestroy(ResList,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	DLListDestroy(ResList,NULL);
	return SUCCEDD;
}

/* UNIQUE */

Result TestListItrUnique_Valid()
{
	int arr[SIZE] = {1,2,2,3,9}, arrAfter[SIZE-1] = {1,2,3,9};
	List *ResList, *list = CreateAndFill(arr,SIZE);

	if(NULL == list)
	{
		return FAILED;
	}

	ResList = ListItrUnique(ListItrBegin(list),ListItrEnd(list),EqualData);
	
	if(!ResList || !checkResult(ListItrPrev(ListItrEnd(list)),arrAfter,0,3) || 2 != *(int*)ListItrGet(ListItrBegin(ResList)))
	{	
		DLListDestroy(list,NULL);
		DLListDestroy(ResList,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	DLListDestroy(ResList,NULL);
	return SUCCEDD;
}

Result TestListItrUnique_Empty()
{
	List *ResList, *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	ResList = ListItrUnique(ListItrBegin(list),ListItrEnd(list),EqualData);
	
	if(!ResList || !ListItrEquals(ListItrBegin(ResList),ListItrEnd(ResList)))
	{	
		DLListDestroy(list,NULL);
		DLListDestroy(ResList,NULL);
		return FAILED;
	}
	
	DLListDestroy(list,NULL);
	DLListDestroy(ResList,NULL);
	return SUCCEDD;
}


static void PrintRes(char *_str, Result(*ptrPrint)(void))
{
	static int count = 0;
	++count;
	
	printf("\n%d. %-40s \t %s \n", count, _str, (SUCCEDD == (*ptrPrint)()) ? "succedded" : "failed");
}



int main()
{
	/*Find first*/
	/*POS*/
	printf("\n--- Find first: ---\n");
	PrintRes("TestListItrFindFirst_Exist:",TestListItrFindFirst_Exist);
	/*NEG*/
	PrintRes("TestListItrFindFirst_NotExist:",TestListItrFindFirst_NotExist);
	PrintRes("TestListItrFindFirst_Empty:",TestListItrFindFirst_Empty);
	
	/*Count if not zero*/
	/*POS*/
	printf("\n--- Count if not zero: ---\n");
	PrintRes("TestListItrCountIf_Exist:",TestListItrCountIf_Exist);
	PrintRes("TestListItrCountIf_NotExist:",TestListItrCountIf_NotExist);
	/*NEG*/
	PrintRes("TestListItrCountIf_Empty:",TestListItrCountIf_Empty);

	/*Sort*/
	/*POS*/
	printf("\n--- Sort: ---\n");
	PrintRes("TestListItrSort_Valid:",TestListItrSort_Valid);
	/*NEG*/
	PrintRes("TestListItrSort_Empty:",TestListItrSort_Empty);

	/*Splice*/
	/*POS*/
	printf("\n--- Splice: ---\n");
	PrintRes("TestListItrSplice_Valid:",TestListItrSplice_Valid);
	/*NEG*/
	PrintRes("TestListItrSplice_Empty:",TestListItrSplice_Empty);

	/*Merge*/
	/*POS*/
	printf("\n--- Merge: ---\n");
	PrintRes("TestListItrMerge_Valid:",TestListItrMerge_Valid);
	/*NEG*/
	PrintRes("TestListItrMerge_Empty:",TestListItrMerge_Empty);
	
	/*Cut*/
	/*POS*/
	printf("\n--- Cut: ---\n");
	PrintRes("TestListItrCut_Valid:",TestListItrCut_Valid);
	/*NEG*/
	PrintRes("TestListItrCut_Empty:",TestListItrCut_Empty);

	/*Unique*/
	/*POS*/
	printf("\n--- Unique: ---\n");
	PrintRes("TestListItrUnique_Valid:",TestListItrUnique_Valid);
	/*NEG*/
	PrintRes("TestListItrUnique_Empty:",TestListItrUnique_Empty);




/* ----- NULL pointer ------ TODO*/


/*DLListPrint(list,PrintElement);*/

	return 0;
}



