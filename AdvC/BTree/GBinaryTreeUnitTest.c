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
	BSTreeItr itr;

	for(i = 0;i < _size;++i)
	{
		itr = TreeInsert(_tree,&_arr[i]);
		
		if(NULL == itr || TREE_ITR_EQUALS(BSTreeItrEnd(_tree),itr))
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
	
	TreeDestroy(tree,NULL);
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
	
	if(TREE_ITR_EQUALS(BSTreeItrEnd(tree),TreeInsert(tree,&insertD)))
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
	
	if(TREE_ITR_EQUALS(BSTreeItrEnd(tree),TreeInsert(tree,NULL)))
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
	if(FAILED == FillArr(tree,arr,7) || NULL != (int*)BSTreeItrGet(BSTreeItrEnd(tree)))
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
	
	if(TREE_ITR_EQUALS(BSTreeItrEnd(tree),BSTreeItrNext(itr)))
	{
		TreeDestroy(tree,NULL);
		return SUCCEDD;
	}
	
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

Result TestBSTreeItrNext_Empty()
{
	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}

	if(TREE_ITR_EQUALS(BSTreeItrEnd(tree),BSTreeItrNext(BSTreeItrBegin(tree))))
	{
		TreeDestroy(tree,NULL);
		return SUCCEDD;
	}
	
	TreeDestroy(tree,NULL);
	return FAILED;
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
	
	itr = BSTreeItrPrev(BSTreeItrEnd(tree));
	
	for(i = 0;i < SIZE;++i)
	{
		if(arrRes[i] != *(int*)BSTreeItrGet(itr))
		{
			TreeDestroy(tree,NULL);
			return FAILED;	
		}
		
		itr = BSTreeItrPrev(itr);
	}
	
	if(TREE_ITR_EQUALS(BSTreeItrEnd(tree),BSTreeItrPrev(itr)))
	{
		TreeDestroy(tree,NULL);
		return SUCCEDD;
	}
	
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

Result TestBSTreeItrPrev_Empty()
{
	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	
	if(TREE_ITR_EQUALS(BSTreeItrEnd(tree),BSTreeItrPrev(BSTreeItrEnd(tree))))
	{
		TreeDestroy(tree,NULL);
		return SUCCEDD;
	}
	
	TreeDestroy(tree,NULL);
	return FAILED;
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
	
	if(!TREE_ITR_EQUALS(BSTreeItrEnd(tree),BSTreeForEach(tree,IN_ORDER,AddContext,&context)))
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

/* REMOVE */

Result TestBSTreeItrRemove_ValidRight()
{
	int arr[] = {5,9,3,1,4,11,8};
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

	itr = BSTreeItrNext(BSTreeItrBegin(tree));
	
	if(3 != *(int*)BSTreeItrRemove(itr))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	itr = BSTreeItrNext(BSTreeItrBegin(tree));
	if(4 != *(int*)BSTreeItrGet(itr) || 1 != *(int*)BSTreeItrGet(BSTreeItrPrev(itr)))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

Result TestBSTreeItrRemove_Validleft()
{
	int arr[] = {5,9,3,1,11,8};
	BSTreeItr itr;

	Tree *tree = TreeCreate(LessCompare);
	if(NULL == tree)
	{
		return FAILED;
	}
	
	if(FAILED == FillArr(tree,arr,6))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}

	itr = BSTreeItrNext(BSTreeItrBegin(tree));
	if(3 != *(int*)BSTreeItrRemove(itr) || 5 != *(int*)BSTreeItrGet(BSTreeItrNext(BSTreeItrBegin(tree))))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}

	TreeDestroy(tree,NULL);
	return SUCCEDD;
}

Result TestBSTreeItrRemove_ValidNoChild()
{
	int arr[] = {5,9,3,4,1,11,8};
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

	itr = BSTreeItrNext(BSTreeItrNext(BSTreeItrBegin(tree)));
	printf("--- %d\n\n", *(int*)BSTreeItrGet(itr));
	
	if(4 != *(int*)BSTreeItrRemove(itr))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
	}
	
	itr = BSTreeItrNext(BSTreeItrBegin(tree));
	if(3 != *(int*)BSTreeItrGet(itr) || 5 != *(int*)BSTreeItrGet(BSTreeItrNext(itr)))
	{
		TreeDestroy(tree,NULL);
		return FAILED;
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
	PrintRes("TestBSTreeItrNext_Empty:",TestBSTreeItrNext_Empty);
	/*prev*/
	PrintRes("TestBSTreeItrPrev_Valid:",TestBSTreeItrPrev_Valid);
	PrintRes("TestBSTreeItrPrev_Empty:",TestBSTreeItrPrev_Empty);
	/*for each*/
	PrintRes("TestBSTreeForEach_Valid:",TestBSTreeForEach_Valid);
	/*remove*/
	PrintRes("TestBSTreeItrRemove_ValidRight:",TestBSTreeItrRemove_ValidRight);
	PrintRes("TestBSTreeItrRemove_Validleft:",TestBSTreeItrRemove_Validleft);
	PrintRes("TestBSTreeItrRemove_ValidNoChild:",TestBSTreeItrRemove_ValidNoChild);




	return 0;
}









