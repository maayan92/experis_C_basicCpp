#include "genHashMap.h"
#include "genDLList.h"
#include "genDLListIter.h"
#include <stdio.h>
#include <stdlib.h>  /* for allocation */
#include <stdbool.h>
#include <math.h>  /* for sqrt */

#define MAGIC_NUMBER 0xbffacefd
#define NO_MAGIC_NUMBER 0xdeacdeac

#define IS_HASH_NOT_EXIST(hs) (!(hs) || (hs)->m_magicNumber != MAGIC_NUMBER)


struct genHashMap
{
    size_t m_magicNumber;
    genList **m_listArr;
    genHashFunc m_genHashFunc;
    equalityFunction m_equalityFunction;
    size_t m_capacity;
    size_t m_numOfElements;
    size_t m_numOfLists;
};

typedef struct element
{
    void *m_key;
    void *m_value;
}element;



static size_t FIrstPrimeNumAfter(size_t _num);
static size_t IndexFromHashFunc(const genHashMap *_map, const void *_key);
static element* ElementCreate(const void *_key, const void *_value);
static void ElementDestroy(void *_elmnt, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
static int IsKeyInHashList(const genHashMap *_map, size_t _index, const void *_key, genListIter *_iterOfElementIfFound);
static size_t ListLength(const genHashMap *_map, size_t _index);
static size_t MaxListLength(const genHashMap *_map);



genHashMap* GenHashMapCreate(size_t _capacity, genHashFunc _hashFunc, equalityFunction _keysEqualFunc)
{
    genHashMap *newHash;
    
    if(!_hashFunc || !_keysEqualFunc || _capacity <= 0)
    {
        return NULL;
    }
    if(!(newHash = (genHashMap*)calloc(1, sizeof(genHashMap))))
    {
        return NULL;
    }
    
    newHash->m_capacity = FIrstPrimeNumAfter(_capacity);
    if(!(newHash->m_listArr = (genList**)calloc(newHash->m_capacity, sizeof(genList*))))
    {
        free(newHash);
        return NULL;
    }
    
    newHash->m_genHashFunc = _hashFunc;
    newHash->m_equalityFunction = _keysEqualFunc;
    newHash->m_magicNumber = MAGIC_NUMBER;
    
    return newHash;
}

void GenHashMapDestroy(genHashMap ** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    register int i;
    element *elmnt;
    genListIter begin, end;
    
    if(_map && !IS_HASH_NOT_EXIST(*_map))
    {
        (*_map)->m_magicNumber = NO_MAGIC_NUMBER;
        for(i=0; i<(*_map)->m_capacity; ++i)
        {
            begin = GenListIterBegin((*_map)->m_listArr[i]);
            end = GenListIterEnd((*_map)->m_listArr[i]);
            while(!GenListIterEquals(begin, end))
            {
                elmnt = GenListIterGet(begin);
                ElementDestroy(elmnt, _keyDestroy, _valDestroy);
                begin = GenListIterNext(begin);
            }
            GenDLListDestroy((*_map)->m_listArr[i], NULL);
        }
        free((*_map)->m_listArr);
        free((*_map));
        *_map = NULL;
    }
}
/*
mapResult GenHashMapRehash(genHashMap *_map, size_t _newCapacity)
{
    register int i;
    genList **rehash;
    element *elmnt;
    genListIter begin, end, prev, newList;
    
    if(IS_HASH_NOT_EXIST(_map))
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    _newCapacity = FIrstPrimeNumAfter(_newCapacity);
    if(!(rehash = (genList**)realloc(_map->m_listArr, _newCapacity * sizeof(genList*))))
    {
        return MAP_ALLOCATION_ERROR;
    }
    for(i=0; i<_map->m_capacity; ++i)
    {
        
    }
}
*/
mapResult GenHashMapInsert(genHashMap *_map, const void *_key, const void *_value)
{
    size_t index;
    element *elmnt;
    genListIter iter;
    
    if(IS_HASH_NOT_EXIST(_map))
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    if(!_key)
    {
        return MAP_KEY_NULL_ERROR;
    }
    
    index = IndexFromHashFunc(_map, _key);
    
    if(!(elmnt = ElementCreate(_key, _value)))
    {
        return MAP_ALLOCATION_ERROR;
    }
    
    if(!_map->m_listArr[index])
    {
        if(!(_map->m_listArr[index] = GenDLListCreate()))
        {
            return MAP_ALLOCATION_ERROR;
        }
        ++_map->m_numOfLists;
    }
    else
    {
        if(IsKeyInHashList(_map, index, _key, &iter))
        {
            return MAP_KEY_DUPLICATE_ERROR;
        }
    }
    
    GenDLListPushTail(_map->m_listArr[index], elmnt);
    ++_map->m_numOfElements;
    return MAP_SUCCESS;
}

mapResult GenHashMapRemove(genHashMap * _map, const void* _searchKey, void** _pKey, void** _pValue)
{
    size_t index;
    element *elmnt;
    genListIter iter;
    
    if(IS_HASH_NOT_EXIST(_map))
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    if(!_searchKey)
    {
        return MAP_KEY_NULL_ERROR;
    }
    
    index = IndexFromHashFunc(_map, _searchKey);
    
    if(!_map->m_listArr[index])
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    else
    {
        if(!IsKeyInHashList(_map, index, _searchKey, &iter))
        {
            return MAP_KEY_NOT_FOUND_ERROR;
        }
    }
    
    elmnt = GenListIterRemove(iter);
    if(_pKey)
    {
        *_pKey = elmnt->m_key;
    }
    if(_pValue)
    {
        *_pValue = elmnt->m_value;
    }
    ElementDestroy(elmnt, NULL, NULL);
    --_map->m_numOfElements;
    return MAP_SUCCESS;
}

mapResult GenHashMapFind(const genHashMap * _map, const void* _key, void** _pValue)
{
    size_t index;
    element *elmnt;
    genListIter iter;
    
    if(IS_HASH_NOT_EXIST(_map))
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    if(!_key)
    {
        return MAP_KEY_NULL_ERROR;
    }
    
    index = IndexFromHashFunc(_map, _key);
    
    if(!_map->m_listArr[index])
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    else
    {
        if(!IsKeyInHashList(_map, index, _key, &iter))
        {
            return MAP_KEY_NOT_FOUND_ERROR;
        }
    }
    
    elmnt = GenListIterGet(iter);
    if(_pValue)
    {
        *_pValue = elmnt->m_value;
    }
    return MAP_SUCCESS;
}

size_t GenHashMapNumOfElements(const genHashMap * _map)
{
    if(IS_HASH_NOT_EXIST(_map))
    {
        return 0;
    }
    return _map->m_numOfElements;
}

size_t GenHashMapForEach(const genHashMap * _map, keyValueActionFunction _action, void* _context)
{
    register int i;
    size_t counter=0;
    element *elmnt;
    genListIter begin, end;
    
    if(!IS_HASH_NOT_EXIST(_map) && _action)
    {
        for(i=0; i<_map->m_capacity; ++i)
        {
            begin = GenListIterBegin(_map->m_listArr[i]);
            end = GenListIterEnd(_map->m_listArr[i]);
            while(!GenListIterEquals(begin, end))
            {
                elmnt = GenListIterGet(begin);
                if(_action(elmnt->m_key, elmnt->m_value, _context))
                {
                    ++counter;
                }
                begin = GenListIterNext(begin);
            }
        }
    }
    return counter;
}

mapStats GenHashMapGetStatistics(const genHashMap * _map)
{
    mapStats stats;
    
    stats.m_numberOfLists = _map->m_numOfLists;
    stats.m_numberOfElements = _map->m_numOfElements;
    stats.m_maxListLength = MaxListLength(_map);
    stats.m_averageListLength = _map->m_numOfLists? _map->m_numOfElements / _map->m_numOfLists: 0;
    
    return stats;
}



static size_t FIrstPrimeNumAfter(size_t _num)
{
    register int i;
    int isPrime = false;
    int numSqrt = sqrt(_num);
    
    while(!isPrime)
    {
        isPrime = true;
        
        for(i=2; i<=numSqrt; ++i)
        {
            if(_num % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        
        if(!isPrime)
        {
            ++_num;
        }
    }
    
    return _num;
}

static size_t IndexFromHashFunc(const genHashMap *_map, const void *_key)
{
    return _map->m_genHashFunc((void*)_key) % _map->m_capacity;
}

static element* ElementCreate(const void *_key, const void *_value)
{
    element *elmnt;
    
    if(!(elmnt = (element*)malloc(sizeof(element))))
    {
        return NULL;
    }
    
    elmnt->m_key = (void*)_key;
    elmnt->m_value = (void*)_value;
    
    return elmnt;
}

static void ElementDestroy(void *_elmnt, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    if(_keyDestroy)
    {
        _keyDestroy(((element*)_elmnt)->m_key);
    }
    if(_valDestroy)
    {
        _valDestroy(((element*)_elmnt)->m_value);
    }
    free(_elmnt);
}

static int IsKeyInHashList(const genHashMap *_map, size_t _index, const void *_key, genListIter *_iterOfElementIfFound)
{
    genListIter begin = GenListIterBegin(_map->m_listArr[_index]);
    genListIter end = GenListIterEnd(_map->m_listArr[_index]);
    element *elmnt;
    
    while(!GenListIterEquals(begin, end))
    {
        elmnt = GenListIterGet(begin);
        if(_map->m_equalityFunction(elmnt->m_key, (void*)_key))
        {
            *_iterOfElementIfFound = begin;
            return true;
        }
        begin = GenListIterNext(begin);
    }
    return false;
}

static size_t ListLength(const genHashMap *_map, size_t _index)
{
    return GenDLListCountItems(_map->m_listArr[_index]);
}

static size_t MaxListLength(const genHashMap *_map)
{
    register int i;
    int len, maxLen=0;
    
    for(i=0; i<_map->m_capacity; ++i)
    {
        if((len = ListLength(_map, i)) > maxLen)
        {
            maxLen = len;
        }
    }
    return maxLen;
}
/*
static void MoveElementsFromListToList(genList **_listFrom, genList **_listTo)
{
    for
}
*/




