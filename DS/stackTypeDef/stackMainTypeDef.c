#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "ADTErrors.h"

enum
{
	CREATE_STACK = 1,
	INSERT_DATA,
	REMOVE_DATA,
	GET_SIZE,
	IS_EMPTY,
	PRINT,
	DESTROY,
	EXIT
};

void GetInitValues(size_t *_initialSize, size_t *_BlockSize)
{
	printf("Please enter the initial size:");
	scanf("%lu",_initialSize);
	printf("Please enter the incremet block size:");
	scanf("%lu",_BlockSize);	
	getchar();
}

int main()
{
	Stack *stack = NULL;
	int action, NewData, isEmpty;
	size_t initialSize, BlockSize, numOfElements;
	ErrCode err;

	do
	{
		printf("\nPlease select an action by pressing the suitable button: \n1 - for creating dynamic stack.\n");
		printf("2 - for inserting a new data to the stack.\n3 - for removing the last data from the stack. \n");
		printf("4 - for get the number of elements in the stack.\n5 - for checking if the stack is empty \n");
		printf("6 - for printing the stack \n7 - for destroying the dynamic stack \n");
		printf("8 - for exit.\n");

		scanf("%d", &action);


		switch (action)
		{
			case CREATE_STACK:
				
				GetInitValues(&initialSize,&BlockSize);

				stack = StackCreate(initialSize,BlockSize);

				if(NULL == stack)
				{
					printf("\nMemory overflow or Illegal input in initial size or in incremet block size\n");
					break;
				}

				printf("\nstack created!\n");
				break;

			case INSERT_DATA:

				printf("\nPlease insert new data:");
				scanf("%d",&NewData);

				err = StackPush(stack,NewData);

				switch (err)
				{
					case ERR_NOT_EXIST:

						printf("\nstack not exist!\n");
						break;

					case ERR_OVERFLOW:

						printf("\nMemory overflow!\n");
						break;

					case ERR_ILLEGAL_INPUT:

						printf("\nIllegal data input!\n");
						break;

					default:

						printf("\nData added to the vector!\n");
						break;
				}


				break;

			case REMOVE_DATA:

				err = StackPop(stack,&NewData);

				switch (err)
				{
					case ERR_NOT_EXIST:

						printf("\nstack not exist or stack is empty!\n");
						break;

					case ERR_OVERFLOW:

						printf("\nMemory overflow!\n");
						break;

					default:

						printf("\nData %d removed!\n", NewData);
						break;
				}

				break;

			case GET_SIZE:

				numOfElements = StackNumOfelements(stack);

				if(0 == numOfElements)
				{
					printf("\nstack if empty or not exist!\n");
					break;
				}

				printf("\nnumber of elements in the stack is %ld \n",numOfElements);

				break;

			case IS_EMPTY:

				isEmpty = StackIsEmpty(stack);

				if(true == isEmpty)
				{
					printf("\nstack is empty or isn't exist!\n");
					break;
				}
	
				printf("\nstack is not empty!\n");

				break;

			case PRINT:

				err = PrintStack(stack);
	
				if(ERR_NOT_EXIST == err)
				{
					printf("\nstack not exist!\n");
				}

				break;

			case DESTROY:

				StackDestroy(stack);
				stack = NULL;

				printf("\nstack destroyed!\n");

				break;


			case EXIT:

				StackDestroy(stack);
				stack = NULL;

				printf("\nbye byeee :) \n");

				break;

			default:

				printf("you press a wrong button!");

				break;
				
		}





	}while(EXIT != action);

	return 0;
}
