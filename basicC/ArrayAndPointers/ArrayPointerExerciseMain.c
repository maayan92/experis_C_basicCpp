#include <stdio.h>
#include <stdlib.h>
#include "ArrayPointerExercise.h"

enum
{
	BINERY_SEARCH = 1,
	LOTTO,
	EXIT
};

static void FillArray(int * _arr, int _size)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		printf("Please enter number %d:", i+1);
		scanf("%d", &_arr[i]);
	}
}

static void PrintArray(int *_arr, int _size)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		printf("%d ",_arr[i]);
	}

	printf("\n");
}

static void FillArrayRand(int *_arr, int _size)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		_arr[i] = rand()%50;
	}
}

int main()
{
	int size, action, element, binarySearch, *arr;
	ErrCode err;
	
	do
	{
		printf("\nPlease select the action you want to do:\n");
		printf("1 - for binary search \n2 - for the lotto \nor any other button to exit\n");
		scanf("%d", &action);

		switch (action)
		{

			case BINERY_SEARCH:

				printf("\nPlease enter array size:");
				scanf("%d",&size);
				arr = (int*)calloc(size,sizeof(int));

				printf("Please fill sorted array\n");

				FillArray(arr,size);
				printf("Please enter the number you want to search:");
				scanf("%d",&element);

				PrintArray(arr,size);

				binarySearch = BinarySearch(arr,size,element);

				if(-1 == binarySearch)
				{
					printf("%d is not exist in the array", element);
					break;
				}

				printf("The position of %d in the array is %d",element,binarySearch);
				break;

			case LOTTO:

				arr = (int*)calloc(LOTTO_LENGTH,sizeof(int));

				FillArrayRand(arr,LOTTO_LENGTH);

				PrintArray(arr,LOTTO_LENGTH);

				err = Lotto(arr);

				switch(err)
				{
					case ERR_NOT_INITIALIZE:

						printf("\nArray not initialize! \n");
						break;
	
					case ERR_ILLEGAL_INPUT:

						printf("\nIllegal input! \n");
						break;

					default:

						break;
				}

				break;

			default:

				action = EXIT;
				break;

		}
	
	}while(EXIT != action);


	return 0;
}







