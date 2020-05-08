#include <stdio.h>
#include "binaryTree.h"

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

static Result FillArr(Tree *_tree, int *_arr, int _size)
{
	int i;
	ErrCode err;

	for(i = 0;i < _size;++i)
	{
		err = TreeInsert(_tree,_arr[i]);
		if(ERR_NOT_INITIALIZE == err || ERR_OVERFLOW == err)
		{
			return FAILED;
		}
	}
	return SUCCEDD;
}

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
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree);
		return FAILED;
	}		

	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestTreeDestroy_Empty()
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

Result TestTreeInsert_Valid()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}
	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestTreeInsert_Duplicate()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate();	
	if(NULL == tree)
	{
		return FAILED;
	}
	if(FAILED == FillArr(tree,arr,7))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	if(ERR_ILLEGAL_INPUT == TreeInsert(tree,9))
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
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}
	if(FAILED == FillArr(tree,arr,7))
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
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate();	
	if(NULL == tree)
	{
		return FAILED;
	}
	if(FAILED == FillArr(tree,arr,7))
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

Result TestTreeIsDataFound_Empty()
{
	Tree *tree = TreeCreate();	
	if(NULL == tree)
	{
		return FAILED;
	}

	if(!TreeIsDataFound(tree,2))
	{
		return SUCCEDD;
	}
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
	Tree *tree1, *tree2 ;
	int arr1[] = {5,9,3,1,4,11,8};
	int arr2[] = {5,9,3,2,4,11,7,6,8};
	
	/*Create tree*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestTreeCreate:",(SUCCEDD == TestTreeCreate()) ? "succedded" : "failed");

	/*Destroy tree*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestTreeDestroy:",(SUCCEDD == TestTreeDestroy()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestTreeDestroy_Empty:",(SUCCEDD == TestTreeDestroy_Empty()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n" ,"TestTreeDestroyNULL:",(SUCCEDD == TestTreeDestroyNULL()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestTreeDoubleDestroy:",(SUCCEDD == TestTreeDoubleDestroy()) ? "succedded" : "failed");

	/*Insert data*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestTreeInsert_Valid:",(SUCCEDD == TestTreeInsert_Valid()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n", "TestTreeInsert_Duplicate:",(SUCCEDD == TestTreeInsert_Duplicate()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestTreeInsert_NULL:",(SUCCEDD == TestTreeInsert_NULL()) ? "succedded" : "failed");

	/*found data*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestTreeIsDataFound_Exist:",(SUCCEDD == TestTreeIsDataFound_Exist()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n" ,"TestTreeIsDataFound_NotExist:",(SUCCEDD == TestTreeIsDataFound_NotExist()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n", "TestTreeIsDataFound_Empty:",(SUCCEDD == TestTreeIsDataFound_Empty()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestTreeInsert_NULL:",(SUCCEDD == TestTreeInsert_NULL()) ? "succedded" : "failed");

	/*Print*/
	tree1 = TreeCreate();	
	if(NULL == tree1)
	{
		return FAILED;
	}
	tree2 = TreeCreate();	
	if(NULL == tree2)
	{
		return FAILED;
	}

	printf("\ntree level -> %d \n",TreeLevel(tree1));
	printf("is full -> %d \n",IsFullTree(tree1));
	printf("is similar -> %d \n",AreSimilar(tree1,tree2));

	if(SUCCEDD == FillArr(tree1,arr1,7))
	{
		TreePrint(tree1,PRE_ORDER);
		TreePrint(tree1,IN_ORDER);
		TreePrint(tree1,POST_ORDER);
	}
	
	printf("\nis similar -> %d \n",AreSimilar(tree1,tree2));

	if(SUCCEDD == FillArr(tree2,arr2,9))
	{
		TreePrint(tree2,PRE_ORDER);
		TreePrint(tree2,IN_ORDER);
		TreePrint(tree2,POST_ORDER);	
	}

	printf("\ntree level -> %d \n",TreeLevel(tree1));
	printf("is full -> %d \n",IsFullTree(tree1));
	printf("is similar -> %d \n",AreSimilar(tree1,tree2));
	printf("is perfect tree1 -> %d \n",IsPerfectTree(tree1));
	printf("is perfect tree2 -> %d \n",IsPerfectTree(tree2));

	return 0;
}









