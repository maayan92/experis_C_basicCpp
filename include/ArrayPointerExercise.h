#ifndef _ARR_POINTER_H
#define _ARR_POINTER_H

#include <stdio.h>
#include "ADTErrors.h"

#define LOTTO_LENGTH 6


/*
	Description: search a specific value in the array.
	Input: _arr - integer array, _size - size of the array.
	Return value: return the position of the value in the array or -1 if the value doesn't exist in the array.
*/
int BinarySearch(int *_arr, int _size, int _element);

/*
	Description: print the array numbers as lotto card.
	Input: _arr - integer array.
	Return value: return error code, ERR_NOT_INITIALIZE - if _arr is NULL, ERR_ILLEGAL_INPUT - if there is a number smaller than 1 or a number bigger than 49,
					SUCCEEDED - on success.
*/
ErrCode Lotto(int *_arr);

#endif
