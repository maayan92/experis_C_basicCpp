#include <stdio.h>
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

/* COUNT */

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
	/*NEG*/







	return 0;
}
