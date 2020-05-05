#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50000

#define SWAP(a,b) \
	{ \
		int temp = a; \
		a = b; \
		b = temp; \
	}

void Swap(int *_a, int *_b)
{
	int temp = *_a;
	*_a = *_b;
	*_b = temp;
}

void BubbleSort(int *_arr, int _size)
{
	register int i, j;
	int swapped = 1;

	for(i = 0;i < _size-1 && swapped;++i)
	{
		swapped = 0;

		for(j = 0;j < _size-i-1;++j)
		{
			if(_arr[j] > _arr[j+1])
			{
				SWAP(_arr[j],_arr[j+1]);
				swapped = 1;
			}
		}
	}
}

void FillArray(int *_arr, int _size)
{
	int i;
	
	for(i = 0;i < _size;++i)
	{
		_arr[i] = rand()%50000;
	}

}

int checkIfSorted(int *_arr, int _size)
{
	int i;
	
	for(i = 0;i < _size-1;++i)
	{
		if(_arr[i] > _arr[i+1])
		{
			return 0;
		}
	}

	return 1;
}

int main()
{
	int arr[SIZE], isSorted;
	clock_t beforeTime, afterTime;
	double time_spent;

	FillArray(arr,SIZE);

	beforeTime = clock();

	BubbleSort(arr,SIZE);

	afterTime = clock();

	printf("before bubble sort time: %ld \n", beforeTime);
	printf("after bubble sort time: %ld \n", afterTime);

	time_spent = (double)(afterTime - beforeTime) / CLOCKS_PER_SEC;
	printf("difference times: %f\n", time_spent);

	isSorted = checkIfSorted(arr,SIZE);

	printf("%s \n", isSorted ? "sorted" : "not sorted");

	return 0;
}










