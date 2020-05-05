#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArrayPointerExercise.h"

#define LENGTH 10

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

/* BINARY SEARCH */

Result TestBinarySearch_Valid()
{
	int arr[] = {2,5,7,12,25,30,34,39,47,52};

	if(4 != BinarySearch(arr,sizeof(arr)/sizeof(int),25))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestBinarySearch_ValidOne()
{
	int arr[] = {2};

	if(0 != BinarySearch(arr,sizeof(arr)/sizeof(int),2))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestBinarySearch_OneNotExist()
{
	int arr[] = {2};

	if(-1 == BinarySearch(arr,sizeof(arr)/sizeof(int),25))
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestBinarySearch_NotExistBig()
{
	int arr[] = {2,5,7,12,25,30,34,39,47,52};

	if(-1 == BinarySearch(arr,sizeof(arr)/sizeof(int),55))
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestBinarySearch_NotExistSmall()
{
	int arr[] = {2,5,7,12,25,30,34,39,47,52};

	if(-1 == BinarySearch(arr,sizeof(arr)/sizeof(int),0))
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestBinarySearch_NotExistMiddle()
{
	int arr[] = {2,5,7,12,25,30,34,39,47,52};

	if(-1 == BinarySearch(arr,sizeof(arr)/sizeof(int),32))
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestBinarySearch_NULLArray()
{

	if(-1 == BinarySearch(NULL,LENGTH,32))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* LOTTO */

static void PrintArray(int *_arr, int _size)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		printf("%d ",_arr[i]);
	}

	printf("\n");
}

static int IsExist(int *_arr, int _size, int _element)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		if(_arr[i] == _element)
		{
			return 1;
		}
	}

	return 0;
}

static void FillArrayRand(int *_arr, int _size)
{
	int i = 0, temp;
	time_t t;
	srand((unsigned)time(&t));

	while(i < _size)
	{
		if(!IsExist(_arr,_size,(temp = 1 + rand()%50)))
		{
			_arr[i] = temp;
			++i;
		}
	}
}

Result TestLotto_NULLArray()
{
	
	if(ERR_NOT_INITIALIZE == Lotto(NULL))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

Result TestLotto_NotValidSmall()
{
	int arr[LOTTO_LENGTH] = {4,12,45,0,30,29};

	if(ERR_ILLEGAL_INPUT == Lotto(arr))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

Result TestLotto_NotValidBig()
{
	int arr[LOTTO_LENGTH] = {4,12,45,50,30,29};

	if(ERR_ILLEGAL_INPUT == Lotto(arr))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

Result TestLotto_EmptyArray()
{
	int arr[LOTTO_LENGTH];

	if(ERR_ILLEGAL_INPUT == Lotto(arr))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

Result TestLotto_NotValidDoubleVal()
{
	int arr[LOTTO_LENGTH] = {4,12,45,50,30,45};

	if(ERR_ILLEGAL_INPUT == Lotto(arr))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

int main()
{
	Result res;
	int arr[LOTTO_LENGTH];

	/*Binary search*/
	/*POS*/
	res = TestBinarySearch_Valid();
	printf("\n%-40s %s \n", "TestBinarySearch_Valid: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestBinarySearch_ValidOne();
	printf("\n%-40s %s \n", "TestBinarySearch_ValidOne: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	/*NEG*/
	res = TestBinarySearch_OneNotExist();
	printf("\n%-40s %s \n", "TestBinarySearch_OneNotExist: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestBinarySearch_NotExistBig();
	printf("\n%-40s %s \n", "TestBinarySearch_NotExistBig: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	res = TestBinarySearch_NotExistSmall();
	printf("\n%-40s %s \n", "TestBinarySearch_NotExistSmall: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestBinarySearch_NotExistMiddle();
	printf("\n%-40s %s \n", "TestBinarySearch_NotExistMiddle: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestBinarySearch_NULLArray();
	printf("\n%-40s %s \n", "TestBinarySearch_NULLArray: ", (SUCCEDD == res) ? "succedded" : "failed");

	/*Binary search*/
	/*NEG*/
	res = TestLotto_NULLArray();
	printf("\n%-40s %s \n", "TestLotto_NULLArray: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestLotto_EmptyArray();
	printf("\n%-40s %s \n", "TestLotto_EmptyArray: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	res = TestLotto_NotValidSmall();
	printf("\n%-40s %s \n", "TestLotto_NotValidSmall: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestLotto_NotValidBig();
	printf("\n%-40s %s \n", "TestLotto_NotValidBig: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestLotto_NotValidDoubleVal();
	printf("\n%-40s %s \n", "TestLotto_NotValidDoubleVal: ", (SUCCEDD == res) ? "succedded" : "failed");

	/*POS*/
	FillArrayRand(arr,LOTTO_LENGTH);
	PrintArray(arr,LOTTO_LENGTH);
	Lotto(arr);


	return 0;
}










