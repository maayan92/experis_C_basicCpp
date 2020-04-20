#include <stdio.h>
#include <stdlib.h>
#include "dynamicVector.h"

enum
{
	CREATE_VECTOR =  1,
	INSERT_NEW_DATA = 2,
	INSERT_BY_POSITION = 3,
	REMOVE_LAST = 4,
	REMOVE_BY_INDX = 5,
	FIND_POSITION = 6,
	DESTROY_VECTOR = 7,
	PRINT = 8,
	EXIT = 9
};

void GetInitValues(size_t *_initialSize, size_t *_incremetBlockSize)
{
	printf("Please enter the initial size:");
	scanf("%lu",_initialSize);
	printf("Please enter the incremet block size:");
	scanf("%lu",_incremetBlockSize);	
	getchar();
}

int main()
{
	size_t initialSize, BlockSize, findPsotion;
	int action, overideVector, newData, position;
	Vector *vector = NULL;
	ErrCode err;

	do
	{
		printf("\nPlease select action: \nfor creating dynamic Vector press 1\n");
		if(NULL != vector)
		{
			printf("for inserting a new data to the vector array press 2 \nfor inserting a new data in a specific position press 3\n");
			printf("for removing the last data from the vector array press 4 \nfor removing data from specific position from the vector array press 5\n");
			printf("for finding the position of a specific data press 6 \nfor destroying the dynamic Vector press 7 \n");
			printf("for printing the vector array press 8\n");
		}
		printf("for exit press 9\n");
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
				scanf("%d",&newData);

				err = VectorAddTail(vector,newData);

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
				scanf("%d",&newData);

				printf("Please insert data position:");
				scanf("%d",&position);

				err = VectorSet(vector,position,newData);

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
				
				err = VectorRemoveTail(vector,&newData);

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

						printf("\nData %d removed!\n", newData);
						break;
				}

				break;

			case REMOVE_BY_INDX:

				printf("Please insert data position to remove:");
				scanf("%d",&position);
				
				err = VectorGet(vector,position,&newData);

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

						printf("\nData %d from position %d removed!\n", newData, position);
						break;
				}

				break;

			case FIND_POSITION:

				printf("Please insert data to find:");
				scanf("%d",&newData);

				findPsotion = VectorFind(vector,newData);

				if(0 == findPsotion)
				{
					printf("\nData not exist or vector not exist!\n");
					break;
				}

				printf("\nData %d is in the position %d \n", newData, position);
				
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








