#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

#define MEMORY_SIZE 1000
#define SMALL_MEMORY_SIZE 11

typedef enum
{
	SUCCEDD,
	FAILED
}Result;


/* MALLOC INIT */

Result TestMyMallocInit_Valid()
{
	void *memory = malloc(MEMORY_SIZE);
	if(!memory)
	{
		return FAILED;
	}
	
	MyMallocInit(memory,MEMORY_SIZE);
	
	if(MEMORY_SIZE != ((int*)memory)[0] || (MEMORY_SIZE - INIT_PLACES*sizeof(int)) != ((int*)memory)[1])
	{
		free(memory);
		return FAILED;
	}

	free(memory);
	return SUCCEDD;
}

Result TestMyMallocInit_SmallSize()
{
	void *memory = malloc(SIZE_OF_INIT-1);
	if(!memory)
	{
		return FAILED;
	}
	
	MyMallocInit(memory,SIZE_OF_INIT-1);
	
	if((SIZE_OF_INIT-1) != ((int*)memory)[0])
	{
		free(memory);
		return SUCCEDD;
	}

	free(memory);
	return FAILED;
}

Result TestMyMallocInit_NULL()
{
	void *memory = malloc(MEMORY_SIZE);
	if(!memory)
	{
		return FAILED;
	}
	
	MyMallocInit(NULL,MEMORY_SIZE);
	
	if(MEMORY_SIZE != ((int*)memory)[0])
	{
		free(memory);
		return SUCCEDD;
	}

	free(memory);
	return FAILED;
}

/* MALLOC */

Result TestMyMalloc_ValidOne()
{
	void *firstMalloc;
	void *memory = malloc(MEMORY_SIZE);
	if(!memory)
	{
		return FAILED;
	}
	
	MyMallocInit(memory,MEMORY_SIZE);
	
	if(MEMORY_SIZE != ((int*)memory)[0])
	{
		free(memory);
		return FAILED;
	}
	
	firstMalloc = MyMalloc(memory,10);
	if(!firstMalloc || (MEMORY_SIZE - INIT_PLACES*sizeof(int) - 10) != ((int*)memory)[12])
	{
		free(memory);
		return FAILED;
	}

	free(memory);
	return SUCCEDD;
}

Result TestMyMalloc_ValidTwo()
{
	void *firstMalloc;
	void *memory = malloc(MEMORY_SIZE);
	if(!memory)
	{
		return FAILED;
	}
	
	MyMallocInit(memory,MEMORY_SIZE);
	
	if(MEMORY_SIZE != ((int*)memory)[0])
	{
		free(memory);
		return FAILED;
	}
	
	firstMalloc = MyMalloc(memory,10);
	if(!firstMalloc || (MEMORY_SIZE - INIT_PLACES*sizeof(int) - 10) != ((int*)memory)[12])
	{
		free(memory);
		return FAILED;
	}
	
	firstMalloc = MyMalloc(memory,16);
	if(!firstMalloc || (MEMORY_SIZE - INIT_PLACES*sizeof(int) - 26) != ((int*)memory)[29])
	{
		free(memory);
		return FAILED;
	}

	free(memory);
	return SUCCEDD;
}

Result TestMyMalloc_AllocFails()
{
	int i = 5, count = 0, j = 2;
	void *firstMalloc, *memory = malloc(MEMORY_SIZE);
	
	if(!memory)
	{
		return FAILED;
	}
	
	MyMallocInit(memory,MEMORY_SIZE);
	
	if(MEMORY_SIZE != ((int*)memory)[0])
	{
		free(memory);
		return FAILED;
	}
	
	firstMalloc = MyMalloc(memory,i);
	
	while(firstMalloc && (int)(MEMORY_SIZE - INIT_PLACES*sizeof(int) - (i+count)) == ((int*)memory)[i+count+j])
	{
		if(i > MEMORY_SIZE)
		{
			free(memory);
			return FAILED;
		}
		
		count += i;
		i += 5;
		++j;
		
		firstMalloc = MyMalloc(memory,i);
	}
	
	if(!firstMalloc)
	{
		free(memory);
		return SUCCEDD;
	}
	
	free(memory);
	return FAILED;
}

Result TestMyMalloc_NULL()
{

	if(!MyMalloc(NULL,10))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* FREE */

Result TestMyFree_ValidOne()
{
	void *firstMalloc;
	void *memory = malloc(MEMORY_SIZE);
	if(!memory)
	{
		return FAILED;
	}
	
	MyMallocInit(memory,MEMORY_SIZE);
	
	if(MEMORY_SIZE != ((int*)memory)[0])
	{
		free(memory);
		return FAILED;
	}
	
	firstMalloc = MyMalloc(memory,10);
	if(!firstMalloc || (MEMORY_SIZE - INIT_PLACES*sizeof(int) - 10) != ((int*)memory)[12])
	{
		free(memory);
		return FAILED;
	}
	
	MyFree(firstMalloc);
	if(firstMalloc || 0 > ((int*)memory)[2])
	{
		free(memory);
		return FAILED;
	}

	free(memory);
	return SUCCEDD;
}

Result TestMyFree_ValidInMiddle()
{
	void *firstMalloc, *MiddleMalloc;
	void *memory = malloc(MEMORY_SIZE);
	if(!memory)
	{
		return FAILED;
	}
	
	MyMallocInit(memory,MEMORY_SIZE);
	
	if(MEMORY_SIZE != ((int*)memory)[0])
	{
		free(memory);
		return FAILED;
	}
	
	firstMalloc = MyMalloc(memory,10);
	if(!firstMalloc || (MEMORY_SIZE - INIT_PLACES*sizeof(int) - 10) != ((int*)memory)[12])
	{
		free(memory);
		return FAILED;
	}
	
	MiddleMalloc = MyMalloc(memory,16);
	if(!MiddleMalloc || (MEMORY_SIZE - INIT_PLACES*sizeof(int) - 26) != ((int*)memory)[29])
	{
		free(memory);
		return FAILED;
	}
	
	firstMalloc = MyMalloc(memory,5);
	if(!firstMalloc || (MEMORY_SIZE - INIT_PLACES*sizeof(int) - 31) != ((int*)memory)[35])
	{
		free(memory);
		return FAILED;
	}
	
	MyFree(MiddleMalloc);
	
	if(MiddleMalloc || 0 > ((int*)memory)[12])
	{
		free(memory);
		return FAILED;
	}

	free(memory);
	return SUCCEDD;
}

Result TestMyFree_NULL()
{
	void *firstMalloc;
	void *memory = malloc(MEMORY_SIZE);
	if(!memory)
	{
		return FAILED;
	}
	
	MyMallocInit(memory,MEMORY_SIZE);
	
	if(MEMORY_SIZE != ((int*)memory)[0])
	{
		free(memory);
		return FAILED;
	}
	
	firstMalloc = MyMalloc(memory,10);
	if(!firstMalloc || (MEMORY_SIZE - INIT_PLACES*sizeof(int) - 10) != ((int*)memory)[12])
	{
		free(memory);
		return FAILED;
	}
	
	MyFree(NULL);
	if(!firstMalloc || (MEMORY_SIZE - INIT_PLACES*sizeof(int) - 10) != ((int*)memory)[12])
	{
		free(memory);
		return FAILED;
	}

	free(memory);
	return SUCCEDD;
}





static void PrintRes(char *_str, Result(*ptrPrint)(void))
{
	static int count = 0;
	++count;
	
	printf("\n%d. %-40s \t %s \n", count, _str, (SUCCEDD == (*ptrPrint)()) ? "succedded" : "failed");
}

int main()
{

	/*Malloc init*/
	/*POS*/
	printf("\n--- Malloc init: ---\n");
	PrintRes("TestMyMallocInit_Valid:",TestMyMallocInit_Valid);
	/*NEG*/
	PrintRes("TestMyMallocInit_SmallSize:",TestMyMallocInit_SmallSize);
	PrintRes("TestMyMallocInit_NULL:",TestMyMallocInit_NULL);

	/*Malloc*/
	/*POS*/
	printf("\n--- Malloc: ---\n");
	PrintRes("TestMyMalloc_ValidOne:",TestMyMalloc_ValidOne);
	PrintRes("TestMyMalloc_ValidTwo:",TestMyMalloc_ValidTwo);
	/*NEG*/
	PrintRes("TestMyMalloc_AllocFails:",TestMyMalloc_AllocFails);
	PrintRes("TestMyMalloc_NULL:",TestMyMalloc_NULL);

	/*Malloc*/
	/*POS*/
	printf("\n--- Malloc: ---\n");
	PrintRes("TestMyFree_ValidOne:",TestMyFree_ValidOne);
	PrintRes("TestMyFree_ValidInMiddle:",TestMyFree_ValidInMiddle);
	/*NEG*/
	PrintRes("TestMyFree_NULL:",TestMyFree_NULL);


	return 0;
}








