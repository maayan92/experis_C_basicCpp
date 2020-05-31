#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

#define HASH_MAGIC_NUMBER 0xaaaabbbb
#define IS_NOT_EXIST(_hash) (NULL == _hash || _hash->m_magicNumber != HASH_MAGIC_NUMBER)

struct Hash
{
	size_t m_magicNumber;
	int* m_data;/*values*/
	char* m_state;/*state, 0 empty, 1 had a value, 2 have value*/
	size_t m_hashSize; /*original size given by the client*/
	size_t m_capacity; /*real hush size */
	size_t m_numOfItems; /*number of occupied plases in the table*/
	size_t m_maxOfRehashOperations; /*maximum emaunt of rehash opetations which have been done over one insertion*/
	size_t m_counterOfInsertions; /*maximum emaunt of insertions into the table*/
	size_t m_allRehashOperations; /*all rehash operations mutual counter*/
	HashFunction m_hashFunction;
};

/*caculate the capacity size*/
static size_t getCapacity(size_t _size);
/*check if the number is primary*/
static size_t checkIfPrimary(size_t _num);
/*insert the new data to the hash*/
static void insertIntoHash(Hash* _hash, int _data);
/*give the new position after rehash*/
static size_t ReHashFunction(size_t _position);
/*remove data if it's exist in the hash*/
static ErrCode RemoveIfExist(Hash* _hash, int _data);
/*find the position to remove from*/
static size_t findRemovePosition(Hash* _hash, int _data, int _position, int _maxPos);
/*search a specific data*/
static int SearchData(const Hash* _hash, int _data, int _position);


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
	if(IS_NOT_EXIST(_hash))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(0 == _hash->m_numOfItems)
	{
		return ERR_UNDERFLOW;
	}
	
	return RemoveIfExist(_hash,_data);
}

int HashIsFound(const Hash* _hash, int _data)
{
	int position;
	
	if(IS_NOT_EXIST(_hash))
	{
		return false;
	}
	
	position = _hash->m_hashFunction(_data) % _hash->m_capacity;
	
	return SearchData(_hash,_data,position);
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
	if(IS_NOT_EXIST(_hash) || !(_hash->m_counterOfInsertions))
	{
		return 0;
	}

	return (double)_hash->m_allRehashOperations / _hash->m_counterOfInsertions;
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
	int i;
	
	if(IS_NOT_EXIST(_hash))
	{
		return;
	}
	
	for(i = 0;i < _hash->m_capacity;++i)
	{
		if(2 == _hash->m_state[i])
		{
			printf("%d \t", _hash->m_data[i]);
		}
	}
	
	printf("\n");
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

	while(2 == _hash->m_state[position])
	{
		position = ReHashFunction(position) % _hash->m_capacity;
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

static size_t ReHashFunction(size_t _position)
{
	return _position + 1;
}

static ErrCode RemoveIfExist(Hash* _hash, int _data)
{
	int maxPos, position;
	
	position = _hash->m_hashFunction(_data) % _hash->m_capacity;
	
	maxPos = (position + (_hash->m_maxOfRehashOperations) + 1) % _hash->m_capacity;
	position = findRemovePosition(_hash,_data,position,maxPos);

	if(0 == _hash->m_state[position] || position == maxPos)
	{
		return ERR_NOT_EXIST;
	}
	
	_hash->m_state[position] = 0;
	--_hash->m_numOfItems;
	
	return SUCCEEDED;
}

static size_t findRemovePosition(Hash* _hash, int _data, int _position, int _maxPos)
{
	while(_data != _hash->m_data[_position] && _position != _maxPos)
	{
		if(0 == _hash->m_state[_position])
		{
			return _position;
		}
		
		_position = ReHashFunction(_position) % _hash->m_capacity;
	}
	
	return _position;
}

static int SearchData(const Hash* _hash, int _data, int _position)
{
	int maxPos = (_position + (_hash->m_maxOfRehashOperations) + 1) % _hash->m_capacity;
	
	while(_position != maxPos)
	{
		if(0 == _hash->m_state[_position])
		{
			return false;
		}
		
		if(2 == _hash->m_state[_position] && _data == _hash->m_data[_position])
		{
			return true;
		}

		_position = ReHashFunction(_position) % _hash->m_capacity;
		
	}
	
	return false;
}

















