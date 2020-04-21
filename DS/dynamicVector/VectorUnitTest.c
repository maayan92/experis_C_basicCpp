#include <stdio.h>
#include "dynamicVector.h"

typedef enum 
{
	SUCCESS,
	FAILED,
	LENGTH = 200
}Result;

Result TestCreateVec_Nsize_Nblock()
{
	Vector *vec = VectorCreate(5,2);

	if(vec)
	{
		VectorDestroy(vec);
		return SUCCESS;
	}

	return FAILED;
}

Result TestCreateVec_size0_block0()
{
	Vector *vec = VectorCreate(0,0);

	if(!vec)
	{
		return SUCCESS;
	}

	return FAILED;
}

Result TestDestroyVec()
{
	Vector *vec = VectorCreate(5,2);
	if(vec)
	{
		VectorDestroy(vec);
		return SUCCESS;
	}

	return FAILED;
}

Result TestDestroyVec_DoubleFree()
{
	Vector *vec = VectorCreate(5,2);
	if(vec)
	{
		VectorDestroy(vec);
		VectorDestroy(vec);

		return SUCCESS;
	}

	return FAILED;
}

Result TestAddToTail_VecExist()
{
	#define INI_SIZE 5
	#define BLK_SIZE 2

	int data, rData, indx;

	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	indx =  INI_SIZE+2*BLK_SIZE;
	while(indx--)
	{
		VectorAddTail(vec,data = rand());

		VectorRemoveTail(vec,&rData);

		if(data != rData)
		{
			VectorDestroy(vec);
			return FAILED;
		}
	}

	return SUCCESS;
}
/*
Result TestRemoveFromTail_VecExist()
{
	#define INI_SIZE 5
	#define BLK_SIZE 2

	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

}
*/

int main()
{
	/*CreateVector:*/
	/*POS*/

	Result res;

	res = TestCreateVec_Nsize_Nblock();
	printf("\nTestCreateVec_Nsize_Nblock result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*NEG*/

	res = TestCreateVec_size0_block0();
	printf("\nTestCreateVec_size0_block0 result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*DestroyVector:*/
	/*POS*/

	res = TestDestroyVec();
	printf("\nTestDestroyVec result: %s \n", (SUCCESS == res) ? "succedded" : "failed");
	
	res = TestDestroyVec_DoubleFree();
	printf("\nTestDestroyVec_DoubleFree result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*AddToTail:*/
	/*POS*/

	res = TestAddToTail_VecExist();
	printf("\nTestAddToTail_VecExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*RemoveFromTail:*/
	/*POS*/
/*	printf("\nTestRemoveFromTail_VecExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");
	if(SUCCESS == TestRemoveFromTail_VecExist())
	{
		printf("succedded \n");
	}
	else
	{
		printf("failed \n");
	}
*/
	
	return 0;
}








