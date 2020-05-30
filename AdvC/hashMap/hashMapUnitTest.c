#include <stdio.h>
#include <stdlib.h>
#include <string.h>/*TODO temp*/
#include "hashMap.h"

#define SIZE 10
#define ARR_SIZE 8

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

static size_t GetPosition(const void* _key)
{
	size_t num = *(int*)_key;
	
	while((num / 10))
	{
		num /= 10;
	}

	return num;
}

static int CompareKeys(const void* _firstKey, const void* _secondKey)
{
	if(*(int*)_firstKey == *(int*)_secondKey)
	{
		return 1;
	}
	
	return 0;
}

static Result FillHash(HashMap *_hashMap, int *_keys, void** _values, int _size)
{
	int i;

	for(i = 0;i < 8;++i)
	{
		if(SUCCEEDED != HashMapInsert(_hashMap,&_keys[i],&_values[i])) 
		{ 
			return FAILED; 
		}
	}
	
	return SUCCEDD;
}

static int DecreaseMoreThan(const void* _key, void* _value, void* _context)
{
	if(*(int*)_value > *(int*)_context)
	{
		*(int*)_value /= 10;
		
		return 1;
	}
	
	return 0;
}

static int PosOrNeg(const void* _key, void* _value, void* _context)
{
	if((*(int*)_value)*(*(int*)_context) > 0)
	{
		return 1;
	}
	
	return 0;
}

/*
static int PrintKeyValue(const void* _key, void* _value, void* _context)
{
	printf("%d \t", *(int*)_key);
	
	if(NULL != _value)
	{
		printf("%d \t",*(int*)_value);
	}
	
	printf("\n");
	
	return 1;
}
*/

static void DestroyKey(void *_key)
{
	free((int*)_key);
}

static void DestroyValue(void *_value)
{
	free((int*)_value);
}

/* CREATE HASH */

Result TestHashMapCreate_Valid()
{
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashCreate_NULLFunGP()
{
	HashMap *hashMap = HashMapCreate(SIZE,NULL,CompareKeys);
	
	if(NULL == hashMap)
	{
		return SUCCEDD;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}

Result TestHashCreate_NULLFunCK()
{
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,NULL);
	
	if(NULL == hashMap)
	{
		return SUCCEDD;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}

/* DESTROY HASH */

Result TestHashMapDestroy_Valid()
{
	int i, arr[] = {1235,239,1253,261,4,11,1678,249}, *keys[ARR_SIZE], *values[ARR_SIZE];
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}
	
	for(i = 0;i < ARR_SIZE;++i)
	{
		keys[i] = (int*)malloc(sizeof(int));
		values[i] = (int*)malloc(sizeof(int));
		
		*keys[i] = arr[i];
		*values[i] = arr[i];
		
		if(SUCCEEDED != HashMapInsert(hashMap,&keys[i],&values[i])) 
		{
			HashMapDestroy(&hashMap,DestroyKey,DestroyValue);
			return FAILED; 
		}
	}

	HashMapDestroy(&hashMap,DestroyKey,DestroyValue);
	return SUCCEDD;
}

Result TestHashMapDestroy_Double()
{
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}
	
	HashMapDestroy(&hashMap,DestroyKey,DestroyValue);
	HashMapDestroy(&hashMap,DestroyKey,DestroyValue);
	return SUCCEDD;
}

Result TestHashMapDestroy_Empty()
{
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}
	
	HashMapDestroy(&hashMap,DestroyKey,DestroyValue);
	return SUCCEDD;
}

Result TestHashMapDestroy_NULL()
{	
	HashMapDestroy(NULL,DestroyKey,DestroyValue);
	return SUCCEDD;
}

/* INSERT DATA */

Result TestHashMapInsert_Valid()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249};
	void* values[] = {(void*)1,"abd",(void*)7,NULL,(void*)4543,(void*)65,(void*)'a',(void*)2};
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,values,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapInsert_Exist()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249,239};
	void* values[] = {(void*)1,"abd",(void*)7,NULL,(void*)4543,(void*)65,(void*)'a',(void*)2,NULL};
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,values,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	if(ERR_EXIST == HashMapInsert(hashMap,&keys[8],&values[8])) 
	{ 
		return SUCCEDD; 
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapInsert_ExistInput()
{
	int key = 2, value = 5;
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}
	
	if(ERR_ILLEGAL_INPUT == HashMapInsert(hashMap,NULL,&value) || ERR_ILLEGAL_INPUT == HashMapInsert(hashMap,&key,NULL)) 
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return SUCCEDD; 
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapInsert_NULLMap()
{
	int key = 2, value = 5;
	
	if(ERR_NOT_INITIALIZE == HashMapInsert(NULL,&key,&value)) 
	{ 
		return SUCCEDD; 
	}

	return FAILED;
}

/* REMOVE DATA */

Result TestHashMapRemove_ValidExist()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249}, *resKey;
	void* values[] = {(void*)1,"abd",(void*)7,NULL,(void*)4543,(void*)65,(void*)'a',(void*)2}, *resVal;
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,values,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	if(SUCCEEDED != HashMapRemove(hashMap,&keys[3],(void**)&resKey,(void**)&resVal) || 261 != *resKey || !resVal)
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapRemove_NotExist()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249,537}, *resKey;
	void* values[] = {(void*)1,"abd",(void*)7,NULL,(void*)4543,(void*)65,(void*)'a',(void*)2}, *resVal;
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,values,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	if(ERR_NOT_EXIST == HashMapRemove(hashMap,&keys[8],(void**)&resKey,(void**)&resVal))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return SUCCEDD;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}

Result TestHashMapRemove_Empty()
{
	int key = 2, *resKey, *resVal;

	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(ERR_NOT_EXIST == HashMapRemove(hashMap,&key,(void**)&resKey,(void**)&resVal))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return SUCCEDD;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}

Result TestHashMapRemove_NULLInput()
{
	int key = 2, *resKey, *resVal;
	ErrCode err, err2, err3;
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	err = HashMapRemove(hashMap,NULL,(void**)&resKey,(void**)&resVal);
	err2 = HashMapRemove(hashMap,&key,NULL,(void**)&resVal);
	err3 = HashMapRemove(hashMap,&key,(void**)&resKey,NULL);
	
	if(ERR_ILLEGAL_INPUT == err && ERR_ILLEGAL_INPUT == err2 && ERR_ILLEGAL_INPUT == err3)
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return SUCCEDD;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}


Result TestHashMapRemove_NULL()
{
	int key = 2, *resKey, *resVal;
	
	if(ERR_NOT_INITIALIZE == HashMapRemove(NULL,&key,(void**)&resKey,(void**)&resVal))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}
/* FIND DATA */

Result TestHashMapFind_ValidExist()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249};
	void* values[] = {(void*)1,"abd",(void*)7,NULL,(void*)4543,(void*)65,(void*)'a',(void*)2}, *resVal;
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,values,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	if(SUCCEEDED != HashMapFind(hashMap,&keys[1],(void**)&resVal) || !strcmp(resVal,"abd"))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapFind_NotExist()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249,537};
	void* values[] = {(void*)1,"abd",(void*)7,NULL,(void*)4543,(void*)65,(void*)'a',(void*)2}, *resVal;
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,values,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	if(ERR_NOT_EXIST == HashMapFind(hashMap,&keys[8],(void**)&resVal))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return SUCCEDD;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}

Result TestHashMapFind_Empty()
{
	int key = 2, *resVal;

	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(ERR_NOT_EXIST == HashMapFind(hashMap,&key,(void**)&resVal))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return SUCCEDD;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}

Result TestHashMapFind_NULLInput()
{
	int key = 2, *resVal;
	ErrCode err, err2;
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	err = HashMapFind(hashMap,NULL,(void**)&resVal);
	err2 = HashMapFind(hashMap,&key,NULL);
	
	if(ERR_ILLEGAL_INPUT == err && ERR_ILLEGAL_INPUT == err2)
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return SUCCEDD;
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}


Result TestHashMapFind_NULL()
{
	int key = 2, *resVal;
	
	if(ERR_NOT_INITIALIZE == HashMapFind(NULL,&key,(void**)&resVal))
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

/* HASH MAP SIZE */

Result TestHashMapSize_Valid()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249};
	void* values[] = {(void*)1,"abd",(void*)7,NULL,(void*)4543,(void*)65,(void*)'a',(void*)2};
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,values,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	if(8 != HashMapSize(hashMap))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;	
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapSize_Empty()
{
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(0 != HashMapSize(hashMap))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;	
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapSize_NULL()
{
	if(0 != HashMapSize(NULL))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

/* FOR EACH */

Result TestHashMapForEach_Valid()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249}, con = 1;
	void* values[] = {(void*)1,(void*)73,(void*)7,(void*)12,(void*)4543,(void*)65,(void*)34,(void*)2};
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,values,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	if(8 != HashMapForEach(hashMap,PosOrNeg,&con))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;	
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapForEach_ValidStop()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249}, con = 100;
	void* values[] = {(void*)61,(void*)146,(void*)74,(void*)4543,(void*)1672,(void*)655,(void*)345,(void*)2};
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,values,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	if(2 != HashMapForEach(hashMap,DecreaseMoreThan,&con))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;	
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapForEach_Empty()
{
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}
	
	if(0 != HashMapForEach(hashMap,DecreaseMoreThan,(void*)100))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;	
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapForEach_NULLFunc()
{
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}
	
	if(0 == HashMapForEach(hashMap,NULL,(void*)100))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return SUCCEDD;	
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}

Result TestHashMapForEach_NULLHash()
{
	if(0 == HashMapForEach(NULL,DecreaseMoreThan,(void*)100))
	{
		return SUCCEDD;	
	}
		return FAILED;
}

/* MAP STATS */

Result TestHashMapGetStatistics_Valid()
{
	int keys[] = {1235,239,1253,261,4,11,1678,249};
	MapStats stats;
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	if(FAILED == FillHash(hashMap,keys,(void*)keys,ARR_SIZE))
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;
	}
	
	stats = HashMapGetStatistics(hashMap);
	
	if(3 != stats.numberOfBuckets || 8 != stats.numberOfChains || 4 != stats.maxChainLength || 2 != stats.averageChainLength)
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return FAILED;	
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return SUCCEDD;
}

Result TestHashMapGetStatistics_Empty()
{
	MapStats stats;
	
	HashMap *hashMap = HashMapCreate(SIZE,GetPosition,CompareKeys);
	if(NULL == hashMap)
	{
		return FAILED;
	}

	stats = HashMapGetStatistics(hashMap);
	
	if(0 == stats.numberOfBuckets && 0 == stats.numberOfChains && 0 == stats.maxChainLength && 0 == stats.averageChainLength)
	{
		HashMapDestroy(&hashMap,NULL,NULL);
		return SUCCEDD;	
	}
	
	HashMapDestroy(&hashMap,NULL,NULL);
	return FAILED;
}

Result TestHashMapGetStatistics_NULL()
{
	MapStats stats;
	
	stats = HashMapGetStatistics(NULL);
	
	if(0 == stats.numberOfBuckets && 0 == stats.numberOfChains && 0 == stats.maxChainLength && 0 == stats.averageChainLength)
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
	/*Create hash map*/
	/*POS*/
	printf("\n--- Create hash map: ---\n");
	PrintRes("TestHashMapCreate_Valid:",TestHashMapCreate_Valid);
	/*NEG*/
	PrintRes("TestHashCreate_NULLFunGP:",TestHashCreate_NULLFunGP);
	PrintRes("TestHashCreate_NULLFunCK:",TestHashCreate_NULLFunCK);

	/*Destroy hash map*/
	/*POS*/
	printf("\n--- Destroy hash map: ---\n");

	/*NEG*/

	/*Insert key and value*/
	/*POS*/
	printf("\n--- Insert key and value: ---\n");
	PrintRes("TestHashMapInsert_Valid:",TestHashMapInsert_Valid);
	/*NEG*/
	PrintRes("TestHashMapInsert_Exist:",TestHashMapInsert_Exist);
	PrintRes("TestHashMapInsert_NULLMap:",TestHashMapInsert_NULLMap);
	PrintRes("TestHashMapInsert_ExistInput:",TestHashMapInsert_ExistInput);
	
	/*Remove key and value*/
	/*POS*/
	printf("\n--- Remove key and value: ---\n");
	PrintRes("TestHashMapRemove_ValidExist:",TestHashMapRemove_ValidExist);
	/*NEG*/
	PrintRes("TestHashMapRemove_NotExist:",TestHashMapRemove_NotExist);
	PrintRes("TestHashMapRemove_Empty:",TestHashMapRemove_Empty);
	PrintRes("TestHashMapRemove_NULLInput:",TestHashMapRemove_NULLInput);
	PrintRes("TestHashMapRemove_NULL:",TestHashMapRemove_NULL);

	/*Find value by key*/
	/*POS*/
	printf("\n--- Find value by key: ---\n");
	PrintRes("TestHashMapFind_ValidExist:",TestHashMapRemove_ValidExist);
	/*NEG*/
	PrintRes("TestHashMapFind_NotExist:",TestHashMapFind_NotExist);
	PrintRes("TestHashMapFind_Empty:",TestHashMapFind_Empty);
	PrintRes("TestHashMapFind_NULLInput:",TestHashMapFind_NULLInput);
	PrintRes("TestHashMapFind_NULL:",TestHashMapFind_NULL);

	/*Hash map size*/
	/*POS*/
	printf("\n--- Hash map size: ---\n");
	PrintRes("TestHashMapSize_Valid:",TestHashMapSize_Valid);
	PrintRes("TestHashMapSize_Empty:",TestHashMapSize_Empty);
	/*NEG*/
	PrintRes("TestHashMapSize_NULL:",TestHashMapSize_NULL);

	/*For each*/
	/*POS*/
	printf("\n--- For each: ---\n");
	PrintRes("TestHashMapForEach_Valid:",TestHashMapForEach_Valid);
	PrintRes("TestHashMapForEach_ValidStop:",TestHashMapForEach_ValidStop);
	/*NEG*/
	PrintRes("TestHashMapForEach_Empty:",TestHashMapForEach_Empty);
	PrintRes("TestHashMapForEach_NULLFunc:",TestHashMapForEach_NULLFunc);
	PrintRes("TestHashMapForEach_NULLHash:",TestHashMapForEach_NULLHash);
	
	/*Map stats*/
	/*POS*/
	printf("\n--- Map stats: ---\n");
	PrintRes("TestHashMapGetStatistics_Valid:",TestHashMapGetStatistics_Valid);
	PrintRes("TestHashMapGetStatistics_Empty:",TestHashMapGetStatistics_Empty);
	/*NEG*/
	PrintRes("TestHashMapGetStatistics_NULL:",TestHashMapGetStatistics_NULL);



	return 0;
}
