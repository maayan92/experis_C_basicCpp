#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringE.h"

static void SwapChars(char *_c1, char *_c2)
{
	char temp = *_c1;
	*_c1 = *_c2;
	*_c2 = temp;
}

void ReverseString(char *_str)
{
	int size = strlen(_str)-1, i = 0;

	while(i < size)
	{
		SwapChars(&_str[i],&_str[size]);

		--size;
		++i;
	}
}

int MyAtoI(char *_str)
{
	int i = 0, num = 0, size = strlen(_str), minus = 1;

	while((i < size) && (_str[i] < '0' || _str[i] > '9'))
	{
		if(_str[i] == '-')
		{
			minus = -1;
		}
		++i;
	}
	while((i < size) && (_str[i] > '0' && _str[i] < '9'))
	{
		num *= 10;
		num += (_str[i]-48);
		++i;
	}

	return num*minus;
}

int ReverseNum(int _num)
{
	int temp = 0;

	while(_num)
	{
		temp *= 10;
		temp += (_num % 10);
		_num /= 10;
	}

	return temp;
}

char* MyItoA(int _num)
{
	char *str = (char *)malloc(LENGTH*sizeof(char));
	int i = 0;

	if(0 > _num)
	{
		_num *= (-1);
		str[i++] = '-';
	}

	_num = ReverseNum(_num);

	while(_num)
	{
		str[i] = (char)(_num % 10) + '0';

		_num /= 10;
		++i;
	}

	str[i] = '\0';

	return str;
}











