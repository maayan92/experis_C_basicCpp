#include <stdio.h>
#include "doubleLinkedList.h"

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

/* CREATE LIST */

Result TestDLListCreate()
{
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	return SUCCEDD;
}

/* DESTROY LIST */

Result TestDLListDestroy()
{
	 List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}
	
	DLListDestroy(list);

	return SUCCEDD;
}

Result TestDLListDestroyNULL()
{
	DLListDestroy(NULL);

	return SUCCEDD;
}

Result TestDLListDoubleDestroy()
{
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	DLListDestroy(list);
	DLListDestroy(list);

	return SUCCEDD;
}

/* ADD TO HEAD */

Result TestDLListPushHeadValidOne()
{
	List *list = DLListCreate();
	int dataH;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,5))
	{	
		DLListDestroy(list);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopHead(list,&dataH) || dataH != 5)
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListPushHeadValid()
{
	List *list = DLListCreate();
	int i, dataH;

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < 4;++i)
	{
		if(SUCCEEDED != DLListPushHead(list,i))
		{	
			DLListDestroy(list);
			return FAILED;
		}
	}

	for(i = 3;i >= 0;--i)
	{
		if(SUCCEEDED != DLListPopHead(list,&dataH) || dataH != i)
		{
			DLListDestroy(list);
			return FAILED;
		}
	}	
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListPushHead_NULLList()
{
	if(ERR_NOT_INITIALIZE == DLListPushHead(NULL,1))
	{	
		return SUCCEDD;
	}

	return FAILED;
}

/* ADD TO TAIL */

Result TestDLListPushTailValidOne()
{
	List *list = DLListCreate();
	int dataT;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushTail(list,5))
	{	
		DLListDestroy(list);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopTail(list,&dataT) || dataT != 5)
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListPushTailValid()
{
	List *list = DLListCreate();
	int i, dataT;

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < 4;++i)
	{
		if(SUCCEEDED != DLListPushTail(list,i))
		{	
			DLListDestroy(list);
			return FAILED;
		}
	}

	for(i = 3;i >= 0;--i)
	{
		if(SUCCEEDED != DLListPopTail(list,&dataT) || dataT != i)
		{
			DLListDestroy(list);
			return FAILED;
		}
	}
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListPushTail_NULLList()
{
	if(ERR_NOT_INITIALIZE == DLListPushTail(NULL,1))
	{	
		return SUCCEDD;
	}

	return FAILED;
}

/* REMOVE FROM HEAD */

Result TestDLListPopHeadValidOne()
{
	List *list = DLListCreate();
	int dataH;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushTail(list,5))
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopHead(list,&dataH) || dataH != 5)
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListPopHeadValid()
{
	List *list = DLListCreate();
	int i, dataH;

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < 4;++i)
	{
		if(SUCCEEDED != DLListPushTail(list,i))
		{
			DLListDestroy(list);
			return FAILED;
		}
	}

	for(i = 0;i < 4;++i)
	{
		if(SUCCEEDED != DLListPopHead(list,&dataH) || dataH != i)
		{
			DLListDestroy(list);
			return FAILED;
		}
	}
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListPopHead_NULLList()
{
	int data;
	if(ERR_NOT_INITIALIZE == DLListPopHead(NULL,&data))
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

	if(ERR_UNDERFLOW == DLListPopHead(list,&data))
	{	
		return SUCCEDD;
	}

	DLListDestroy(list);
	return FAILED;
}

Result TestDLListPopHead_NULLPointer()
{
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushTail(list,5))
	{
		DLListDestroy(list);
		return FAILED;
	}

	if(ERR_NOT_INITIALIZE == DLListPopHead(list,NULL))
	{	
		return SUCCEDD;
	}

	DLListDestroy(list);
	return FAILED;
}

/* REMOVE FROM TAIL */

Result TestDLListPopTailValidOne()
{
	List *list = DLListCreate();
	int dataT;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,5))
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	if(SUCCEEDED != DLListPopTail(list,&dataT) || dataT != 5)
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListPopTailValid()
{
	List *list = DLListCreate();
	int i, dataT;

	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < 4;++i)
	{
		if(SUCCEEDED != DLListPushHead(list,i))
		{
			DLListDestroy(list);
			return FAILED;
		}
		
	}

	for(i = 0;i < 4;++i)
	{
		if(SUCCEEDED != DLListPopTail(list,&dataT) || dataT != i)
		{
			DLListDestroy(list);
			return FAILED;
		}
	}
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListPopTail_NULLList()
{
	int data;
	if(ERR_NOT_INITIALIZE == DLListPopTail(NULL,&data))
	{	
		return SUCCEDD;
	}

	return FAILED;
}

Result TestDLListPopTail_EmptyList()
{
	int data;
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}

	if(ERR_UNDERFLOW == DLListPopTail(list,&data))
	{	
		return SUCCEDD;
	}

	DLListDestroy(list);
	return FAILED;
}

Result TestDLListPopTail_NULLPointer()
{
	List *list = DLListCreate();
	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushTail(list,5))
	{
		DLListDestroy(list);
		return FAILED;
	}

	if(ERR_NOT_INITIALIZE == DLListPopTail(list,NULL))
	{	
		return SUCCEDD;
	}

	DLListDestroy(list);
	return FAILED;
}

/* COUNT ITEMS */

Result TestDLListCountItems()
{
	List *list = DLListCreate();
	int i;
	
	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < 4;++i)
	{
		if(SUCCEEDED != DLListPushHead(list,i))
		{
			DLListDestroy(list);	
			return FAILED;
		}
	}

	if(i != DLListCountItems(list))
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	DLListDestroy(list);
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
		DLListDestroy(list);
		return SUCCEDD;
	}
	
	DLListDestroy(list);
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

Result TestDLListIsEmpty0()
{
	List *list = DLListCreate();
	int i;
	
	if(NULL == list)
	{
		return FAILED;
	}

	for(i = 0;i < 2;++i)
	{
		if(SUCCEEDED != DLListPushHead(list,i))
		{
			DLListDestroy(list);	
			return FAILED;
		}
	}

	if(DLListIsEmpty(list))
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListIsEmptyN()
{
	List *list = DLListCreate();

	if(NULL == list)
	{
		return FAILED;
	}

	if(!DLListIsEmpty(list))
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	DLListDestroy(list);
	return SUCCEDD;
}

Result TestDLListIsEmpty_InsertRemove()
{
	List *list = DLListCreate();
	int data;

	if(NULL == list)
	{
		return FAILED;
	}

	if(SUCCEEDED != DLListPushHead(list,1))
	{
		DLListDestroy(list);	
		return FAILED;
	}

	if(SUCCEEDED != DLListPopTail(list,&data) || data != 1)
	{
		DLListDestroy(list);
		return FAILED;
	}
	
	if(!DLListIsEmpty(list))
	{
		DLListDestroy(list);
		return FAILED;
	}

	DLListDestroy(list);
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

int main()
{
	Result res;
	
	/*Create list*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestDLListCreate:",(SUCCEDD == TestDLListCreate()) ? "succedded" : "failed");

	/*Destroy list*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestDLListDestroy:",(SUCCEDD == TestDLListDestroy()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n" ,"TestDLListDestroyNULL:",(SUCCEDD == TestDLListDestroyNULL()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestDLListDoubleDestroy:",(SUCCEDD == TestDLListDoubleDestroy()) ? "succedded" : "failed");

	/*Insert head*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestDLListPushHeadValidOne:",(SUCCEDD == TestDLListPushHeadValidOne()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestDLListPushHeadValid:",(SUCCEDD == TestDLListPushHeadValid()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n", "TestDLListPushHead_NULLList:",(SUCCEDD == TestDLListPushHead_NULLList()) ? "succedded" : "failed");

	/*Insert tail*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestDLListPushTailValidOne:",(SUCCEDD == TestDLListPushTailValidOne()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n" ,"TestDLListPushTailValid:",(SUCCEDD == TestDLListPushTailValid()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n", "TestDLListPushTail_NULLList:",(SUCCEDD == TestDLListPushTail_NULLList()) ? "succedded" : "failed");

	/*Remove head*/
	/*POS*/
	printf("\n%-40s \t %s \n" ,"TestDLListPopHeadValidOne:",(SUCCEDD == TestDLListPopHeadValidOne()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n" ,"TestDLListPopHeadValid:",(SUCCEDD == TestDLListPopHeadValid()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n" ,"TestDLListPopHead_NULLList:",(SUCCEDD == TestDLListPopHead_NULLList()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n" ,"TestDLListPopHead_EmptyList:",(SUCCEDD == TestDLListPopHead_EmptyList()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n" ,"TestDLListPopHead_NULLPointer:",(SUCCEDD == TestDLListPopHead_NULLPointer()) ? "succedded" : "failed");

	/*Remove tail*/
	/*POS*/
	printf("\n%-40s \t %s \n" ,"TestDLListPopTailValidOne:",(SUCCEDD == TestDLListPopTailValidOne()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n" ,"TestDLListPopTailValid:",(SUCCEDD == TestDLListPopTailValid()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n", "TestDLListPopTail_NULLList:",(SUCCEDD == TestDLListPopTail_NULLList()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestDLListPopTail_EmptyList:",(SUCCEDD == TestDLListPopTail_EmptyList()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestDLListPopTail_NULLPointer:",(SUCCEDD == TestDLListPopTail_NULLPointer()) ? "succedded" : "failed");

	/*Count list*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestDLListCountItems:",(SUCCEDD == TestDLListCountItems()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestDLListCountItems0:",(SUCCEDD == TestDLListCountItems0()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n", "TestDLListCountItems_NULLList:",(SUCCEDD == TestDLListCountItems_NULLList()) ? "succedded" : "failed");

	/*Is empty*/
	/*POS*/
	printf("\n%-40s \t %s \n", "TestDLListIsEmpty0:",(SUCCEDD == TestDLListIsEmpty0()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestDLListIsEmptyN:",(SUCCEDD == TestDLListIsEmptyN()) ? "succedded" : "failed");
	printf("\n%-40s \t %s \n", "TestDLListIsEmpty_InsertRemove:",(SUCCEDD == TestDLListIsEmpty_InsertRemove()) ? "succedded" : "failed");

	/*NEG*/
	printf("\n%-40s \t %s \n", "TestDLListIsEmpty_NULLList:",(SUCCEDD == TestDLListIsEmpty_NULLList()) ? "succedded" : "failed");

	return 0;
}


