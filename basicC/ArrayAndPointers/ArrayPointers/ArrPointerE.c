#include <stdio.h>

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

double AverageArray(int *_arr, int _size)
{
	int i;
	double sum = 0;

	for(i = 0;i < _size;++i)
	{
		sum += _arr[i];
	}

	return sum/_size;
}

int MostOccur(int *_arr, int _size)
{
	int i, mostOccur = _arr[0], mostTimes = 1, count = 1;

	BubbleSort(_arr,_size);

	for(i = 1;i < _size;++i)
	{
		if(_arr[i-1] == _arr[i])
		{
			count++;
		}
		else if(count > mostTimes)
		{
			mostTimes = count;
			count = 1;
			mostOccur = _arr[i-1];
		}	
	}

	return (count > mostTimes) ? _arr[_size-1] : mostOccur;
}

int NumOfEven(int *_arr, int _size)
{
	int i = 0, count = 0;

	while(0 == _arr[i]%2 && i < _size)
	{
		count++;
		++i;
	}

	return count;
}

void SortOneZero(int *_arr, int _size)
{
	int i = 0, j = _size-1;

	while(i < j)
	{
		if(1 == _arr[i])
		{
			if(0 == _arr[j])
			{
				Swap(&_arr[i],&_arr[j]);
				
				++i;
				--j;
			}
			else
			{
				--j;
			}
		}
		else
		{
			if(1 == _arr[j])
			{
				--j;
			}
			
			++i;
		}
	}
}
