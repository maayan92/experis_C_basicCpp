#ifndef _VECTOR_H
#define _VECTOR_H

/*error code*/
#include "ADTErrors.h"

typedef struct Vector Vector;

/*action function, return true or false*/
typedef int (*ActionFunction)(const void*, void*);

/*
	Description: create dynamic struct Vector.
	Input: _initialSize - initial size of vector array, _blockSize - block size to increase the vector array when it's full, both should to be positive.
	Return value: return pointer to allocated Vector, or NULL in case it fails.
*/
Vector* VectorCreate(size_t _initialSize, size_t _blockSize);


/*
	Description: destroy the Vector, after calling this function the Vector pointer should be reset with NULL.
	Input: _vec - dynamic struct Vector pointer.
	Return value: nothing returns.
*/
void VectorDestroy(Vector* _vec, void(*ptrDestroy)(void*));

/*
	Description: add new data to the end of the vector array, resize (increases the size) the vector array in case that it's full.
	Input: _vec - dynamic struct Vector pointer, 
			_data - void poniter to the new data that would be inserted to the vector array.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, ERR_OVERFLOW - if the resize fails because there is a memory overflow,
					 SUCCEEDED - on success.
*/
ErrCode VectorAddTail(Vector* _vec, void* _data);

/*
	Description: remove the last data from the vector array, resize (reduces the size) the vector array in case there is too much empty space.
	Input: _vec - dynamic struct Vector pointer, 
			_data - void pointer to the data pointer that would be removed from the vector array.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL or if the vector array is empty, ERR_FAILED - if the realloc fails,
					SUCCEEDED - on success.
*/
ErrCode VectorRemoveTail(Vector* _vec, void** _data);

/*
	Description: add new data to a specific position in the vector array.
	Input: _vec - dynamic struct Vector pointer, 
			_indx - the position where the data would be insert to , 
			_data - void pointer to the new data that would be inserted to the vector array.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, ERR_ILLEGAL_INPUT - if the _indx is 0 or bigger than the array size,
					SUCCEEDED - on success.
*/
ErrCode VectorSet(Vector* _vec, size_t _indx, void* _data);

/*
	Description: remove data from a specific position in the vector array, resize (reduces the size) the vector array in case there is too much empty space.
	Input: _vec - dynamic struct Vector pointer, 
			_indx - the position where the data would be removed from , 
			_data - pointer to the data that would be removed.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL or if the vector array is empty,
					ERR_ILLEGAL_INPUT - if the _indx is 0 or bigger than the array size, SUCCEEDED - on success.
*/
ErrCode VectorGet(const Vector* _vec, size_t _indx, void** _data);

/*
	Description: search a specific data.
	Input: _vec - dynamic struct Vector pointer, 
			_data - the data you want to find.
	Return value: return the position of the data or 0 if the vector if NULL or the data is not found.
*/
size_t VectorFind(const Vector* _vec,  void* _data);

/*
	Description: prints the dynamic struct vector.
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode PrintArray(const Vector *_vec, void(*ptrPrint)(void*));

/*
	Description: give the number of elements in the vector array.
	Input: _vec - dynamic struct Vector pointer.
	Return value: return the number of elements in the array, or NULL if the _vec is NULL.
*/	
size_t VectorNumOfelements(const Vector* _vec);


size_t VectorForEach(const Vector* _vector, ActionFunction _action, void* _context);


#endif
