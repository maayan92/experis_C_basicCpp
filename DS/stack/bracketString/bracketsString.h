#ifndef _BRACKETS_H
#define _BRACKETS_H

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define LENGTH 200


/*
	Description: check if the string is brackets valid, must be a string of brackets.
	Input: _str - the string that would be checked.
	Return value: return true if the string is brackets valid or false if not.
*/
int ValidBrackets(char *_str);

#endif
