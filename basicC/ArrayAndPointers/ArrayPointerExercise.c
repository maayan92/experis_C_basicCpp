#include <stdio.h>
#include "ArrayPointerExercise.h"

static void Swap(int *_a, int *_b)
{
	int temp = *_a;
	*_a = *_b;
	*_b = temp;
}

static void PushBack(int *_arr, int _size)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		if(_arr[i] > _arr[i+1])
		{
			Swap(&_arr[i],&_arr[i+1]);
		}
		
	}
}

static void BubbleSort(int *_arr, int _size)
{
	int i;
	
	for(i = 0;i < _size-1;++i)
	{
		PushBack(_arr,_size-i-1);
	}
}

/* BINARY SEARCH */

static int SearchElement(int *_arr, int _size, int _element)
{
	int i, start = 0, end = _size-1;

	while(start <= end)
	{
		i = (start + end)/2;

		if(_element == _arr[i])
		{
			return i;
		}
		if(_element < _arr[i])
		{
			end = i-1;
		}
		else
		{
			start = i+1;
		}
	}

	return -1;
}

int BinarySearch(int *_arr, int _size, int _element)
{
	
	if(NULL == _arr || _element < _arr[0] || _element > _arr[_size-1])
	{
		return -1;
	}

	return SearchElement(_arr,_size,_element);
}

/* LOTTO */

static void PrintRow(int *_arr, int _i, int *_k, int _colNum)
{
	int j, row, column;

	for(j = 1;j <= _colNum;++j)
	{
		row = (_arr[*_k]/10)%10;
		column = _arr[*_k]%10;

		if(column == 0)
		{
			column = 10;
			row--;
		}

		if(_i == row && j == column)
		{
			printf("+ ");
			(*_k)++;
		}
		else
		{
			printf("- ");
		}
	}
}

static void PrintLotto(int *_arr, int _colNum, int _rowNum)
{
	int i, k = 0;

	for(i = 0;i < _rowNum;++i)
	{
		printf("\n%d ", i);
		PrintRow(_arr,i,&k,_colNum);
	}

	printf("\n%d ", i);
	PrintRow(_arr,i,&k,_colNum-1);
	printf("\n");
}

static void PrintFirstLine(int *_arr, int _colNum)
{
	int i;

	printf(" ");

	for(i = 1;i <= _colNum;++i)
	{
		printf(" %d",i);
	}
}

static ErrCode IsValid(int *_arr)
{
	int i;

	if(1 > _arr[0] || 49 < _arr[LOTTO_LENGTH-1])
	{
		return ERR_ILLEGAL_INPUT;
	}

	for(i = 0;i < LOTTO_LENGTH-1;++i)
	{
		if(_arr[i] == _arr[i+1])
		{
			return ERR_ILLEGAL_INPUT;
		}
	}

	return SUCCEEDED;
}

ErrCode Lotto(int *_arr)
{
	int colNum = 10, rowNum = 4;

	if(NULL == _arr)
	{
		return ERR_NOT_INITIALIZE; 
	}

	BubbleSort(_arr,LOTTO_LENGTH);

	if(ERR_ILLEGAL_INPUT == IsValid(_arr))
	{
		return ERR_ILLEGAL_INPUT;
	}

	PrintFirstLine(_arr,colNum);
	
	PrintLotto(_arr,colNum,rowNum);

	return SUCCEEDED;
}






