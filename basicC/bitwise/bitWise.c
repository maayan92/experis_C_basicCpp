#include <stdio.h>

#define INT_BIT 8
#define BIT_FIELD 4

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
	int i, newNum[INT_BIT];
	
	printf("\nthe number in hex 0x");
	
	for(i = 0;i < INT_BIT;++i)
	{
		newNum[i] = SetBitField(_num);

		_num >>=  4;
	}
	
	for(i = INT_BIT-1;i >= 0;--i)
	{
		printHexVal(newNum[i]);
	}
}

/* COUNT BITS */

size_t BitCount(size_t _num)
{
	size_t count = 0;
	int i, mask = (_num);

	for(i = 0;i < sizeof(int)*INT_BIT;++i)
	{
		count += ((_num >> i) & mask);
	}

	return count;
}

/* FLIP BITS */

int Flip(int _num, size_t _firstBit, size_t _secondBit)
{
	_firstBit %= sizeof(int)*INT_BIT;
	_secondBit %= sizeof(int)*INT_BIT;

	_num ^= (1 << _firstBit);
	_num ^= (1 << _secondBit);

	return _num;
}

int FlipByRange(int _num, int _from, int _to)
{
	_from %= sizeof(int)*INT_BIT;
	_to %= sizeof(int)*INT_BIT;
	
	while(_from <= _to)
	{
		_num ^= (1 << _from);
		++_from;
	}
	
	return _num;
}

/* ROTATE BITS */

int RotateRightBits(int _num, size_t _n)
{
	_n %= sizeof(int)*INT_BIT;
	while(_n)
	{
		_num = ptrMoveSide(_num);
		
		--_n;
	}

	return _num;


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
	
	for(i = 0;i < sizeof(int)*INT_BIT;++i)
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

static int GoOnBits(int _num, size_t _n, int(*ptrMoveSide)(int))
{
	
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











