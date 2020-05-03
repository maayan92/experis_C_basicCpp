#ifndef _SQUEEZE_LOCATION_H
#define _SQUEEZE_LOCATION_H

#include "ADTErrors.h"

#define LENGTH 50

/*
	Description: remove characters that in str2 from str1.
	Input: _str1 - string to remove from, _str2 - string with the chars to remove.
	Return value: 
*/
ErrCode Squeeze(char *_str1, const char *_str2);

/*
	Description: search the position of _str2 in _str1.
	Input: _str1 - the string to to be scanned, _str2 - the string to scan in _str1.
	Return value: returns the position of the first occurence or -1 if _str1 doesn't contains _str2.
*/
int Location(char *_str1, char *_str2);


#endif
