#include <stdio.h>
#include "malloc.h"

void MyMallocInit(void* _memory, size_t _memorySize)
{
	if(!_memory || SIZE_OF_INIT > _memorySize)
	{
		return;
	}

	((int*)_memory)[0] = (int)_memorySize;
	((int*)_memory)[1] = (int)_memorySize - INIT_PLACES*sizeof(int);
	((int*)_memory)[(int)_memorySize - 1] = 0;
}

void* MyMalloc(void* _memory, size_t _requiredBlockSize)
{
	int i = 1;
	
	if(!_memory)
	{
		return NULL;
	}
	
	while(((int*)_memory)[i] != 0)
	{
		if(0 < ((int*)_memory)[i])
		{
			if(((int*)_memory)[i] >= _requiredBlockSize)
			{
				((int*)_memory)[i + _requiredBlockSize + 1] = ((int*)_memory)[i] - _requiredBlockSize;
				((int*)_memory)[i] = (-1)*_requiredBlockSize;
					
				return &(((int*)_memory)[i + _requiredBlockSize]);
			}
			
			i += (((int*)_memory)[i] + 1);
			
		}
		
		else
		{
			i += ((((int*)_memory)[i] * (-1)) + 1);
		}
	}
	
	return NULL;
}

void MyFree(void* _myBlock)
{

	if(!_myBlock || 0 < *(( int*)_myBlock - 1))
	{
		return;
	}

	*((int*)_myBlock - 1) *= (-1);
	
	_myBlock = NULL;
}



