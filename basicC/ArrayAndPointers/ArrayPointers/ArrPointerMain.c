#include <stdio.h>
#include <stdlib.h>
#include "ArrayPointerExercise.h"

enum
{
	AVERAGE = 1,
	MOST_OCCUR,
	NUM_OF_EVEN,
	SORT_ZERO_ONE,
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

int main()
{
	int size, action, element, binarySearch;
	int *arr;
	
	do
	{
		printf("\nPlease select the action you want to do:\n");
		printf("1 - for average of array \n2 - for the most occur element in the array \n");
		printf("3 - for number of even elements in the array \n4 - for sorting array of zero and one \n");
		printf("or any other button to exit\n");
		scanf("%d", &action);

		switch (action)
		{
			case AVERAGE:

				printf("\nPlease enter array size:");
				scanf("%d",&size);

				printf("Please fill the array\n");

				FillArray(arr,size);

				PrintArray(arr,size);
				printf("Array average is: %f \n",AverageArray(arr,size));

				break;

			case MOST_OCCUR:

				printf("\nPlease enter array size:");
				scanf("%d",&size);
				arr = (int*)calloc(size,sizeof(int));

				printf("Please fill the array\n");

				FillArray(arr,size);

				PrintArray(arr,size);
				printf("The most occur number is %d \n", MostOccur(arr,size));
	
				break;

			case NUM_OF_EVEN:

				printf("\nPlease enter array size:");
				scanf("%d",&size);
				arr = (int*)calloc(size,sizeof(int));

				printf("Please fill the array with even numbers first and then odd\n");

				FillArray(arr,size);

				PrintArray(arr,size);
				printf("Even numbers in the array = %d \n", NumOfEven(arr,size));

				break;
	
			case SORT_ZERO_ONE:

				printf("\nPlease enter array size:");
				scanf("%d",&size);
				arr = (int*)calloc(size,sizeof(int));

				printf("Please fill the array with one and zero only\n");

				FillArray(arr,size);

				PrintArray(arr,size);

				SortOneZero(arr,size);	

				PrintArray(arr,size);

				break;


			default:

				action = EXIT;
				break;

		}
	
	}while(EXIT != action);


	return 0;
}







