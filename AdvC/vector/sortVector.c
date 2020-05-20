#include <stdio.h>
#include "sortVector.h"

#define SWAP(_vec,_a,_b,_i,_j) { VectorSet(_vec,_j,_a); VectorSet(_vec,_i,_b); }

void PrintElementsInt(void* _data);

static Bool PushBack(Vector *_vec, int _size, Bool(*ptrIfToSwap)(void*,void*))
{
	int j, swapped = false;
	int *data1, *data2;
	
	for(j = 1;j <= _size;++j)
	{
		VectorGet(_vec,j,(void**)&data1);
		VectorGet(_vec,j+1,(void**)&data2);
		
		if((*ptrIfToSwap)(data1,data2))
		{
			SWAP(_vec,data1,data2,j,j+1);
			swapped = true;
		}
	}
	
	return swapped;
}

void BubbleSort(Vector* _vec, Bool(*ptrIfToSwap)(void*,void*))
{
	register int i, size = VectorNumOfelements(_vec);
	
	for(i = 1;i < size;++i)
	{
		if(!PushBack(_vec,size-1,ptrIfToSwap))
		{
			return;
		}
	}
}
