#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


typedef enum 
{
	SUCCESS,
	FAILED,
	LENGTH = 200
}Result;

/* CREATE QUEUE */

Result TestCreateCycQue_Nsize()
{
	CyclicQueue *que = QueueCreate(5);

	if(que)
	{
		QueueDestroy(que);
		return SUCCESS;
	}

	return FAILED;
}

Result TestCreateCycQue_size0()
{
	CyclicQueue *que = QueueCreate(0);

	if(!que)
	{
		return SUCCESS;
	}

	return FAILED;
}

Result TestCreateCycQue_sizeHUGE()
{
	CyclicQueue *que = QueueCreate(20000000000);

	if(!que)
	{
		return SUCCESS;
	}

	return FAILED;
}

/* DESTROY QUEUE */

Result TestDestroyCycQue()
{
	CyclicQueue *que = QueueCreate(5);

	if(que)
	{
		QueueDestroy(que);
		return SUCCESS;
	}

	return FAILED;
}

Result TestDestroyCycQue_DoubleFree()
{
	CyclicQueue *que = QueueCreate(5);

	if(que)
	{
		QueueDestroy(que);
		QueueDestroy(que);

		return SUCCESS;
	}

	return FAILED;
}

/* ADD TO QUEUE */

Result TestAddValidAmount_CycQueExist()
{
	#define INI_SIZE 5

	int data, indx;

	CyclicQueue *que = QueueCreate(INI_SIZE);

	if(!que)
	{
		return FAILED;
	}

	indx =  INI_SIZE;
	while(indx--)
	{
		if(SUCCEEDED != QueueEnQueue(que,data = rand()))
		{
			QueueDestroy(que);
			return FAILED;
		}
	}

	QueueDestroy(que);
	return SUCCESS;
}

Result TestAddRemove_CycQueExist()
{
	#define INI_SIZE 5

	int data, rData, indx;

	CyclicQueue *que = QueueCreate(INI_SIZE);

	if(!que)
	{
		return FAILED;
	}

	indx =  INI_SIZE*2;
	while(indx--)
	{
		if(SUCCEEDED != QueueEnQueue(que,data = rand()))
		{
			QueueDestroy(que);
			return FAILED;
		}
		if(SUCCEEDED != QueueDeQueue(que,&rData))
		{
			QueueDestroy(que);
			return FAILED;
		}

		if(rData != data)
		{
			QueueDestroy(que);
			return FAILED;
		}
	}

	QueueDestroy(que);
	return SUCCESS;
}

Result TestAddTooBigAmount_CycQueExist()
{
	#define INI_SIZE 5

	int data, indx;

	CyclicQueue *que = QueueCreate(INI_SIZE);

	if(!que)
	{
		return FAILED;
	}

	indx =  INI_SIZE*2;
	while(indx--)
	{
		if(ERR_OVERFLOW == QueueEnQueue(que,data = rand()))
		{
			QueueDestroy(que);
			return SUCCESS;
		}
	}

	QueueDestroy(que);
	return FAILED;
}

/* REMOVE FROM QUEUE */

Result TestRemoveValidAmount_CycQueExist()
{
	#define INI_SIZE 5

	int data, rData, indx;

	CyclicQueue *que = QueueCreate(INI_SIZE);

	if(!que)
	{
		return FAILED;
	}

	indx =  INI_SIZE*2;
	while(indx--)
	{
		if(SUCCEEDED != QueueEnQueue(que,data = rand()))
		{
			QueueDestroy(que);
			return FAILED;
		}
		
		if(SUCCEEDED != QueueDeQueue(que,&rData))
		{
			QueueDestroy(que);
			return FAILED;
		}

		if(rData != data)
		{
			QueueDestroy(que);
			return FAILED;
		}
	}

	QueueDestroy(que);
	return SUCCESS;
}

Result TestRemoveTooBigAmount_CycQueExist()
{
	#define INI_SIZE 5

	int rData, indx;

	CyclicQueue *que = QueueCreate(INI_SIZE);

	if(!que)
	{
		return FAILED;
	}

	indx =  INI_SIZE*2;
	while(indx--)
	{
		if(ERR_UNDERFLOW == QueueDeQueue(que,&rData))
		{
			QueueDestroy(que);
			return SUCCESS;
		}
	}

	QueueDestroy(que);
	return FAILED;
}

/* NUMBER OF ELEMENTS*/

Result TestNumOfElements_CycQueExist()
{
	#define INI_SIZE 5

	int data, indx;

	CyclicQueue *que = QueueCreate(INI_SIZE);

	if(!que)
	{
		return FAILED;
	}

	indx =  INI_SIZE;
	while(indx--)
	{
		if(SUCCEEDED != QueueEnQueue(que,data = rand()))
		{
			QueueDestroy(que);
			return FAILED;
		}
	}
	
	if(QueueNumOfElements(que) == INI_SIZE)
	{
		QueueDestroy(que);
		return SUCCESS;
	}

	QueueDestroy(que);
	return FAILED;
}

Result TestNumOfElements0_CycQueExist()
{
	#define INI_SIZE 5

	CyclicQueue *que = QueueCreate(INI_SIZE);

	if(!que)
	{
		return FAILED;
	}
	
	if(QueueNumOfElements(que) != INI_SIZE)
	{
		QueueDestroy(que);
		return SUCCESS;
	}

	QueueDestroy(que);
	return FAILED;
}

Result TestIsEmpty_CycQueExist()
{
	#define INI_SIZE 5

	CyclicQueue *que = QueueCreate(INI_SIZE);

	if(!que)
	{
		return FAILED;
	}

	if(QueueIsEmpty(que))
	{
		QueueDestroy(que);
		return SUCCESS;
	}

	return FAILED; 
}

Result TestIsNotEmpty_CycQueExist()
{
	#define INI_SIZE 5

	int data, indx;

	CyclicQueue *que = QueueCreate(INI_SIZE);

	if(!que)
	{
		return FAILED;
	}

	indx =  INI_SIZE;
	while(indx--)
	{
		if(SUCCEEDED != QueueEnQueue(que,data = rand()))
		{
			QueueDestroy(que);
			return FAILED;
		}
	}

	if(QueueIsEmpty(que))
	{
		QueueDestroy(que);
		return FAILED;
	}

	QueueDestroy(que);
	return SUCCESS; 
}

int main()
{
	Result res;

	/*Create Queue*/
	/*POS*/
	res = TestCreateCycQue_Nsize();
	printf("\nTestCreateCycQue_Nsize result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestCreateCycQue_size0();
	printf("\nTestCreateCycQue_size0 result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	res = TestCreateCycQue_sizeHUGE();
	printf("\nTestCreateCycQue_sizeHUGE result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*DestroyVector:*/
	/*POS*/
	res = TestDestroyCycQue();
	printf("\nTestDestroyCycQue result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestDestroyCycQue_DoubleFree();
	printf("\nTestDestroyCycQue_DoubleFree result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*AddToTail:*/
	/*POS*/
	res = TestAddValidAmount_CycQueExist();
	printf("\nTestAddValidAmount_CycQueExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestAddTooBigAmount_CycQueExist();
	printf("\nTestAddTooBigAmount_CycQueExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*RemoveFromTail:*/
	/*POS*/
	res = TestRemoveValidAmount_CycQueExist();
	printf("\nTestRemoveValidAmount_CycQueExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestRemoveTooBigAmount_CycQueExist();
	printf("\nTestRemoveTooBigAmount_CycQueExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*Add&Remove*/
	res = TestAddRemove_CycQueExist();
	printf("\nTestAddRemove_CycQueExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*NumOfElements*/
	/*POS*/
	res = TestNumOfElements_CycQueExist();
	printf("\nTestNumOfElements_CycQueExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestNumOfElements0_CycQueExist();
	printf("\nTestNumOfElements0_CycQueExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");


	/*IsEmpty*/
	/*POS*/
	res = TestIsEmpty_CycQueExist();
	printf("\nTestIsEmpty_CycQueExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestIsNotEmpty_CycQueExist();
	printf("\nTestIsNotEmpty_CycQueExist result: %s \n", (SUCCESS == res) ? "succedded" : "failed");



	return 0;
}







