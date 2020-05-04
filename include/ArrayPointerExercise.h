#ifndef _ARR_POINTER_H
#define _ARR_POINTER_H

#include <stdio.h>
#include "ADTErrors.h"

#define LOTTO_LENGTH 6


/*
	Description: search a specific value in the array.
	Input: _arr - integer array, should be sorted, _size - size of the array.
	Return value: return the position of the value in the array, -1 if the value doesn't exist in the array or if _arr is NULL.
*/
int BinarySearch(int *_arr, int _size, int _element);

/*
	Description: print the array numbers as lotto card.
	Input: _arr - integer array, should be with 6 numbers and be between 1 to 49.
	Return value: return error code, ERR_NOT_INITIALIZE - if _arr is NULL, ERR_ILLEGAL_INPUT - if there is a number smaller than 1 or a number bigger than 49,
					SUCCEEDED - on success.
*/
ErrCode Lotto(int *_arr);

#endif
