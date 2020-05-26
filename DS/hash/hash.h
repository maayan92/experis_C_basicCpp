#ifndef __HASH_H_
#define __HASH_H_

#include "ADTErrors.h"

typedef struct Hash Hash;

typedef size_t(*HashFunction)(int);

enum { false, true };


/*
	Description: create new hash.
	Input: _size - size of the hash, _hashFunction - hash function to insert the data.
	Return value: return pointer to the hash, or NULL if the _hashFunction is NULL or if one of the allocations fails.
*/
Hash* HashCreate(size_t _size, HashFunction _hashFunction);

/*
	Description: destroy the hash.
	Input: _hash - pointer to pointer to the hash.
	Return value: nothing returns.
*/
void HashDestroy(Hash** _hash);

/*
	Description: insert a new data to the hash.
	Input: _hash - pointer to pointer to the hash, _data - the new data to insert.
	Return value: return error code, ERR_NOT_INITIALIZE - if the hash doesn't exist, ERR_OVERFLOW - if the hash if full, 
					ERR_EXIST - if the data is alreaty exist in the hash, SUCCEEDED - on success.
*/
ErrCode HashInsert(Hash* _hash, int _data);

/*
	Description: remove the data from the hash.
	Input: _hash - pointer to pointer to the hash, _data - the data to remove.
	Return value: return error code, ERR_NOT_INITIALIZE - if the hash doesn't exist, ERR_UNDERFLOW - if the hash is empty,
					ERR_NOT_EXIST - if the data is not exist, SUCCEEDED - on success.
*/
ErrCode HashRemove(Hash* _hash, int _data);

/*
	Description: search for specific data.
	Input: _hash - pointer to the hash, _data - the data to search.
	Return value: return true if the data found, false if the data isn't found or if the _hash isn't exist.
*/
int HashIsFound(const Hash* _hash, int _data);

/*
	Description: get the number of items in the hash.
	Input: _hash - pointer to the hash.
	Return value: return the number of items, 0 if the hash isn't exist.
*/
size_t HashNumOfItems(const Hash* _hash);

/*
	Description: get the hash size.
	Input: _hash - pointer to the hash.
	Return value: return the hash size, 0 if the hash isn't exist.
*/
size_t HashCapacity(const Hash* _hash);

/*
	Description: get the average rehash by the ratio between rehash and insertions.
	Input: _hash - pointer to the hash.
	Return value: the average rehash, 0 if the hash isn't exist.
*/
double HashAverageRehashes(const Hash* _hash);

/*
	Description: get the max rehash number that has been done.
	Input: _hash - pointer to the hash.
	Return value: return the max rehash number, 0 if the hash isn't exist.
*/
size_t HashMaxReHash(const Hash* _hash);

/*
	Description: print the hash.
	Input: _hash - pointer to the hash.
	Return value: nothing returns.
*/
/*HashPrint for debug only*/
void HashPrint(const Hash* _hash);




#endif
