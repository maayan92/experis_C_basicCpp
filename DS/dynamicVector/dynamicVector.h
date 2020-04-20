#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef int ErrCode;

typedef struct Vector Vector;

enum
{
	ERR_NOT_EXIST,
	ERR_OVERFLOW,
	EMPTY_VECTOR_ARR,
	ERR_ILLEGAL_INPUT,
	ERR_FAILED,
	SUCCEEDED
};

/*
	Description: create dynamic struct Vector, and inside dynamic vector array (int array).
	Input: _initialSize - initial size of vector array, _blockSize - block size to increase the vector array when it's full, both should to be positive.
	Return value: return pointer to allocated Vector, or NULL in case it fails.
*/
Vector* VectorCreate(size_t _initialSize, size_t _blockSize);


/*
	Description: destroy the Vector, and the vector array, after calling this function the Vector pointer should be reset with NULL.
	Input: _vec - dynamic struct Vector pointer.
	Return value: nothing returns.
*/
void VectorDestroy(Vector* _vec);

/*
	Description: add new data to the end of the vector array, resize (increases the size) the vector array in case that it's full.
	Input: _vec - dynamic struct Vector pointer, _data - the new data that would be inserted to the vector array.
	Return value: return error code, ERR_NOT_EXIST - if the _vec is NULL, ERR_OVERFLOW - if the resize fails because there is a memory overflow,
					 SUCCEEDED - on success.
*/
ErrCode VectorAddTail(Vector* _vec, int _data);

/*
	Description: remove the last data from the vector array, resize (reduces the size) the vector array in case there is too much empty space.
	Input: _vec - dynamic struct Vector pointer, _data - the data that would be removed from the vector array.
	Return value: return error code, ERR_NOT_EXIST - if the _vec is NULL or if the vector array is empty, ERR_FAILED - if the realloc fails,
					SUCCEEDED - on success.
*/
ErrCode VectorRemoveTail(Vector* _vec, int* _data);

/*
	Description: add new data to a specific position in the vector array.
	Input: _vec - dynamic struct Vector pointer, _indx - the position where the data would be insert to , 
		_data - the new data that would be inserted to the vector array.
	Return value: return error code, ERR_NOT_EXIST - if the _vec is NULL, ERR_ILLEGAL_INPUT - if the _indx is 0 or bigger than the array size,
					SUCCEEDED - on success.
*/
ErrCode VectorSet(Vector* _vec, size_t _indx, int _data);

/*
	Description: remove data from a specific position in the vector array, resize (reduces the size) the vector array in case there is too much empty space.
	Input: _vec - dynamic struct Vector pointer, _indx - the position where the data would be removed from , _data - pointer to the data that would be removed.
	Return value: return error code, ERR_NOT_EXIST - if the _vec is NULL or if the vector array is empty, ERR_FAILED - if the realloc fails,
					ERR_ILLEGAL_INPUT - if the _indx is 0 or bigger than the array size, SUCCEEDED - on success.
*/
ErrCode VectorGet(Vector* _vec, size_t _indx, int* _data);

/*
	Description: search a specific data.
	Input: _vec - dynamic struct Vector pointer, _data - the data you want to find.
	Return value: return the position of the data or 0 if the vector if NULL or the data is not found.
*/
size_t VectorFind(Vector* _vec,  int _data);

/*
	Description: prints the dynamic struct vector.
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_EXIST - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode PrintArray(Vector *_vec);

/*
	Description: give the number of elements in the vector array.
	Input: _vec - dynamic struct Vector pointer.
	Return value: return the number of elements in the array, or NULL if the _vec is NULL.
*/
size_t VectorNumOfelements(Vector* _vec);



#endif
