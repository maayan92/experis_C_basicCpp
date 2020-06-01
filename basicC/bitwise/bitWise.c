#include <stdio.h>

typedef struct BitField
{
	unsigned int rightBit 	:4;
}BitField;

/*check if the bit at position _i is 0 or 1.*/
static int TestBit(unsigned int _num, int _i);
/*set the first 4 bit to the bit field*/
static int SetBitField(int _num);
/*print the hexadecimal value*/
static void printHexVal(int _num);
/*flip the bit in _index position*/
static int FlipBit(int _num, int _index);

/*go on all bits*/
static int GoOnBits(int _num, size_t _n, int(*ptrMoveSide)(int));
/*move the bit to the left*/
static int LeftMove(int _num);
/*move the bit to the right*/
static int RightMove(int _num);


/* PRINT IN HEX */

void PrintInHex(int _num)
{
	int i, newNum[8];
	
	printf("\nthe number in hex 0x");
	
	for(i = 0;i < 8;++i)
	{
		newNum[i] = SetBitField(_num);

		_num >>=  4;
	}
	
	for(i = 7;i >= 0;--i)
	{
		printHexVal(newNum[i]);
	}
}

/* COUNT BITS */

size_t BitCount(size_t _num)
{
	size_t count = 0;
	int i;

	for(i = 0;i < sizeof(int)*8;++i)
	{
		if(0 != TestBit(_num,i))
		{
			++count;
		}
	}

	return count;
}

/* FLIP BITS */

int Flip(int _num, int _firstBit, int _secondBit)
{
	_num = FlipBit(_num,_firstBit);
	
	return FlipBit(_num,_secondBit);
}

int FlipByRange(int _num, int _from, int _to)
{
	while(_from <= _to)
	{
		_num = FlipBit(_num,_from);
		++_from;
	}
	
	return _num;
}

/* ROTATE BITS */

int RotateRightBits(int _num, size_t _n)
{
	return GoOnBits(_num,_n,RightMove);
}

int RotateLeftBits(int _num, size_t _n)
{
	return GoOnBits(_num,_n,LeftMove);
}

/* COMPOSE */

int ComposeNumToNum(int _num1, int _num2)
{
	int i, cary = 0, result, newNum = 0, sum;
	
	for(i = 0;i < sizeof(int)*8;++i)
	{
		sum = cary + TestBit(_num1,i) + TestBit(_num2,i);
		
		cary = sum / 2;
		result = sum % 2;
		
		newNum |= (result << i);
	}
	
	return newNum;
}


/* SUB FUNCTIONS */

static int TestBit(unsigned int _num, int _i)
{
	return (_num & (1 << _i)) ? 1 : 0;
}

static int SetBitField(int _num)
{
	BitField temp;
	
	temp.rightBit = _num;

	return temp.rightBit;
}

static void printHexVal(int _num)
{
	if(_num > 9)
	{
		printf("%c",(_num + 55));
	}
	
	else if(_num > 0)	
	{
		printf("%d",_num);
	}
}

static int FlipBit(int _num, int _index)
{
	int bit = TestBit(_num,_index);
	
	if(bit)
	{
		_num &= ~(1 << _index);
	}
	else
	{
		_num |= (1 << _index);
	}
	
	return _num;
}

static int GoOnBits(int _num, size_t _n, int(*ptrMoveSide)(int))
{
	if(8 < _n)
	{
		_n = 8;
	}

	while(_n)
	{
		_num = ptrMoveSide(_num);
		
		--_n;
	}

	return _num;
}

static int LeftMove(int _num)
{
	int bit = TestBit(_num,7);
	
	_num <<=  1;
	
	if(bit)
	{
		_num -= 255;
	}
	
	return _num;
}

static int RightMove(int _num)
{
	int bit = TestBit(_num,0);
	
	_num >>=  1;
	
	if(bit)
	{
		_num += 128;
	}
	
	return _num;
}











