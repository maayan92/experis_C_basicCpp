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
	if(FAILED == FillArr(tree,arr,7) || !TreeIsDataFound(tree,1))
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

/* IS FULL */

Result TestIsFullTree_ValidY()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree,arr,7) || !IsFullTree(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestIsFullTree_ValidN()
{
	int arr[] = {5,9,3,2,4,11,7,6};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree,arr,8))
	{
		TreeDestroy(tree);
		return FAILED;
	}

	if(!IsFullTree(tree))
	{
		TreeDestroy(tree);
		return SUCCEDD;
	}
	
	TreeDestroy(tree);
	return FAILED;
}

Result TestIsFullTree_Empty()
{
	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(!IsFullTree(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestIsFullTree_NULL()
{
	if(!IsFullTree(NULL))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* TREE LEVET */

Result TestTreeLevel_Valid()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree,arr,7) || 2 != TreeLevel(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestTreeLevel_BeforeAfterInsert()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree,arr,7) || 2 != TreeLevel(tree) || TreeInsert(tree,7) || 3 != TreeLevel(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}

	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestTreeLevel_Empty()
{
	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(-1 != TreeLevel(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestTreeLevel_NULL()
{
	if(-1 != TreeLevel(NULL))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

/* ARE SIMILAR */

Result TestAreSimilar_Valid()
{
	int arr1[] = {5,9,3,1,4,11,8};
	int arr2[] = {5,9,3,2,4,11,7};

	Tree *tree1 = TreeCreate();
	Tree *tree2 = TreeCreate();
	if(NULL == tree1 || NULL == tree2)
	{
		TreeDestroy(tree1);
		TreeDestroy(tree2);
		return FAILED;
	}

	if(FAILED == FillArr(tree1,arr1,7) || FAILED == FillArr(tree2,arr2,7) || !AreSimilar(tree1,tree2))
	{
		TreeDestroy(tree1);
		TreeDestroy(tree2);
		return FAILED;
	}
	
	TreeDestroy(tree1);
	TreeDestroy(tree2);
	return SUCCEDD;
}

Result TestAreSimilar_Not()
{
	int arr1[] = {5,9,3,1,4,11,8};
	int arr2[] = {5,9,3,2,4,11,7,6,8};

	Tree *tree1 = TreeCreate();
	Tree *tree2 = TreeCreate();
	if(NULL == tree1 || NULL == tree2)
	{
		TreeDestroy(tree1);
		TreeDestroy(tree2);
		return FAILED;
	}

	if(FAILED == FillArr(tree1,arr1,7) || FAILED == FillArr(tree2,arr2,9))
	{
		TreeDestroy(tree1);
		TreeDestroy(tree2);
		return FAILED;
	}

	if(!AreSimilar(tree1,tree2))
	{
		TreeDestroy(tree1);
		TreeDestroy(tree2);
		return SUCCEDD;
	}
	
	TreeDestroy(tree1);
	TreeDestroy(tree2);
	return FAILED;
}

Result TestAreSimilar_Empty()
{
	Tree *tree1 = TreeCreate();
	Tree *tree2 = TreeCreate();
	if(NULL == tree1 || NULL == tree2)
	{
		TreeDestroy(tree1);
		TreeDestroy(tree2);
		return FAILED;
	}

	if(!AreSimilar(tree1,tree2))
	{
		TreeDestroy(tree1);
		TreeDestroy(tree2);
		return FAILED;
	}
	
	TreeDestroy(tree1);
	TreeDestroy(tree2);
	return SUCCEDD;
}

Result TestAreSimilar_NULLFirst()
{
	int arr2[] = {5,9,3,2,4,11,7};

	Tree *tree2 = TreeCreate();
	if(NULL == tree2)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree2,arr2,7))
	{
		TreeDestroy(tree2);
		return FAILED;
	}

	if(!AreSimilar(NULL,tree2))
	{
		TreeDestroy(tree2);
		return SUCCEDD;
	}
	
	TreeDestroy(tree2);
	return SUCCEDD;
}

Result TestAreSimilar_NULLSecond()
{
	int arr1[] = {5,9,3,2,4,11,7};

	Tree *tree1 = TreeCreate();
	if(NULL == tree1)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree1,arr1,7))
	{
		TreeDestroy(tree1);
		return FAILED;
	}

	if(!AreSimilar(tree1,NULL))
	{
		TreeDestroy(tree1);
		return SUCCEDD;
	}
	
	TreeDestroy(tree1);
	return SUCCEDD;
}

/* IS PERFECT */

Result TestIsPerfectTree_Valid()
{
	int arr[] = {5,9,3,1,4,11,8};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree,arr,7) || !IsPerfectTree(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestIsPerfectTree_Not()
{
	int arr[] = {5,9,3,1,4,11};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree,arr,6))
	{
		TreeDestroy(tree);
		return FAILED;
	}

	if(!IsPerfectTree(tree))
	{
		TreeDestroy(tree);
		return SUCCEDD;
	}
	
	TreeDestroy(tree);
	return FAILED;
}

Result TestIsPerfectTree_Empty()
{
	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(!IsPerfectTree(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}
	
	TreeDestroy(tree);
	return SUCCEDD;
}

Result TestIsPerfectTree_NULL()
{
	if(!IsPerfectTree(NULL))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* MIRRO TREE */

Result TestMirrorTree_NULL()
{
	if(ERR_NOT_INITIALIZE == MirrorTree(NULL))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

Result TestMirrorTree_Valid()
{
	int arr[] = {5,9,3,1,4};

	Tree *tree = TreeCreate();
	if(NULL == tree)
	{
		return FAILED;
	}

	if(FAILED == FillArr(tree,arr,5))
	{
		TreeDestroy(tree);
		return FAILED;
	}


	TreePrint(tree,IN_ORDER);
	if(SUCCEEDED != MirrorTree(tree))
	{
		TreeDestroy(tree);
		return FAILED;
	}

	printf("mirror tree:\n");
	TreePrint(tree,IN_ORDER);

	TreeDestroy(tree);
	return SUCCEDD;
}


int main()
{
	Tree *tree;
	int arr[] = {5,9,3,1,4,11,8};
	
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

	/*Is full*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestIsFullTree_ValidY:",(SUCCEDD == TestIsFullTree_ValidY()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n" ,"TestIsFullTree_ValidN:",(SUCCEDD == TestIsFullTree_ValidN()) ? "succedded" : "failed");
	/*NEG*/
	printf("\n%-40s \t %s \n", "TestIsFullTree_Empty:",(SUCCEDD == TestIsFullTree_Empty()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestIsFullTree_NULL:",(SUCCEDD == TestIsFullTree_NULL()) ? "succedded" : "failed");

	/*Tree level*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestTreeLevel_Valid:",(SUCCEDD == TestTreeLevel_Valid()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n" ,"TestTreeLevel_BeforeAfterInsert:",(SUCCEDD == TestTreeLevel_BeforeAfterInsert()) ? "succedded" : "failed");
	/*NEG*/
	printf("\n%-40s \t %s \n", "TestTreeLevel_Empty:",(SUCCEDD == TestTreeLevel_Empty()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestTreeLevel_NULL:",(SUCCEDD == TestTreeLevel_NULL()) ? "succedded" : "failed");

	/*Are similar*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestAreSimilar_Valid:",(SUCCEDD == TestAreSimilar_Valid()) ? "succedded" : "failed");
	/*NEG*/
	printf("\n%-40s \t %s \n", "TestAreSimilar_Not:",(SUCCEDD == TestAreSimilar_Not()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestAreSimilar_Empty:",(SUCCEDD == TestAreSimilar_Empty()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestAreSimilar_NULLFirst:",(SUCCEDD == TestAreSimilar_NULLFirst()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestAreSimilar_NULLSecond:",(SUCCEDD == TestAreSimilar_NULLSecond()) ? "succedded" : "failed");

	/*Is perfect*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestIsPerfectTree_Valid:",(SUCCEDD == TestIsPerfectTree_Valid()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n" ,"TestIsPerfectTree_Not:",(SUCCEDD == TestIsPerfectTree_Not()) ? "succedded" : "failed");
	/*NEG*/
	printf("\n%-40s \t %s \n", "TestIsPerfectTree_Empty:",(SUCCEDD == TestIsPerfectTree_Empty()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestIsPerfectTree_NULL:",(SUCCEDD == TestIsPerfectTree_NULL()) ? "succedded" : "failed");

	/*Mirror tree*/
	/*NEG*/
	printf("\n%-40s \t %s \n", "TestMirrorTree_NULL:",(SUCCEDD == TestMirrorTree_NULL()) ? "succedded" : "failed");

	printf("\n%s\n", "TestMirrorTree_Valid:");
	printf("%58s \n", (SUCCEDD == TestMirrorTree_Valid()) ? "succedded" : "failed");

	/*Print*/
	tree = TreeCreate();	
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

	return 0;
}









