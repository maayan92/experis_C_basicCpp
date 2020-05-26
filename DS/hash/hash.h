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
	Return value: return error code, ERR_NOT_INITIALIZE - if the hash doesn't exist, ERR_OVERFLOW -   SUCCEEDED - on success.
*/
ErrCode HashInsert(Hash* _hash, int _data);

/*
	Description: remove the data fro the hash.
	Input: _hash - pointer to pointer to the hash, _data - the data to remove.
	Return value: return error code, 
*/
ErrCode HashRemove(Hash* _hash, int _data);

/*
	Description: search for specific data.
	Input: _hash - pointer to the hash, _data - the data to search.
	Return value: return true if the data found, false if the data isn't found or if the _hash isn't exist.
*/
int HashIsFound(const Hash* _hash, int _data);


size_t HashNumOfItems(const Hash* _hash);


size_t HashCapacity(const Hash* _hash);


double HashAverageRehashes(const Hash* _hash);


size_t HashMaxReHash(const Hash* _hash);


void HashPrint(const Hash* _hash);




#endif
