#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bracketsString.h"

static int CompareBrackets(Stack *_stack, int _ch1)
{
	int ch2;
	ErrCode err;

	err = StackPop(_stack,&ch2);

	if(SUCCEEDED != err)
	{
		return false;
	}

	switch (ch2)
	{
		case '{':

			if('}' == _ch1)
			{
				return true;
			}

			break;

		case '(':

			if(')' == _ch1)
			{
				return true;
			}

			break;	

		default:

			if(']' == _ch1)
			{
				return true;
			}

			break;	
	}

	return false;
}

int ValidBrackets(char *_str)
{
	Stack *stack;
	int i = 0, isValid = true;
	size_t initialSize = strlen(_str)/2;
	ErrCode err;

	stack = StackCreate(initialSize,initialSize);

	if(NULL == stack)
	{
		return false;	
	}

	while('\0' != _str[i] && isValid)
	{
		if('{' == _str[i] || '(' == _str[i] || '[' == _str[i])
		{
			err = StackPush(stack,_str[i]);

			if(SUCCEEDED != err)
			{
				return false;
			}
		}
		else
		{
			isValid = CompareBrackets(stack,_str[i]);
		}

		++i;
	}

	return isValid;

}
