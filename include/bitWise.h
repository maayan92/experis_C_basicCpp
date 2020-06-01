#ifndef __BIT_WISE__
#define __BIT_WISE__


/*
	Description: print the number in hexadecimal.
	Input: _num - decimal number.
	Return: nothing returns.
*/
void PrintInHex(int _num);

/*
	Description: count the number of on bits.
	Input: _num - decimal number.
	Return value: return the number of on bits.
*/
size_t BitCount(size_t _num);

/*
	Description: flip the bit in specific positions.
	Input: _num - decimal number, _firstBit - position to flip bit, _secondBit - position to flip bit.
	Return: return the number after flipping.
*/
int Flip(int _num, int _firstBit, int _secondBit);

/*
	Description: flip the bit in specific range.
	Input: _num - decimal number, _firstBit - start position to flip bit, _secondBit - end position to flip bit.
	Return: return the number after flipping.
*/
int FlipByRange(int _num, int _from, int _to);

/*
	Description: rotates the _num's bits to the right _n time, without losing any bit
	Input: _num - decimal number, _n - number of rotations.
	Return: return the number after rotation.
*/
int RotateRightBits(int _num, size_t _n);

/*
	Description: rotates the _num's bits to the left _n time, without losing any bit
	Input: _num - decimal number, _n - number of rotations.
	Return: return the number after rotation.
*/
int RotateLeftBits(int _num, size_t _n);

/*
	Description: Compose two numbers.
	Input: _num1 - first decimal number, _num - second decimal number.
	Return: return the new number after the compose.
*/
int ComposeNumToNum(int _num1, int _num2);





#endif
