#include <stdio.h>
#include <stdlib.h>
#include "GBinaryTree.h"

#define SIZE 7

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

static Result FillArr(Tree *_tree, int *_arr, int _size)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		if(NULL == TreeInsert(_tree,&_arr[i]))
		{
			return FAILED;
		}
	}
	return SUCCEDD;
}

static int LessCompare(void* _left, void* _right)
{
	if(*(int*)_left < *(int*)_right)
	{
		return 1;
	}
	
	return 0;
}

static void DestroyData(void* _data)
{
	free((int*)_data);
}

static int AddContext(void* _data, void* _context)
{
	*(int*)_data += *(int*)_context;
	
	++(*(int*)_context);
	
	return 1;
}


/* CREATE TREE */
Result TestTreeCreate()
{
	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	return SUCCEDD;
}

/* DESTROY TREE */

Result TestTreeDestroy()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}		

	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

Result TestTreeDestroy_DataDestroy()
{
	int i, *arr[SIZE];
	Tree *tree;
	
	for(i = 0;i < SIZE;++i)
	{
		arr[i] = (int*)malloc(sizeof(int));
		*arr[i] = i;
	}

	tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}

	for(i = 0;i < SIZE;++i)
	{
		if(NULL == TreeInsert(tree,arr[i]))
		{
			TreeDestroy(tree,DestroyData);
			return FAILED;
		}
	}

	TreeDestroy(tree,DestroyData);
	return SUCCEDD;
}

Result TestTreeDestroy_Empty()
{
	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

Result TestTreeDestroyNULL()
{
	TreeDestroy(NULL,NULL);
	return SUCCEDD;
}

Result TestTreeDoubleDestroy()
{
	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	TreeDestroy(tree,NULL);
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

/* INSERT DATA */

Result TestTreeInsert_Valid()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

Result TestTreeInsert_Duplicate()
{
	int arr[] = {5,9,3,1,4,11,8}, insertD = 9;

	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	if(NULL == TreeInsert(tree,&insertD))
	{
		TreeDestroy(tree,NULL);
		return SUCCEDD;
	}
	
	TreeDestroy(tree,NULL);
	return FAILED;
}

Result TestTreeInsert_NULLTree()
{
	int insertD = 2;
	
	if(NULL == TreeInsert(NULL,&insertD))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

Result TestTreeInsert_NULLData()
{
	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	
	if(NULL == TreeInsert(tree,NULL))
	{
		TreeDestroy(tree,NULL);
		return SUCCEDD;
	}
	
	TreeDestroy(tree,NULL);
	return FAILED;
}


/* BEGIN */

Result TestBSTreeItrBegin_Valid()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	
	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	if(1 != *(int*)BSTreeItrGet(BSTreeItrBegin(tree)))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

Result TestBSTreeItrBegin_Empty()
{
	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	
	if(BSTreeItrEnd(tree) == BSTreeItrBegin(tree))
	{
		TreeDestroy(tree,NULL);
		return SUCCEDD;
	}
	
	TreeDestroy(tree,NULL);
	return FAILED;
}

Result TestBSTreeItrBegin_NULL()
{
	
	if(NULL == BSTreeItrBegin(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* END */

Result TestBSTreeItrEnd_Valid()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	if(FAILED == FillArr(tree,arr,7) || 11 != *(int*)BSTreeItrGet(BSTreeItrEnd(tree)))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

Result TestBSTreeItrEnd_Empty()
{
	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	if(BSTreeItrBegin(tree) == BSTreeItrEnd(tree))
	{
		TreeDestroy(tree,NULL);
		return SUCCEDD;
	}
	
	TreeDestroy(tree,NULL);
	return FAILED;
}

Result TestBSTreeItrEnd_NULL()
{

	if(NULL == BSTreeItrEnd(NULL))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}
/* NEXT */

Result TestBSTreeItrNext_Valid()
{
	int i, arr[SIZE] = {5,9,3,1,4,11,8}, arrRes[SIZE] = {1,3,4,5,8,9,11};
	BSTreeItr itr;

	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	
	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree,NULL);
		return FAILED;	
	}
	
	
	itr = BSTreeItrBegin(tree);
	
	for(i = 0;i < SIZE;++i)
	{
		if(arrRes[i] != *(int*)BSTreeItrGet(itr))
		{
			TreeDestroy(tree,NULL);
			return FAILED;	
		}
		
		itr = BSTreeItrNext(itr);
	}
	
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

/* PREV */

Result TestBSTreeItrPrev_Valid()
{
	int i, arr[SIZE] = {5,9,3,1,4,11,8}, arrRes[SIZE] = {11,9,8,5,4,3,1};
	BSTreeItr itr;
	
	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	
	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree,NULL);
		return FAILED;	
	}
	
	itr = BSTreeItrEnd(tree);
	
	for(i = 0;i < SIZE;++i)
	{
		if(arrRes[i] != *(int*)BSTreeItrGet(itr))
		{
			TreeDestroy(tree,NULL);
			return FAILED;	
		}
		
		itr = BSTreeItrPrev(itr);
	}
	
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

/* FOR EACH */

Result TestBSTreeForEach_Valid()
{
	int i, arr[] = {5,9,3,1,4,11,8}, context = 1, arrRes[SIZE] = {2,5,7,9,13,15,18};
	BSTreeItr itr;

	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	
	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	if(NULL != BSTreeForEach(tree,IN_ORDER,AddContext,&context))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	itr = BSTreeItrBegin(tree);
	
	for(i = 0;i < SIZE;++i)
	{
		if(arrRes[i] != *(int*)BSTreeItrGet(itr))
		{
			TreeDestroy(tree,NULL);
			return FAILED;	
		}
		
		itr = BSTreeItrNext(itr);
	}
	
	TreeDestroy(tree,NULL);
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
	/*Tree *tree;
	int arr[] = {5,9,3,1,4,11,8};*/
	
	/*Create tree*/
	printf("\n--- Create tree: ---\n");
	/*POS*/
	PrintRes("TestTreeCreate:",TestTreeCreate);

	/*Destroy tree*/
	printf("\n--- Destroy tree: ---\n");
	/*POS*/
	PrintRes("TestTreeDestroy:",TestTreeDestroy);
	PrintRes("TestTreeDestroy_DataDestroy:",TestTreeDestroy_DataDestroy);
	PrintRes("TestTreeDestroy_Empty:",TestTreeDestroy_Empty);
	/*NEG*/
	PrintRes("TestTreeDestroyNULL:",TestTreeDestroyNULL);
	PrintRes("TestTreeDoubleDestroy:",TestTreeDoubleDestroy);

	/*Insert data*/
	printf("\n--- Insert data: ---\n");
	/*POS*/
	PrintRes("TestTreeInsert_Valid:",TestTreeInsert_Valid);
	/*NEG*/
	PrintRes("TestTreeInsert_Duplicate:",TestTreeInsert_Duplicate);
	PrintRes("TestTreeInsert_NULLTree:",TestTreeInsert_NULLTree);
	PrintRes("TestTreeInsert_NULLData:",TestTreeInsert_NULLData);
	


	/*Iterators*/
	printf("\n--- Iterators: ---\n");
	/*begin*/
	PrintRes("TestBSTreeItrBegin_Valid:",TestBSTreeItrBegin_Valid);
	PrintRes("TestBSTreeItrBegin_Empty:",TestBSTreeItrBegin_Empty);
	PrintRes("TestBSTreeItrBegin_NULL:",TestBSTreeItrBegin_NULL);
	/*end*/
	PrintRes("TestBSTreeItrEnd_Valid:",TestBSTreeItrEnd_Valid);
	PrintRes("TestBSTreeItrEnd_Empty:",TestBSTreeItrEnd_Empty);
	PrintRes("TestBSTreeItrEnd_Empty:",TestBSTreeItrEnd_Empty);
	/*next*/
	PrintRes("TestBSTreeItrNext_Valid:",TestBSTreeItrNext_Valid);
	/*prev*/
	PrintRes("TestBSTreeItrPrev_Valid:",TestBSTreeItrPrev_Valid);
	/*for each*/
	PrintRes("TestBSTreeForEach_Valid:",TestBSTreeForEach_Valid);





	/*Print*/
/*	tree = TreeCreate();	
	if(NULL == tree)
	{
		printf("create tree Failed!\n");
	}

	if(SUCCEDD == FillArr(tree,arr,7))
	{
		TreePrint(tree,PRE_ORDER);
		TreePrint(tree,IN_ORDER);
		TreePrint(tree,POST_ORDER);
	}
*/
	return 0;
}









