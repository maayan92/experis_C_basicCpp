#include <stdio.h>
#include "hash.h"

#define SIZE 10

typedef enum
{
	SUCCEDD,
	FAILED
}Result;


static Result FillHash(Hash *_hash, int *_arr, int _size)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		if(SUCCEEDED != HashInsert(_hash,_arr[i]))
		{
			return FAILED;
		}
	}
	
	return SUCCEDD;
}

static size_t getPosition(int _data)
{
	return (_data*5);
}


/* CREATE HASH */

Result TestHashCreate_Valid()
{
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashCreate_NULLFun()
{
	Hash *hash = HashCreate(SIZE,NULL);
	
	if(NULL == hash)
	{
		return SUCCEDD;
	}
	
	HashDestroy(&hash);
	return FAILED;
}

/* DESTROY HASH */

Result TestHashDestroy_ValidValues()
{
	int arr[] = {5,9,3,1,4,11,8};
	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	if(FAILED == FillHash(hash,arr,7))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	if(SUCCEEDED != HashRemove(hash,4))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashDestroy_Empty()
{
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashDestroy_Double()
{
	Hash *hash = HashCreate(SIZE,getPosition);
	
	if(NULL == hash)
	{
		return FAILED;
	}
	
	HashDestroy(&hash);
	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashDestroy_NULL()
{
	HashDestroy(NULL);

	return SUCCEDD;
}

/* INSERT DATA */

Result TestHashInsert_Valid()
{
	int arr[] = {5,9,3,1,4,11,8};
	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	if(FAILED == FillHash(hash,arr,7))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashInsert_ExistData()
{
	int arr[] = {5,9,3,1,4,11,8};
	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	if(FAILED == FillHash(hash,arr,7))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	if(ERR_EXIST != HashInsert(hash,4))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashInsert_ExistPosition()
{
	int arr[] = {5,9,3,1,4,11,8};
	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	if(FAILED == FillHash(hash,arr,7))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	if(SUCCEEDED != HashInsert(hash,16))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashInsert_Full()
{
	int arr[] = {5,9,3,1,4,11,8,};
	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	if(FAILED == FillHash(hash,arr,7))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	if(SUCCEEDED != HashInsert(hash,16))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashInsert_NULL()
{
	if(ERR_NOT_INITIALIZE == HashInsert(NULL,4))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

/* REMOVE DATA */

Result TestHashRemove_Valid()
{
	int arr[] = {5,9,3,1,4,11,8};
	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	if(FAILED == FillHash(hash,arr,7))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashRemove_Exist()
{
	int arr[] = {5,9,3,1,4,11,8};
	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	if(FAILED == FillHash(hash,arr,7))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	if(ERR_EXIST != HashInsert(hash,4))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	HashDestroy(&hash);
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
	
	/*Create hash*/
	printf("\n--- Create hash: ---\n");
	/*POS*/
	PrintRes("TestHashCreate_Valid:",TestHashCreate_Valid);
	/*NEG*/
	PrintRes("TestHashCreate_NULLFun:",TestHashCreate_NULLFun);

	/*Destroy hash*/
	printf("\n--- Destroy hash: ---\n");
	/*POS*/
	PrintRes("TestHashDestroy_ValidValues:",TestHashDestroy_ValidValues);
	/*NEG*/
	PrintRes("TestHashDestroy_Empty:",TestHashDestroy_Empty);
	PrintRes("TestHashDestroy_Double:",TestHashDestroy_Double);
	PrintRes("TestHashDestroy_NULL:",TestHashDestroy_NULL);

	
	
	
	
	return 0;
}


