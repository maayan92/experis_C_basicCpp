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

Result TestHashDestroy_NULLHash()
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
	
	if(ERR_EXIST == HashInsert(hash,4))
	{
		HashDestroy(&hash);
		return SUCCEDD;
	}
	
	HashDestroy(&hash);
	return FAILED;
}

Result TestHashInsert_Full()
{
	int arr[] = {5,9,3,1,4,11,8,13,6,2};
	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}
	
	if(FAILED == FillHash(hash,arr,SIZE))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	if(ERR_OVERFLOW == HashInsert(hash,16))
	{
		HashDestroy(&hash);
		return SUCCEDD;
	}
	
	HashDestroy(&hash);
	return FAILED;
}

Result TestHashInsert_NULLHash()
{
	if(ERR_NOT_INITIALIZE == HashInsert(NULL,4))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* REMOVE DATA */

Result TestHashRemove_ValidAtPos()
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

Result TestHashRemove_ValidNotAtPos()
{
	int arr[] = {5,9,3,1,4,16,11};
	
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
	
	if(SUCCEEDED != HashRemove(hash,16))
	{
		HashDestroy(&hash);
		return FAILED;
	}
	
	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashRemove_NotExist()
{
	int arr[] = {5,9,3,1,4,16,11};
	
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
	
	if(ERR_NOT_EXIST == HashRemove(hash,8))
	{
		HashDestroy(&hash);
		return SUCCEDD;
	}
	
	HashDestroy(&hash);
	return FAILED;
}

Result TestHashRemove_Empty()
{
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}

	if(ERR_UNDERFLOW == HashRemove(hash,16))
	{
		HashDestroy(&hash);
		return SUCCEDD;
	}
	
	HashDestroy(&hash);
	return FAILED;
}

Result TestHashRemove_NULLHash()
{
	if(ERR_NOT_INITIALIZE == HashRemove(NULL,4))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* IS FOUND DATA */

Result TestHashIsFound_ValidFound()
{
	int arr[] = {5,9,3,1,4,16,11};
	
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
	
	if(!HashIsFound(hash,4))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashIsFound_ValidNotFound()
{
	int arr[] = {5,9,3,1,4,16,11};
	
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
	
	if(!HashIsFound(hash,7))
	{
		HashDestroy(&hash);
		return SUCCEDD;
	}

	HashDestroy(&hash);
	return FAILED;
}

Result TestHashIsFound_Empty()
{
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}

	if(!HashIsFound(hash,7))
	{
		HashDestroy(&hash);
		return SUCCEDD;
	}

	HashDestroy(&hash);
	return FAILED;
}

Result TestHashIsFound_NULLHash()
{
	if(!HashIsFound(NULL,7))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* NUM OF ITEMS */

Result TestHashNumOfItems_Valid()
{
	int arr[] = {5,9,3,1,4,16,11};
	
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
	
	if(7 != HashNumOfItems(hash))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashNumOfItems_Empty()
{	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}

	if(0 != HashNumOfItems(hash))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashNumOfItems_NULLHash()
{
	if(0 == HashNumOfItems(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* CAPACITY (SIZE) */

Result TestHashCapacity_Valid()
{
	int arr[] = {5,9,3,1,4,16,11};
	
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
	
	if(SIZE != HashCapacity(hash))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashCapacity_Empty()
{	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}

	if(SIZE != HashCapacity(hash))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashCapacity_NULLHash()
{
	if(0 == HashCapacity(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* AVG REHASH */

Result TestHashAverageRehashes_Valid()
{
	int arr[] = {5,9,3,1,4,16,11};
	double ans = 0.285714;
	
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
	
	if((int)(ans*100) != (int)(HashAverageRehashes(hash)*100))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashAverageRehashes_Empty()
{	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}

	if(0 != HashAverageRehashes(hash))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashAverageRehashes_NULLHash()
{
	if(0 == HashAverageRehashes(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* MAX REHASH */

Result TestHashMaxReHash_Valid()
{
	int arr[] = {5,9,3,1,4,16,11};
	
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
	
	if(1 != HashMaxReHash(hash))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashMaxReHash_Empty()
{	
	Hash *hash = HashCreate(SIZE,getPosition);
	if(NULL == hash)
	{
		return FAILED;
	}

	if(0 != HashMaxReHash(hash))
	{
		HashDestroy(&hash);
		return FAILED;
	}

	HashDestroy(&hash);
	return SUCCEDD;
}

Result TestHashMaxReHash_NULLHash()
{
	if(0 == HashMaxReHash(NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
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
	PrintRes("TestHashDestroy_NULLHash:",TestHashDestroy_NULLHash);
	
	/*Insert data*/
	printf("\n--- Insert data: ---\n");
	/*POS*/
	PrintRes("TestHashInsert_Valid:",TestHashInsert_Valid);
	PrintRes("TestHashInsert_ExistPosition:",TestHashInsert_ExistPosition);
	/*NEG*/
	PrintRes("TestHashInsert_ExistData:",TestHashDestroy_Empty);
	PrintRes("TestHashInsert_Full:",TestHashInsert_Full);
	PrintRes("TestHashInsert_NULLHash:",TestHashInsert_NULLHash);

	/*Remove data*/
	printf("\n--- Remove data: ---\n");
	/*POS*/
	PrintRes("TestHashRemove_ValidAtPos:",TestHashRemove_ValidAtPos);
	PrintRes("TestHashRemove_ValidNotAtPos:",TestHashRemove_ValidNotAtPos);
	/*NEG*/
	PrintRes("TestHashRemove_NotExist:",TestHashRemove_NotExist);
	PrintRes("TestHashRemove_Empty:",TestHashRemove_Empty);
	PrintRes("TestHashRemove_NULLHash:",TestHashRemove_NULLHash);
	
	/*Is found data*/
	printf("\n--- Is found data: ---\n");
	/*POS*/
	PrintRes("TestHashIsFound_ValidFound:",TestHashIsFound_ValidFound);
	/*NEG*/
	PrintRes("TestHashIsFound_ValidNotFound:",TestHashIsFound_ValidNotFound);
	PrintRes("TestHashIsFound_Empty:",TestHashIsFound_Empty);
	PrintRes("TestHashIsFound_NULLHash:",TestHashIsFound_NULLHash);

	/*Num of items*/
	printf("\n--- Num of items: ---\n");
	/*POS*/
	PrintRes("TestHashNumOfItems_Valid:",TestHashNumOfItems_Valid);
	PrintRes("TestHashNumOfItems_Empty:",TestHashNumOfItems_Empty);
	/*NEG*/
	PrintRes("TestHashNumOfItems_NULLHash:",TestHashNumOfItems_NULLHash);

	/*Capacity*/
	printf("\n--- Capacity: ---\n");
	/*POS*/
	PrintRes("TestHashCapacity_Valid:",TestHashCapacity_Valid);
	PrintRes("TestHashCapacity_Empty:",TestHashCapacity_Empty);
	/*NEG*/
	PrintRes("TestHashCapacity_NULLHash:",TestHashCapacity_NULLHash);
	
	/*Average rehash*/
	printf("\n--- Average rehash: ---\n");
	/*POS*/
	PrintRes("TestHashAverageRehashes_Valid:",TestHashAverageRehashes_Valid);
	PrintRes("TestHashAverageRehashes_Empty:",TestHashAverageRehashes_Empty);
	/*NEG*/
	PrintRes("TestHashAverageRehashes_NULLHash:",TestHashAverageRehashes_NULLHash);
	
	/*Max rehash*/
	printf("\n--- Max rehash: ---\n");
	/*POS*/
	PrintRes("TestHashMaxReHash_Valid:",TestHashMaxReHash_Valid);
	PrintRes("TestHashMaxReHash_Empty:",TestHashMaxReHash_Empty);
	/*NEG*/
	PrintRes("TestHashMaxReHash_NULLHash:",TestHashMaxReHash_NULLHash);
	
	
	
	
	return 0;
}


