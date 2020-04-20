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

size_t GetMaxVal(Vector *_vec, int *maxVal)
{
	int i = 2, data;
	size_t maxValIndx = 1;
	ErrCode err;

	err = VectorGet(_vec,i,&data);

	while(SUCCEEDED == err)
	{
		if(data > *maxVal)
		{
			*maxVal = data;
			maxValIndx = i;
		}
		
		++i;
		err = VectorGet(_vec,i,&data);
	}
	
	return maxValIndx;
}

size_t MaxVal(Vector *_vec, int *maxVal)
{
	int data, i = 1, maxValIndx = 0;
	ErrCode err;
	
	err = VectorGet(_vec,i,&data);

	if(SUCCEEDED == err)
	{
		*maxVal = data;
		maxValIndx = GetMaxVal(_vec, maxVal);
	}

	return maxValIndx;
}

static void Swap(Vector *_vec, int _data1,int _data2, int _indx)
{
	VectorSet(_vec,_indx-1,_data2);
	VectorSet(_vec,_indx,_data1);
}

void BubbleSort(Vector *_vec)
{
	int i = 1, j, data1, data2;
	ErrCode err;

	while(SUCCEEDED == VectorGet(_vec,i,&data1))
	{
		j = 2;

		err = VectorGet(_vec,1,&data1);
		err = VectorGet(_vec,j,&data2);

		while(ERR_ILLEGAL_INPUT != err)
		{
			if(data1 > data2)
			{
				Swap(_vec,data1,data2,j);
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

int main()
{
	size_t initialSize, BlockSize, findPsotion, maxValIndx;
	int action, overideVector, getNewData, setNewData, position, maxVal;
	Vector *vector = NULL;
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
					case ERR_NOT_EXIST:

						printf("\nVector not exist!\n");
						break;

					case ERR_OVERFLOW:

						printf("\nMemory overflow!\n");
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
					case ERR_NOT_EXIST:

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
					case ERR_NOT_EXIST:

						printf("\nVector not exist!\n");
						break;

					case EMPTY_VECTOR_ARR:

						printf("\nVector array is empty!\n");
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
				
				VectorGet(vector,position,&getNewData);
				VectorRemoveTail(vector,&setNewData);
				err = VectorSet(vector,position,setNewData);

				switch (err)
				{

					case ERR_NOT_EXIST:

						printf("\nVector not exist!\n");
						break;

					case EMPTY_VECTOR_ARR:

						printf("\nVector array is empty!\n");
						break;

					case ERR_OVERFLOW:

						printf("\nMemory overflow!\n");
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

					case ERR_NOT_EXIST:

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

				if(ERR_NOT_EXIST == err)
				{
					printf("\nVector not exist!\n");
				}

				break;

			case MAX_VAL:

				maxValIndx = MaxVal(vector,&maxVal);

				if(0 == maxVal)
				{
					printf("\nIllegal position input!\n");
					break;
				}

				printf("max value is %d in position %ld \n",maxVal,maxValIndx);
				break;

			case SORT:

				BubbleSort(vector);

				err = PrintArray(vector);

				if(ERR_NOT_EXIST == err)
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








