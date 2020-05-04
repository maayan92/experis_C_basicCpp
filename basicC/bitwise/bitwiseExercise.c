#include <stdio.h>
#include <string.h>
#include "bitwiseExercise.h"

#define BITS 8

static int TestBit(unsigned char _ch, int _i)
{
	return (_ch & (1 << _i)) ? 1 : 0;
}

size_t BitCount(size_t _num)
{
	size_t count = 0;
	int i;

	for(i = 0;i < sizeof(int)*BITS;++i)
	{

		if(0 != (_num & (1 << i)))
		{
			++count;
		}

	}

	return count;
}

void PrintAsBinary(unsigned char _ch)
{
	int i;

	for(i = sizeof(unsigned char)*BITS-1;i >= 0;--i)
	{
		printf("%d ", TestBit(_ch,i));
	}

	printf("\n");
}

unsigned char InvertBits(unsigned char _ch)
{
	return ~_ch;
}

unsigned char RotateRightBits(unsigned char _ch, int _n)
{
	int bit;

	if(8 < _n)
	{
		_n = 8;
	}

	while(_n)
	{
		bit = TestBit(_ch,0);

		_ch = (_ch >> 1);

		if(bit)
		{
			_ch += 128;
		}

		--_n;
	}

	return _ch;

}

unsigned char SetBits(unsigned char x, int _p, int _n, unsigned char y)
{
	int i;

	if(7 < _p || 0 > _p || 1 > _n)
	{
		return x;
	}

	if(8 < _n)
	{
		_n = 8;
	}

	for(i = _n-1;i >= 0 && _p >= 0;--i)
	{
		if(0 != TestBit(y,i))
		{
			x |= (1 << _p);
		}
		else
		{
			x &= ~(1 << _p);
		}	
		
		--_p;
	}

	return x;
}

/*  */

static char InsertToString(char _ch, char _newCh2)
{
	char resCh;

	resCh = SetBits(_ch,7,4,_ch);

	resCh = SetBits(resCh,3,4,_newCh2);

	return resCh;

}

ErrCode Compress(char *_str)
{
	int i, j = 0, size = strlen(_str);

	for(i = 0;i < size-1;i += 2)
	{
		if('a' > _str[i] || 'o' < _str[i] || 'a' > _str[i+1] || 'o' < _str[i+1])
		{
			return ERR_ILLEGAL_INPUT;
		}
	
		_str[j] = InsertToString(_str[i],_str[i+1]);
		++j;
	}

	if(_str[i] != '\0')
	{
		_str[j] = InsertToString(_str[i],0);
		++j;
	}
	
	_str[j] = '\0';
	
	return SUCCEEDED;	
}

















