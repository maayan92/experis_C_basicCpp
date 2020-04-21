#include <stdio.h>
#include <stdlib.h>
#include "dynamicVector.h"

enum
{
	CREATE_VECTOR =  1,
	INSERT_NEW_DATA,
	INSERT_BY_POSITION,
	REMOVE_LAST,
	REMOVE_BY_INDX,
	GET_DATA,
	FIND_POSITION,
	DESTROY_VECTOR,
	PRINT,
	MAX_VAL,
	SORT,
	EXIT
};

void GetInitValues(size_t *_initialSize, size_t *_incremetBlockSize)
{
	printf("Please enter the initial size:");
	scanf("%lu",_initialSize);
	printf("Please enter the incremet block size:");
	scanf("%lu",_incremetBlockSize);	
	getchar();
}

ErrCode MaxVal(Vector *_vec, int *maxVal)
{
	int data, i = 1;
	ErrCode err;
	
	if(SUCCEEDED != (err = VectorGet(_vec,i,&data)))
	{
		return err;
	}
	
	*maxVal = data;

	while(SUCCEEDED == err)
	{
		if(data > *maxVal)
		{
			*maxVal = data;
		}
		
		++i;
		err = VectorGet(_vec,i,&data);
	}

	return SUCCEEDED;
}

static void Swap(Vector *_vec, int _data1,int _data2, int _indx)
{
	VectorSet(_vec,_indx-1,_data2);
	VectorSet(_vec,_indx,_data1);
}

void BubbleSort(Vector *_vec)
{
	int i = 1, j, data1, data2, swapped = 1;
	ErrCode err;

	while(SUCCEEDED == VectorGet(_vec,i,&data1) && swapped)
	{
		j = 2;
		swapped = 0;

		err = VectorGet(_vec,1,&data1);
		err = VectorGet(_vec,j,&data2);

		while(ERR_ILLEGAL_INPUT != err)
		{
			if(data1 > data2)
			{
				Swap(_vec,data1,data2,j);
				swapped = 1;
			}			
			else
			{
				err = VectorGet(_vec,j,&data1);
			}

			++j;
			err = VectorGet(_vec,j,&data2);
		}

		++i;
	}
}

ErrCode RemoveByIndx(Vector *_vec, size_t _position, int *_getNewData)
{
	int setNewData;
	ErrCode err;

	err = VectorGet(_vec,_position,_getNewData);

	if(SUCCEEDED != err)
	{
		return err;
	}

	err = VectorRemoveTail(_vec,&setNewData);

	if(SUCCEEDED != err)
	{
		return err;
	}

	err = VectorSet(_vec,_position,setNewData);

	if(SUCCEEDED != err)
	{
		return err;
	}

	return SUCCEEDED;
}

int main()
{
	size_t initialSize, BlockSize, findPsotion;
	int action, overideVector, getNewData, setNewData, position, maxVal;
	Vector *vector;
	ErrCode err;

	do
	{
		printf("\nPlease select an action by pressing the suitable button: \n1 - for creating dynamic Vector.\n");
		if(NULL != vector)
		{
			printf("2 - for inserting a new data to the vector array.\n3 - for inserting a new data in a specific position.\n");
			printf("4 - for removing the last data from the vector array. \n5 - for removing data by position \n");
			printf("6 - for get data by position from the vector array.\n7 - for finding the position of a specific data \n");
			printf("8 - for destroying the dynamic Vector \n9 - for printing the vector array\n");
			printf("10 - for geting the max value from the Vector \n11 - for sorting the vector array \n");
		}
		printf("12 - for exit.\n");
		scanf("%d",&action);


		switch(action)
		{
			case CREATE_VECTOR:

				if(NULL != vector)
				{
					printf("There is a dynamic Vector exist, if you want to destroy it and create a new one press 1: ");
					scanf("%d",&overideVector);

					if(1 != overideVector)
					{
						break;
					}

					VectorDestroy(vector);
					vector = NULL;
				}

				GetInitValues(&initialSize,&BlockSize);

				vector = VectorCreate(initialSize,BlockSize);

				if(NULL == vector)
				{
					printf("\nMemory overflow or Illegal input in initial size or in incremet block size\n");
					break;
				}
	
				printf("\nVector created!\n");
				break;

			case INSERT_NEW_DATA:

				printf("\nPlease insert new data:");
				scanf("%d",&setNewData);

				err = VectorAddTail(vector,setNewData);

				switch (err)
				{
					case ERR_NOT_INITIALIZE:

						printf("\nVector not exist!\n");
						break;

					case ERR_OVERFLOW:

						printf("\nMemory overflow!\n");
						break;

					case ERR_ILLEGAL_INPUT:

						printf("Illegal data input!");
						break;

					default:

						printf("\nData added to the vector!\n");
						break;
				}

				break;

			case INSERT_BY_POSITION:

				printf("\nPlease insert new data:");
				scanf("%d",&setNewData);

				printf("Please insert data position:");
				scanf("%d",&position);

				err = VectorSet(vector,position,setNewData);

				switch (err)
				{
					case ERR_NOT_INITIALIZE:

						printf("\nVector not exist!\n");
						break;

					case ERR_ILLEGAL_INPUT:

						printf("\nIllegal position input!\n");
						break;

					default:

						printf("\nData added to the vector!\n");
						break;
				}

				break;

			case REMOVE_LAST:
		
				err = VectorRemoveTail(vector,&getNewData);

				switch (err)
				{
					case ERR_NOT_INITIALIZE:

						printf("\nVector not exist or Vector array is empty!\n");
						break;

					case ERR_OVERFLOW:

						printf("\nMemory overflow!\n");
						break;

					default:

						printf("\nData %d removed!\n", getNewData);
						break;
				}

				break;

			case REMOVE_BY_INDX:

				printf("Please insert data position to remove:");
				scanf("%d",&position);
				
				err = RemoveByIndx(vector,position,&getNewData);

				switch (err)
				{

					case ERR_NOT_INITIALIZE:

						printf("\nVector not exist or Vector array is empty!\n");
						break;

					case ERR_OVERFLOW:

						printf("\nMemory overflow!\n");
						break;

					case ERR_FAILED:

						printf("\nReduces the size failed!\n");
						break;

					default:

						printf("\nData %d position %d removed! \n", getNewData, position);
						break;
				}

				break;

			case GET_DATA:

				printf("Please insert data position to remove:");
				scanf("%d",&position);
				
				err = VectorGet(vector,position,&getNewData);

				switch (err)
				{

					case ERR_NOT_INITIALIZE:

						printf("\nVector not exist!\n");
						break;

					case ERR_ILLEGAL_INPUT:

						printf("\nIllegal position input!\n");
						break;

					default:

						printf("\nData position %d is %d \n", position, getNewData);
						break;
				}

				break;

			case FIND_POSITION:

				printf("Please insert data to find:");
				scanf("%d",&setNewData);

				findPsotion = VectorFind(vector,setNewData);

				if(0 == findPsotion)
				{
					printf("\nData not exist or vector not exist!\n");
					break;
				}

				printf("\nData %d is in the position %ld \n", setNewData, findPsotion);
				
				break;

			case DESTROY_VECTOR:

				VectorDestroy(vector);
				vector = NULL;

				printf("\ndynamic vector destroyed! \n");
				
				break;

			case PRINT:

				err = PrintArray(vector);

				if(ERR_NOT_INITIALIZE == err)
				{
					printf("\nVector not exist!\n");
				}

				break;

			case MAX_VAL:

				err = MaxVal(vector,&maxVal);

				switch (err)
				{
					case ERR_NOT_INITIALIZE:

						printf("\nVector not exist or Vector array is empty!\n");
						break;

					case ERR_ILLEGAL_INPUT:

						printf("\nIllegal position input!\n");
						break;

					case ERR_FAILED:

						printf("\nReduces the size failed!\n");
						break;

					default:

						printf("\nmax value is %d \n",maxVal);
						break;
				}

				break;

			case SORT:

				BubbleSort(vector);

				err = PrintArray(vector);

				if(ERR_NOT_INITIALIZE == err)
				{
					printf("\nVector not exist!\n");
				}

				break;

			case EXIT:

				VectorDestroy(vector);
				vector = NULL;

				printf("\nBye Byeeeee :) \n");
				break;

			default:

				printf("\nYou pressed a wrong button!!\n");
				break;
			
		}

		
	}while(EXIT != action);
	
	

	return 0;
}








