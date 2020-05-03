#include <stdio.h>
#include <string.h>
#include "StringExercise.h"

void EachWordInLine(char *_str)
{
	int i;

	for(i = 0;i < strlen(_str);++i)
	{
		if(' ' == *(_str + i))
		{
			printf("\n");
			++i;
		}
		
		printf("%c",*(_str + i));
	}
}

void ReverseStr(char *_str)
{
	int i;

	for(i = strlen(_str);i >= 0;--i)
	{
		printf("%c",*(_str + i));
	}

	printf("\n");
}

int Power(int _num, int _pow)
{
	int _sum = 1;

	while(0 < _pow)
	{
		_sum *= _num;
		--_pow;
	}

	return _sum;
}

void BinaryOrDecimal(int _num, char _type)
{
	int sum = 0, i;

	if('d' == _type)
	{	
		i = 1;

		printf("The decimal number of %d is ",_num);

		while(0 < _num)
		{
			sum += (_num%2)*i;

			i *= 10;
			_num /= 2;
		}

	}

	else
	{
		i = 0;

		printf("The binary decimal number of %d is ",_num);

		while(0 < _num)
		{
			sum += (_num%10)*Power(2,i);

			++i;
			_num /= 10;
		}
	}

	printf("%d \n", sum);
}

void TrimSpaces(char *_str)
{
	int i = 0, count = 1;
	char *temp;

	while(i < strlen(_str))
	{	
		if(' ' == *(_str + i))
		{
			while(' ' == *(_str + i))
			{
				++i;
				count++;
			}

			memmove(_str, " ", count);
		}

		++i;

	}

	printf("%s \n", _str);
	
}












