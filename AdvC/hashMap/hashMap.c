#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashMap.h"
#include "listFunctions.h"

#define HASH_MAP_MAGIC_NUMBER 0xbbbbaaaa
#define IS_NOT_EXIST(_hashMap) (NULL == _hashMap || _hashMap->m_magicNumber != HASH_MAP_MAGIC_NUMBER)

struct HashMap
{
	size_t m_magicNumber;
	List **m_listArr;
	size_t m_capacity;
	HashFunction m_hashFunc;
	EqualityFunction m_keysEqualFunc;
};

typedef struct Data
{
	const void* m_key;
	void* m_value;
}Data;

typedef struct ContextFind
{
	const void* m_key;
	EqualityFunction m_equalFunc;
}ContextFind;

typedef struct ContextAction
{
	void* m_userContext;
	KeyValueActionFunction m_userActionFunc;
}ContextAction;	
	

/*destroy all list elements*/
static void DestroyElements(List *_list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
/*create a new data with the new _key and the new _value*/
static Data* CreateData(const void* _key, const void* _value);
/*destroy the _data*/
static void DestroyData(Data *_data, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
/*caculate the capacity number*/
static size_t getCapacity(size_t _capacity);
/*check if the number is primary*/
static size_t checkIfPrimary(size_t _num);

/*insert the new key and value to the hash if not exist key*/
static ErrCode insertIntoList(HashMap* _map, const void* _key, const void* _value);
/*remove data (key and value) from the appropriate list if exist key*/
static ErrCode RemoveFromHash(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue);
/*get value from the appropriate list if exist*/
static ErrCode FoundValueIfExist(const HashMap* _map, const void* _key, void** _pValue);
/*get the ListItr with the appropriate key if exist*/
static ListItr GetListItrIfExist(const HashMap* _map, const void* _key);
/*check if a key exist in the appropriate list*/
static int CheckIfEqual(void *_element, void *_context);
/**/
static size_t GoOnAllElements(const HashMap* _map, void* _context);
/**/
static int innerAction(void *_element, void *_context);

/*count the number of lists*/
static size_t CountExistingLists(List* _list,size_t _count);
/*count the number of elements*/
static size_t CountAllElements(List* _list,size_t _count);
/*get the list with the max size*/
static size_t GetMaxListLegth(List* _list,size_t _count);
/*go on all lists in the map and return count by NumOfFunc function*/
static size_t GoOnMapLists(const HashMap* _map, size_t(*NumOfFunc)(List*,size_t));


HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap *hashMap;
	
	if(!_hashFunc || !_keysEqualFunc)
	{
		return NULL;
	}
	
	hashMap = (HashMap*)malloc(sizeof(HashMap));
	if(!hashMap)
	{
		return NULL;
	}
	
	hashMap->m_capacity = getCapacity(_capacity);
	
	hashMap->m_listArr = (List**)calloc((hashMap->m_capacity),sizeof(List*));
	if(!hashMap->m_listArr)
	{
		free(hashMap);
		return NULL;
	}
	
	hashMap->m_hashFunc = _hashFunc;
	hashMap->m_keysEqualFunc = _keysEqualFunc;
	hashMap->m_magicNumber = HASH_MAP_MAGIC_NUMBER;
	
	return hashMap;
}

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	int i;

	if(!_map || IS_NOT_EXIST((*_map)))
	{
		return;
	}
	
	(*_map)->m_magicNumber = 0;
	
	for(i = 0;i < (*_map)->m_capacity;++i)
	{
		if((*_map)->m_listArr[i])
		{
			DestroyElements((*_map)->m_listArr[i],_keyDestroy,_valDestroy);
		
			DLListDestroy((*_map)->m_listArr[i],NULL);
		}
	}
	
	free((*_map)->m_listArr);
	free(*_map);
	*_map = NULL;
}

ErrCode HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
	if(IS_NOT_EXIST(_map))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(!_key)
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	return insertIntoList(_map,_key,_value);
}

ErrCode HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	if(IS_NOT_EXIST(_map))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(!_searchKey || !_pKey || !_pValue)
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	return RemoveFromHash(_map,_searchKey,_pKey,_pValue);
}

ErrCode HashMapFind(const HashMap* _map, const void* _key, void** _pValue)
{
	if(IS_NOT_EXIST(_map))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(!_key || !_pValue)
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	return FoundValueIfExist(_map,_key,_pValue);
}

size_t HashMapSize(const HashMap* _map)
{
	if(IS_NOT_EXIST(_map))
	{
		return 0;
	}
	
	return GoOnMapLists(_map,CountAllElements);
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	ContextAction con;
	
	if(IS_NOT_EXIST(_map) || !_action)
	{
		return 0;
	}
	
	con.m_userContext = _context;
	con.m_userActionFunc = _action;
	
	return GoOnAllElements(_map,&con);
}

MapStats HashMapGetStatistics(const HashMap* _map)
{
	MapStats mapStats = {0,0,0,0};
	
	if(IS_NOT_EXIST(_map))
	{
		return mapStats;
	}
	
	mapStats.numberOfBuckets = GoOnMapLists(_map,CountExistingLists);
	mapStats.numberOfChains = GoOnMapLists(_map,CountAllElements);
	mapStats.maxChainLength = GoOnMapLists(_map,GetMaxListLegth);
	mapStats.averageChainLength = (0 == mapStats.numberOfBuckets) ? 0 : mapStats.numberOfChains / mapStats.numberOfBuckets;
	
	return mapStats;
}

/* SUB FUNCTIONS */

static void DestroyElements(List *_list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	ListItr beginItr = ListItrBegin(_list);
	ListItr endItr = ListItrEnd(_list);
	Data *data;
	
	while(!ListItrEquals(beginItr,endItr))
	{
		data = (Data*)ListItrGet(beginItr);
		
		DestroyData(data,_keyDestroy,_valDestroy);
		
		beginItr = ListItrNext(beginItr);
	}
}

static Data* CreateData(const void* _key, const void* _value)
{
	Data *data = (Data*)malloc(sizeof(Data));
	if(!data)
	{
		return NULL;
	}
	
	data->m_key = _key;
	data->m_value = (void*)_value;
	
	return data;
}

static void DestroyData(Data *_data, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	if(_keyDestroy)
	{
		_keyDestroy((void*)_data->m_key);
	}
	
	if(_valDestroy)
	{
		_valDestroy(_data->m_value);
	}
	
	free(_data);
}

static size_t getCapacity(size_t _capacity)
{
	while(!checkIfPrimary(_capacity))
	{
		++_capacity;
	}
	
	return _capacity;
}

static size_t checkIfPrimary(size_t _num)
{
	int i;
	
	if((_num % 2) == 0)
	{
		return 0;
	}
	
	for(i = 3;i < ((int)sqrt((double)_num)+1);i += 2)
	{
		if((_num % i) == 0)
		{
			return 0;
		}
	}
	
	return 1;
}

static ErrCode insertIntoList(HashMap* _map, const void* _key, const void* _value)
{
	size_t position = _map->m_hashFunc(_key) % _map->m_capacity;
	ContextFind con;
	ListItr foundItr;
	
	if(!_map->m_listArr[position])
	{
		_map->m_listArr[position] = DLListCreate();
		if(!(_map->m_listArr[position]))
		{
			return ERR_ALLOCATION_FAILED;
		}
	}
	
	con.m_key = _key;
	con.m_equalFunc = _map->m_keysEqualFunc;
	
	foundItr = ListItrFindFirst(ListItrBegin(_map->m_listArr[position]),ListItrEnd(_map->m_listArr[position]),CheckIfEqual,&con);
	
	if(!ListItrEquals(ListItrEnd(_map->m_listArr[position]),foundItr))
	{
		return ERR_EXIST;
	}
	
	if(ERR_ILLEGAL_INPUT == DLListPushHead(_map->m_listArr[position],CreateData(_key,_value)))
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	return SUCCEEDED;
}

static ErrCode RemoveFromHash(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	Data *data;
	ListItr removeItr = GetListItrIfExist(_map,_searchKey);
	
	if(!removeItr)
	{
		return ERR_NOT_EXIST;
	}
	
	data = (Data*)ListItrRemove(removeItr);

	*_pKey = (void*)data->m_key;
	*_pValue = data->m_value;
	
	DestroyData(data,NULL,NULL);
	
	return SUCCEEDED;
}

static ErrCode FoundValueIfExist(const HashMap* _map, const void* _key, void** _pValue)
{
	ListItr foundItr = GetListItrIfExist(_map,_key);
	
	if(!foundItr)
	{
		return ERR_NOT_EXIST;
	}

	*_pValue = ((Data*)ListItrGet(foundItr))->m_value;
	
	return SUCCEEDED;
}

/* search and get ListItr */

static ListItr GetListItrIfExist(const HashMap* _map, const void* _key)
{
	size_t position = _map->m_hashFunc(_key) % _map->m_capacity;
	ListItr foundItr;
	ContextFind con;

	if(!(_map->m_listArr[position]))
	{
		return NULL;
	}
	
	con.m_key = _key;
	con.m_equalFunc = _map->m_keysEqualFunc;
	
	foundItr = ListItrFindFirst(ListItrBegin(_map->m_listArr[position]),ListItrEnd(_map->m_listArr[position]),CheckIfEqual,&con);
	
	if(ListItrEquals(ListItrEnd(_map->m_listArr[position]),foundItr))
	{
		return NULL;
	}
	
	return foundItr;
}

static int CheckIfEqual(void *_element, void *_context)
{
	return ((ContextFind*)_context)->m_equalFunc(((Data*)_element)->m_key,((ContextFind*)_context)->m_key);
}

static size_t GoOnAllElements(const HashMap* _map, void* _context)
{
	int i;
	size_t listCount, count = 0;
	
	for(i = 0;i < _map->m_capacity;++i)
	{
		if(_map->m_listArr[i])
		{
			listCount = ListItrCountIf(ListItrBegin(_map->m_listArr[i]),ListItrEnd(_map->m_listArr[i]),innerAction,_context);
			count += listCount;
			
			if(listCount < DLListCountItems(_map->m_listArr[i]))
			{
				return count;
			}
		}
	}
	
	return count;
}

static int innerAction(void *_element, void *_context)
{
	return ((ContextAction*)_context)->m_userActionFunc(((Data*)_element)->m_key,((Data*)_element)->m_value,((ContextAction*)_context)->m_userContext);
}

/* NDEBUG */

static size_t CountExistingLists(List* _list,size_t _count)
{
	return _count + 1;
}

static size_t CountAllElements(List* _list,size_t _count)
{
	return _count + DLListCountItems(_list);
}

static size_t GetMaxListLegth(List* _list,size_t _count)
{
	size_t listAmount = DLListCountItems(_list);
	
	return (listAmount > _count) ? listAmount: _count;
}

static size_t GoOnMapLists(const HashMap* _map, size_t(*NumOfFunc)(List*,size_t))
{
	int i, count = 0;
	
	for(i = 0;i < _map->m_capacity;++i)
	{
		if(_map->m_listArr[i])
		{
			count = NumOfFunc(_map->m_listArr[i],count);
		}
	}
	
	return count;
}







