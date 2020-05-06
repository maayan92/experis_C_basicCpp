#include <stdio.h>
#include "binaryTree.h"

#define SIZE 7

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

/* CREATE TREE */

Result TestTreeCreate()
{
	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	return SUCCEDD;
}

/* DESTROY TREE */

Result TestTreeDestroy()
{
	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}
	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestTreeDestroyNULL()
{
	TreeDestroy(NULL);
	return SUCCEDD;
}

Result TestTreeDoubleDestroy()
{
	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	TreeDestroy(tree);
	TreeDestroy(tree);
	return SUCCEDD;
}

/* INSERT DATA */

static Result FillArr(Tree *_tree)
{
	int arr[] = {3,5,4,9,1,7,2}, i;

	for(i = 0;i < SIZE;++i)
	{
		if(SUCCEEDED != TreeInsert(_tree,arr[i]))
		{
			return FAILED;
		}
	}

	return SUCCEDD;
}

Result TestTreeInsert_Valid()
{
	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}

	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestTreeInsert_Duplicate()
{
	Tree *tree = TreeCreate();	
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	if(ERR_ILLEGAL_INPUT == TreeInsert(tree,2))
	{
		TreeDestroy(tree);
		return SUCCEDD;
	}
	
	TreeDestroy(tree);
	return FAILED;
}

Result TestTreeInsert_NULL()
{
	if(ERR_NOT_INITIALIZE == TreeInsert(NULL,2))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* IS FOUND */

Result TestTreeIsDataFound_Exist()
{
	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}

	if(!TreeIsDataFound(tree,1))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestTreeIsDataFound_NotExist()
{
	Tree *tree = TreeCreate();	
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	if(!TreeIsDataFound(tree,6))
	{
		TreeDestroy(tree);
		return SUCCEDD;
	}
	
	TreeDestroy(tree);
	return FAILED;
}

Result TestTreeIsDataFound_NULL()
{
	if(!TreeIsDataFound(NULL,2))
	{
		return SUCCEDD;
	}

	return FAILED;
}

int main()
{
	Result res;
	
	/*Create tree*/
	/*POS*/
	res = TestTreeCreate();
	printf("\n%-40s \t %s \n", "TestTreeCreate:",(SUCCEDD == res) ? "succedded" : "failed");

	/*Destroy tree*/
	/*POS*/
	res = TestTreeDestroy();
	printf("\n%-40s \t %s \n", "TestTreeDestroy:",(SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestTreeDestroyNULL();
	printf("\n%-40s \t %s \n" ,"TestTreeDestroyNULL:",(SUCCEDD == res) ? "succedded" : "failed");

	res = TestTreeDoubleDestroy();
	printf("\n%-40s \t %s \n", "TestTreeDoubleDestroy:",(SUCCEDD == res) ? "succedded" : "failed");

	/*Insert data*/
	/*POS*/
	res = TestTreeInsert_Valid();
	printf("\n%-40s \t %s \n", "TestTreeInsert_Valid:",(SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestTreeInsert_Duplicate();
	printf("\n%-40s \t %s \n", "TestTreeInsert_Duplicate:",(SUCCEDD == res) ? "succedded" : "failed");

	res = TestTreeInsert_NULL();
	printf("\n%-40s \t %s \n", "TestTreeInsert_NULL:",(SUCCEDD == res) ? "succedded" : "failed");

	/*found data*/
	/*POS*/
	res = TestTreeIsDataFound_Exist();
	printf("\n%-40s \t %s \n", "TestTreeIsDataFound_Exist:",(SUCCEDD == res) ? "succedded" : "failed");

	res = TestTreeIsDataFound_NotExist();
	printf("\n%-40s \t %s \n" ,"TestTreeIsDataFound_NotExist:",(SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestTreeInsert_NULL();
	printf("\n%-40s \t %s \n", "TestTreeInsert_NULL:",(SUCCEDD == res) ? "succedded" : "failed");


	return 0;
}
