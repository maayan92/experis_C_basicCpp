#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

#define HASH_MAGIC_NUMBER 0xaaaabbbb
#define IS_NOT_EXIST(_hash) (NULL == _hash || _hash->m_magicNumber != HASH_MAGIC_NUMBER)

struct Hash
{
	size_t m_magicNumber;
	int* m_data;/**/
	char* m_state;/**/
	size_t m_hashSize; /*original size given by the client*/
	size_t m_capacity; /*real hush size */
	size_t m_numOfItems; /*number of occupied plases in the table*/
	size_t m_maxOfRehashOperations; /*maximum emaunt of rehash opetations which have been done over one insertion*/
	size_t m_counterOfInsertions; /*maximum emaunt of insertions into the table*/
	size_t m_allRehashOperations; /*all rehash operations mutual counter*/
	HashFunction m_hashFunction;
};

/**/
static size_t getCapacity(size_t _size);
/**/
static size_t checkIfPrimary(size_t _num);
/**/
static void insertIntoHash(Hash* _hash, int _data);
/**/
static size_t ReHashFunction(size_t _position, size_t _capacity);
/**/
static size_t findRemovePosition(Hash* _hash, int _data, int _position, int _maxPos);

Hash* HashCreate(size_t _size, HashFunction _hashFunction)
{
	Hash *hash;
	
	if(!_hashFunction)
	{
		return NULL;
	}
	
	hash = (Hash*)malloc(sizeof(Hash));
	if(!hash)
	{
		return NULL;
	}
	
	hash->m_hashSize = _size;
	hash->m_capacity = getCapacity(_size);
	
	hash->m_data = (int*)calloc(hash->m_capacity,sizeof(int));
	if(!(hash->m_data))
	{
		free(hash);
		return NULL;
	}

	hash->m_state = (char*)calloc(hash->m_capacity,sizeof(char));
	if(!(hash->m_state))
	{
		free(hash);
		free(hash->m_data);
		return NULL;
	}
	
	hash->m_numOfItems = 0; 
	hash->m_maxOfRehashOperations = 0;
	hash->m_counterOfInsertions = 0;
	hash->m_allRehashOperations = 0;
	hash->m_hashFunction = _hashFunction;
	hash->m_magicNumber = HASH_MAGIC_NUMBER;
	
	return hash;
}

void HashDestroy(Hash** _hash)
{
	if(!_hash || IS_NOT_EXIST((*_hash)))
	{
		return;
	}
	
	(*_hash)->m_magicNumber = 0;
	
	free((*_hash)->m_data);
	free((*_hash)->m_state);
	free(*_hash);
	
	(*_hash) = NULL;
}

ErrCode HashInsert(Hash* _hash, int _data)
{	
	if(IS_NOT_EXIST(_hash))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(_hash->m_numOfItems == _hash->m_hashSize)
	{
		return ERR_OVERFLOW;
	}

	if(HashIsFound(_hash,_data))
	{
		return ERR_EXIST;
	}
	
	insertIntoHash(_hash,_data);

	return SUCCEEDED;
}

ErrCode HashRemove(Hash* _hash, int _data)
{
	int maxPos, position = _hash->m_hashFunction(_data) % _hash->m_capacity;
	
	if(IS_NOT_EXIST(_hash))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(0 == _hash->m_numOfItems)
	{
		return ERR_UNDERFLOW;
	}
	
	maxPos = (position + (_hash->m_maxOfRehashOperations) + 1) % _hash->m_capacity;
	position = findRemovePosition(_hash,_data,position,maxPos);

	if('0' == _hash->m_state[position] || position == maxPos)
	{
		return ERR_NOT_EXIST;
	}
	
	_hash->m_state[position] = 0;
	--_hash->m_numOfItems;
	
	return SUCCEEDED;
}

int HashIsFound(const Hash* _hash, int _data)
{
	int maxPos, position = _hash->m_hashFunction(_data) % _hash->m_capacity;
	
	if(IS_NOT_EXIST(_hash))
	{
		return false;
	}
	
	maxPos = (position + (_hash->m_maxOfRehashOperations) + 1) % _hash->m_capacity;
	
	while(position != maxPos)
	{
		if(0 == _hash->m_state[position])
		{
			return false;
		}
		
		if(2 == _hash->m_state[position] && _data == _hash->m_data[position])
		{
			return true;
		}

		position = ReHashFunction(position,_hash->m_capacity);
		
	}
	
	return false;
}

size_t HashNumOfItems(const Hash* _hash)
{
	if(IS_NOT_EXIST(_hash))
	{
		return 0;
	}
	
	return _hash->m_numOfItems;
}

size_t HashCapacity(const Hash* _hash)
{
	if(IS_NOT_EXIST(_hash))
	{
		return 0;
	}
	
	return _hash->m_hashSize;
}

double HashAverageRehashes(const Hash* _hash)
{
	if(IS_NOT_EXIST(_hash))
	{
		return 0;
	}

	return (_hash->m_allRehashOperations / _hash->m_counterOfInsertions);
}

size_t HashMaxReHash(const Hash* _hash)
{
	if(IS_NOT_EXIST(_hash))
	{
		return 0;
	}
	
	return _hash->m_maxOfRehashOperations;
}

void HashPrint(const Hash* _hash)
{
	
}

/* SUB FUNCTIONS */

static size_t getCapacity(size_t _size)
{
	int capacity = _size*(1.3);
	
	while(!checkIfPrimary(capacity))
	{
		++capacity;
	}
	
	return capacity;
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

static void insertIntoHash(Hash* _hash, int _data)
{
	int countReHash = 0, position = _hash->m_hashFunction(_data) % _hash->m_capacity;

	while('2' == _hash->m_state[position])
	{
		position = ReHashFunction(position,_hash->m_capacity);
		++countReHash;
		++_hash->m_allRehashOperations;
	}
	
	if(countReHash > _hash->m_maxOfRehashOperations)
	{
		_hash->m_maxOfRehashOperations = countReHash;
	}
	
	_hash->m_data[position] = _data;
	_hash->m_state[position] = 2;
	++_hash->m_numOfItems;
	++_hash->m_counterOfInsertions;
}

static size_t ReHashFunction(size_t _position, size_t _capacity)
{
	return (_position + 1) % _capacity;
}

static size_t findRemovePosition(Hash* _hash, int _data, int _position, int _maxPos)
{
	while(_data != _hash->m_data[_position] && _position != _maxPos)
	{
		if('0' == _hash->m_state[_position])
		{
			return _position;
		}
		
		_position = ReHashFunction(_position,_hash->m_capacity);
	}
	
	return _position;
}


















