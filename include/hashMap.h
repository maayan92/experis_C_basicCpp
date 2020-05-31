#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <stddef.h>
#include "ADTErrors.h"

typedef struct HashMap HashMap;

typedef size_t (*HashFunction)(const void* _key);
typedef int (*EqualityFunction)(const void* _firstKey, const void* _secondKey);
typedef int (*KeyValueActionFunction)(const void* _key, void* _value, void* _context);


/*
	Description: create new hash map.
	Input: _capacity - max capacity, _hashFunc - hashing function for keys, _keysEqualFunc - equality check function for keys.
	Return value: return pointer to the hash, or NULL if the _hashFunc or the _keysEqualFunc are NULL or if allocations fails.
*/
HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);

/*
	Description: destroy hash map and set *_map to null
	Input: _map - pointer to hash map, _keyDestroy - pointer to function to destroy keys, NULL if not need to free,
		_valDestroy - pointer to function to destroy values, NULL if not need to free.
	Return value: nothing returns.
*/
void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));

/*
	Description: Insert a key-value pair into the hash map.
	Input: _map - pointer to hash map, must be initialized, _key - key to serve as index, _value - The value to associate with the key.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _map isn't exist, ERR_ILLEGAL_INPUT - if _key is NULL, 
					ERR_ALLOCATION_FAILED - if the allocation fails, ERR_EXIST - if the key is already exist, SUCCEEDED - on success.
	Warning: key must be unique and destinct.
*/
ErrCode HashMapInsert(HashMap* _map, const void* _key, const void* _value);

/*
	Description: Remove a key-value pair from the hash map.
	Input: _map - pointer to hash map, must be initialized, _key - key to serve as index to locate _value,
		_pKey  - pointer to variable to recieve key from map if found, _pValue - pointer to variable that will get the value if found.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _map isn't exist, ERR_ILLEGAL_INPUT - if _searchKey/_pKey/_pValue are NULL, 
					ERR_NOT_EXIST - if the key is not found, SUCCEEDED - on success.
	Warning: key must be unique and destinct.
*/
ErrCode HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue);

/*
	Description: Find a value by key.
	Input: _map - pointer to hash map, must be initialized, _key - key to serve as index to locate _value,
		_pValue - pointer to variable that will get the value if found.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _map isn't exist, ERR_ILLEGAL_INPUT - if _Key/_pValue are NULL, 
					ERR_NOT_EXIST - if the key is not found, SUCCEEDED - on success.
	Warning: key must be unique and destinct.
*/
ErrCode HashMapFind(const HashMap* _map, const void* _key, void** _pValue);

/*
	Description: Get number of key-value pairs inserted into the hash map.
	Input: _map - pointer to hash map.
	Return value: return the number of key-value pairs in the hash map, 0 if the _map isn't exist.
*/
size_t HashMapSize(const HashMap* _map);

/*
	Description: Iterate over all key-value pairs in the map, Iteration will stop if _act returns a zero for a given pair
	Input: _map - pointer to hash map, _act - User provided function pointer to be invoked for each element, _context - parameters for the function.
	Return value: returns number of times the user functions was invoked, 0 if the _map isn't exist.
*/
size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context);


#ifndef NDEBUG

typedef struct MapStats {
	size_t numberOfBuckets;/*nubmer of existing lists*/
	size_t numberOfChains; /*num of elements in all the lists*/
	size_t maxChainLength;/*longest list*/
	size_t averageChainLength;/*avg number of lists size*/
}MapStats;

MapStats HashMapGetStatistics(const HashMap* _map);

#endif /* NDEBUG */


#endif
