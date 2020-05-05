#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void BubbleSort(int (*ifToSwap)(int,int), int *_arr, int _size);

#define SIZE 10

static int ByBigger(int _a, int _b)
{
	return (_a > _b);
}

static int BySmaller(int _a, int _b)
{
	return (_a < _b);
}

static int ByEven(int _a, int _b)
{
	return ((0 != _a % 2) && (0 == _b % 2));
}

static int ByUnits(int _a, int _b)
{
	return (_a % 10 > _b % 10);
}

static void FillArrayRand(int *_arr, int _size)
{
	int i;
	time_t t;
	srand((unsigned)time(&t));

	for(i = 0;i < _size;++i)
	{
		_arr[i] = 1 + rand()%100;
	}
}

static void PrintArr(int *_arr, int _size)
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
	int arr[SIZE], i;
	int(*IfToSwap[])(int,int) =
	{
		ByBigger,
		BySmaller,
		ByEven,
		ByUnits
	};

	for(i = 0;i < 4;++i)
	{
		FillArrayRand(arr,SIZE);
		PrintArr(arr,SIZE);
		BubbleSort(IfToSwap[i],arr,SIZE);
		PrintArr(arr,SIZE);
		printf("\n");
	}
	

	return 0;
}










