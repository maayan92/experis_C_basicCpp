#include <stdio.h>
#include <string.h>
#include "bitwiseExercise.h"

#define BITS 8

typedef struct statusReg
{
	unsigned char rightBit 	:4;
	unsigned char leftBit	:4;
}statusReg;

/* 
check if the bit at position _i is 0 or 1.
*/
static int TestBit(unsigned char _ch, int _i)
{
	return (_ch & (1 << _i)) ? 1 : 0;
}

/* COUNT BITS 
count the bits set to 1.
*/
size_t BitCount(size_t _num)
{
	size_t count = 0;
	int i;

	for(i = 0;i < sizeof(int)*BITS;++i)
	{

		if(0 != TestBit(_num,i))
		{
			++count;
		}

	}

	return count;
}

/* INVERT BITS */

unsigned char InvertBits(unsigned char _ch)
{
	return ~_ch;
}

/* ROTATE BITS 
rotates the char's bits to the right _n time, without losing any bit.
*/
unsigned char RotateRightBits(unsigned char _ch, size_t _n)
{
	int bit;

	if(8 < _n)
	{
		_n = 8;
	}

	while(_n)
	{
		bit = TestBit(_ch,0);

		_ch >>=  1;

		if(bit)
		{
			_ch += 128;
		}

		--_n;
	}

	return _ch;

}

/* 
sets the _n last bits of _y in _x at the positions _p->(_p - _n).
*/
unsigned char SetBits(unsigned char _x, int _p, int _n, unsigned char _y)
{
	int i;

	if(7 < _p || 0 > _p || 1 > _n)
	{
		return _x;
	}

	if(8 < _n)
	{
		_n = 8;
	}

	for(i = _n-1;i >= 0 && _p >= 0;--i)
	{
		if(0 != TestBit(_y,i))
		{
			_x |= (1 << _p);
		}
		else
		{
			_x &= ~(1 << _p);
		}	
		
		--_p;
	}

	return _x;
}

/* COMPRESS STRING */

/*
change the bits in the char _ch.
*/
static char ChangeBits(char _ch, char _newCh2)
{
	char resCh;

	resCh = SetBits(_ch,7,4,_ch);
	resCh = SetBits(resCh,3,4,_newCh2);

	return resCh;
}

/*
compress the string's chars from 8 bits to 4 bits.
*/
ErrCode Compress(char *_str)
{
	int i, j = 0, size = strlen(_str);

	for(i = 0;i < size-1;i += 2, ++j)
	{
		if('a' > _str[i] || 'o' < _str[i] || 'a' > _str[i+1] || 'o' < _str[i+1])
		{
			return ERR_ILLEGAL_INPUT;
		}
	
		_str[j] = ChangeBits(_str[i],_str[i+1]);
	}

	if(_str[i] != '\0')
	{
		_str[j] = ChangeBits(_str[i],0);
		++j;
	}
	
	_str[j] = '\0';
	
	return SUCCEEDED;	
}

/* COMPRESS STRING WITH BIT FIELD */

/*
compress two chars to one char, by compressing every char's bits from 8 to 4.
*/
static void Compress2To1(char *_currentPos, char _left, char _right)
{
	statusReg *Left, *Right, *strS;

	strS = _currentPos;
	Right = &_right;
	Left = &_left;
	strS->leftBit = Left->rightBit;
	strS->rightBit = Right->rightBit;
}

static int IsLegallInput(char _ch1, char _ch2)
{
	return ('a' > _ch1 || 'o' < _ch1 || ('\0' != _ch2 && ('a' > _ch2 || 'o' < _ch2)));
}

/*
compress the string's chars from 8 bits to 4 bits, using bit field.
*/

ErrCode CompressBitF(char *_str)
{
	int i, j = 0, size = strlen(_str);

	for(i = 0;i < size;i += 2, ++j)
	{
		if(IsLegallInput(_str[i],_str[i+1]))
		{
			return ERR_ILLEGAL_INPUT;
		}

		Compress2To1(&_str[j],_str[i],_str[i+1]);
	}
	
	_str[j] = '\0';
	
	return SUCCEEDED;	
}

/* SET BIT INT 
set the bit _value in _w bits at the positions _from->_to.
*/
unsigned int SetBitsInt(unsigned int _w, size_t _from, size_t _to, int _value)
{
	if(31 < _from || 31 < _to || (_value != 0 && _value != 1))
	{
		return _w;
	}

	while(_from <= _to)
	{
		if(_value)
		{
			_w |= (1 << _from);
		}
		else
		{
			_w &= ~(1 << _from);
		}	

		++_from;
	}

	return _w;
}

/* PRINT */

void PrintAsBinaryChar(unsigned char _ch)
{
	int i;

	for(i = sizeof(unsigned char)*BITS-1;i >= 0;--i)
	{
		printf("%d ", TestBit(_ch,i));
	}

	printf("\n");
}

void PrintAsBinaryInt(unsigned int _num)
{
	int i;

	for(i = sizeof(unsigned int)*BITS-1;i >= 0;--i)
	{
		printf("%d ", ((_num & (1 << i)) ? 1 : 0));
	}

	printf("\n");
}




