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

static Vector* CreateAndFill()
{
	int i;
	time_t t;

	Vector *vec = VectorCreate(INIT_SIZE,BLOCK_SIZE);
	if(NULL == vec)
	{
		return NULL;
	}

	srand((unsigned)time(&t));

	for(i = 0;i < INIT_SIZE;++i)
	{
		VectorAddTail(vec,rand()%INIT_SIZE);
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

	printf("\n%s \n",_str);

	printf("sort running time: %f seconds\n", (double)(afterTime - beforeTime) / CLOCKS_PER_SEC);

	printf("-> %s \n",(IsSorted(_vec)) ? "sorted" : "not sorted");
}

int main()
{
	Vector *vec1 = CreateAndFill(), *vec2;
	if(NULL == vec1)
	{
		printf("create vector failed!\n");
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

	vec2 = vec1;	

	PrintResult(vec1,BubbleSort,"bubble sort:");

	vec1 = vec2;
	PrintResult(vec1,ShakeSort,"shake sort:");

	vec1 = vec2;
	PrintResult(vec1,QuickSortRec,"quick sort recurtion:");

	vec1 = vec2;
	PrintResult(vec1,QuickSortIter,"quick sort iterative:");
	
	vec1 = vec2;
	PrintResult(vec1,InsertionSort,"insertion sort:");

	vec1 = vec2;
	PrintResult(vec1,ShellSort,"shell sort:");


	VectorDestroy(vec1);
	VectorDestroy(vec2);



	return 0;
}














