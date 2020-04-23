#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTErrors.h"
#include "stack.h"

#define LENGTH 200

/*
	Description: convert an infix expression to postfix.
	Input: _str - the expression that would be converted.
	Return value: return the expression as postfix, or NULL if the 
*/

char* FromInfixToPostFix(char *_str)
{
	Stack *stack;
	size_t size = strlen(_str);
	int i = 0, intCh;
	char charCh, *_newStr;

	_newStr = (char *)malloc(sizeof(char)*size);

	stack = StackCreate(size,0);

	if(NULL == stack)
	{
		return NULL;
	}

	while(i < size)
	{
	
		if((_str[i] >= '0' && _str[i] <= '9') || (_str[i] >= 'A' && _str[i] <= 'Z') || (_str[i] >= 'a' && _str[i] <= 'z'))
		{
			strncat(_newStr, &_str[i], 1); 
		}
		else if (_str[i] == '(')
		{
			StackPush(stack,_str[i]);
		}
		else if(_str[i] == ')')
		{
			while(SUCCEEDED == (StackTop(stack,&intCh)) && intCh != '(')
			{
				StackPop(stack,&intCh);
				charCh = (char)intCh;
				strncat(_newStr, &charCh, 1); 
			}
		}
		else
		{
			while(SUCCEEDED == (StackTop(stack,&intCh)) && intCh != '(' && _str[i] > intCh)
			{
				StackPop(stack,&intCh);
				charCh = (char)intCh;
				strncat(_newStr, &charCh, 1); 
			}
	
			StackPush(stack,_str[i]);
		}
		++i;
	}

	while(SUCCEEDED == StackPop(stack,&intCh))
	{
		if(intCh != '(')
		{
			charCh = (char)intCh;
			strncat(_newStr, &charCh, 1); 
		}
	}

	StackDestroy(stack);

	return _newStr;
}

int main()
{
	char str[LENGTH];

	printf("Please insert infix expression: ");
	scanf("%s",str);

	printf("The infix expression is %s \n", str);
	printf("The postfix expression is %s \n", FromInfixToPostFix(str));

	return 0;
}




