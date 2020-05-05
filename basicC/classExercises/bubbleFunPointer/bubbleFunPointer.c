#include <stdio.h>

#define SWAP(a,b) \
	{ \
		int temp = a; \
		a = b; \
		b = temp; \
	}


void BubbleSort(int (*SwapStatus)(int,int), int *_arr, int _size)
{
	register int i, j;
	int swapped = 1;

	for(i = 0;i < _size-1 && swapped;++i)
	{
		swapped = 0;

		for(j = 0;j < _size-i-1;++j)
		{
			if((*SwapStatus)(_arr[j],_arr[j+1]))
			{
				SWAP(_arr[j],_arr[j+1]);
				swapped = 1;
			}
		}
	}
}
