#include <stdio.h>
#include <time.h>
#include "sortingAlgorithms.h"

#define INIT_SIZE 50000
#define BLOCK_SIZE 3

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

/* BUBBLE SORT */

Result TestBubbleSort_Empty()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}

	if(SUCCEEDED != BubbleSort(vec))
	{
		VectorDestroy(vec);
		return FAILED;
	}

	VectorDestroy(vec);
	return SUCCEDD;
}

Result TestBubbleSort_NULL()
{
	if(ERR_NOT_INITIALIZE == BubbleSort(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* SHAKE SORT */

Result TestShakeSort_Empty()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}

	if(SUCCEEDED != ShakeSort(vec))
	{
		VectorDestroy(vec);
		return FAILED;
	}

	VectorDestroy(vec);
	return SUCCEDD;
}

Result TestShakeSort_NULL()
{
	if(ERR_NOT_INITIALIZE == ShakeSort(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* QUICK SORT RECURTION */

Result TestQuickSortRec_Empty()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}

	if(SUCCEEDED != QuickSortRec(vec))
	{
		VectorDestroy(vec);
		return FAILED;
	}

	VectorDestroy(vec);
	return SUCCEDD;
}

Result TestQuickSortRec_NULL()
{
	if(ERR_NOT_INITIALIZE == QuickSortRec(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* QUICK SORT ITERATIVE */

Result TestQuickSortIter_Empty()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}

	if(SUCCEEDED != QuickSortIter(vec))
	{
		VectorDestroy(vec);
		return FAILED;
	}

	VectorDestroy(vec);
	return SUCCEDD;
}

Result TestQuickSortIter_NULL()
{
	if(ERR_NOT_INITIALIZE == QuickSortIter(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* INSERTION SORT */

Result TestInsertionSort_Empty()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}

	if(SUCCEEDED != InsertionSort(vec))
	{
		VectorDestroy(vec);
		return FAILED;
	}

	VectorDestroy(vec);
	return SUCCEDD;
}

Result TestInsertionSort_NULL()
{
	if(ERR_NOT_INITIALIZE == InsertionSort(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* SHELL SORT */

Result TestShellSort_Empty()
{
	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return FAILED;
	}

	if(SUCCEEDED != ShellSort(vec))
	{
		VectorDestroy(vec);
		return FAILED;
	}

	VectorDestroy(vec);
	return SUCCEDD;
}

Result TestShellSort_NULL()
{
	if(ERR_NOT_INITIALIZE == ShellSort(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

static void Print(char *_str1, Result(*TestFun)(void))
{
	printf("\n%-40s \t %s \n", _str1,(SUCCEDD == (*TestFun)()) ? "succedded" : "failed");
}

static void ReFillVec(Vector *_vec, int *_arr)
{
	int i;

	for(i = 0;i < INIT_SIZE;++i)
	{
		VectorSet(_vec,i+1,_arr[i]);
	}
}

static void FillArr(int *_arr)
{
	int i;
	time_t t;

	srand((unsigned)time(&t));

	for(i = 0;i < INIT_SIZE;++i)
	{
		_arr[i] = rand()%1000;
	}
}

static Vector* CreateAndFill(int *_arr)
{
	int i;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		printf("creation failed!\n");
		return NULL;
	}

	for(i = 0;i < INIT_SIZE;++i)
	{
		VectorAddTail(vec,_arr[i]);
	}

	return vec;
}

static int IsSorted(Vector *_vec)
{
	int i, data1, data2;
	
	for(i = 1;i <= INIT_SIZE;++i)
	{
		VectorGet(_vec,i,&data1);
		VectorGet(_vec,i+1,&data2);

		if(data1 > data2)
		{	
			return 0;
		}
	}

	return 1;
}

static void PrintTime(size_t _afterTime, size_t _beforeTime)
{
	printf("running time: %f seconds\n", (double)(_afterTime - _beforeTime) / CLOCKS_PER_SEC);
} 

static void PrintStr(Vector *_vec, char *_str, size_t _afterTime, size_t _beforeTime)
{
	printf("\n%s \n",_str);

	PrintTime(_afterTime,_beforeTime);

	printf("-> %s \n",(IsSorted(_vec)) ? "sorted" : "not sorted");
}

static void PrintResult(Vector *_vec, ErrCode(*sortFunction)(Vector*), char *_str)
{
	clock_t beforeTime, afterTime;

	beforeTime = clock();

	if(ERR_NOT_INITIALIZE == (*sortFunction)(_vec))
	{
		printf("vector not initialized!\n");
		return;
	}

	afterTime = clock();

	PrintStr(_vec,_str,afterTime,beforeTime);
}

int main()
{
	int *arr, i;
	clock_t beforeTime, afterTime;
	Vector *vec;

	arr = (int*)malloc(INIT_SIZE*sizeof(int));

	if(NULL == arr)
	{
		return 0;
	}

	FillArr(arr);

	if(NULL == (vec = CreateAndFill(arr)))
	{
		return 0;
	}

	/*Bubble sort*/
	/*POS*/
	Print("TestBubbleSort_Empty",TestBubbleSort_Empty);
	/*NEG*/
	Print("TestBubbleSort_NULL",TestBubbleSort_NULL);
	
	/*Shake sort*/
	/*POS*/
	Print("TestShakeSort_Empty",TestShakeSort_Empty);
	/*NEG*/
	Print("TestShakeSort_NULL",TestShakeSort_NULL);

	/*Quick sort recurtion*/
	/*POS*/
	Print("TestQuickSortRec_Empty",TestQuickSortRec_Empty);
	/*NEG*/
	Print("TestQuickSortRec_NULL",TestQuickSortRec_NULL);

	/*Quick sort iterative*/
	/*POS*/
	Print("TestQuickSortIter_Empty",TestQuickSortIter_Empty);
	/*NEG*/
	Print("TestQuickSortIter_NULL",TestQuickSortIter_NULL);

	/*Insertion sort*/
	/*POS*/
	Print("TestInsertionSort_Empty",TestInsertionSort_Empty);
	/*NEG*/
	Print("TestInsertionSort_NULL",TestInsertionSort_NULL);

	/*Shell sort*/
	/*POS*/
	Print("TestShellSort_Empty",TestShellSort_Empty);
	/*NEG*/
	Print("TestShellSort_NULL",TestShellSort_NULL);

	PrintResult(vec,BubbleSort,"bubble sort:");

	ReFillVec(vec,arr);
	PrintResult(vec,ShakeSort,"shake sort:");

	ReFillVec(vec,arr);
	PrintResult(vec,QuickSortRec,"quick sort recurtion:");

	ReFillVec(vec,arr);	
	PrintResult(vec,QuickSortIter,"quick sort iterative:");

	ReFillVec(vec,arr);
	PrintResult(vec,InsertionSort,"insertion sort:");

	ReFillVec(vec,arr);	
	PrintResult(vec,ShellSort,"shell sort:");

	ReFillVec(vec,arr);
	PrintResult(vec,SelectionSort,"Selection sort:");

	ReFillVec(vec,arr);	
	PrintResult(vec,MergeSort,"Merge sort:");

	ReFillVec(vec,arr);	
	beforeTime = clock();
	if(ERR_NOT_INITIALIZE == CountingSort(vec,0,1000))
	{
		printf("vector not initialized!\n");
		return 0;
	}
	afterTime = clock();
	PrintStr(vec,"Counting sort:",afterTime,beforeTime);

	ReFillVec(vec,arr);	
	beforeTime = clock();
	if(ERR_NOT_INITIALIZE == RadixSort(vec,3))
	{
		printf("vector not initialized!\n");
		return 0;
	}
	afterTime = clock();
	PrintStr(vec,"Radix sort:",afterTime,beforeTime);


	printf("\nsearch with no improve\n");
	beforeTime = clock();
	for(i = 0;i < 10000;++i)
	{
		SearchNoImprove(arr,INIT_SIZE,401);
	}
	afterTime = clock();
	PrintTime(afterTime,beforeTime);


	printf("\nsearch with improve\n");
	beforeTime = clock();
	for(i = 0;i < 10000;++i)
	{
		SearchWithImprove(arr,INIT_SIZE,401);
	}
	afterTime = clock();
	PrintTime(afterTime,beforeTime);


	free(arr);
	VectorDestroy(vec);



	return 0;
}














