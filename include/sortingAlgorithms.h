#ifndef __SORTING_ALGORITHMS_H_
#define __SORTING_ALGORITHMS_H_

#include "ADTErrors.h"
#include "dynamicVector.h"

/*
	Description: sort the vector by bubble sort, one-directional sort.
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode BubbleSort(Vector *_vec);

/*
	Description: sort the vector by shake sort, bi-directional sort.
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode ShakeSort(Vector *_vec);

/*
	Description: sort the vector by recurtion quick sort.
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode QuickSortRec(Vector *_vec);

/*
	Description: sort the vector by iterative quick sort.
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode QuickSortIter(Vector* _vec);

/*
	Description: sort the vector by insertion sort
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode InsertionSort(Vector* _vec);

/*
	Description: sort the vector by shell sort. 
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode ShellSort(Vector* _vec);

/*
	Description:  TODO
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode SelectionSort(Vector* _vec);

/*
	Description:  TODO
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode MergeSort(Vector* _vec);

/*
	Description:  TODO
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode CountingSort(Vector* _vec, int _minValue, int _maxValue);

/*
	Description:  TODO
	Input: _vec - dynamic struct Vector pointer.
	Return value: return error code, ERR_NOT_INITIALIZE - if the _vec is NULL, SUCCEEDED - on success.
*/
ErrCode RadixSort(Vector* _vec, int _nDigits);


int SearchWithImprove(int *_arr, size_t _size, int _numToSearch);

int SearchNoImprove(int *_arr, size_t _size, int _numToSearch);


#endif
