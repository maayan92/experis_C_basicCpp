#ifndef _BITWISE_H
#define _BITWISE_H

#include "ADTErrors.h"

/*
	Description: count the number of bits set to 1 in a decimal number.
	Input: _num - the decimal number.
	Return value: return the number of bits set to 1.
*/
size_t BitCount(size_t _num);

/*
	Description: inverts the bits of the char.
	Input: _ch - the char value that would be invert.
	Return value: return the new char, after inverting.
*/
unsigned char InvertBits(unsigned char _ch);

/*
	Description: rotate the bits of _ch _n time to the right, without loosing any bit.
	Input:  _ch - the char value that would be rotate, _n - the number of time the bit rotate.
	Return value: return the new char after rotated.
*/
unsigned char RotateRightBits(unsigned char _ch, int _n);

/*
	Description: set the last _n bits of char y in char x at the positions _p and descending.
	Input: x - the char that would be changed, _p - the first position, _n - 
	Return value: 
*/
unsigned char SetBits(unsigned char x, int _p, int _n, unsigned char y);

/*
	Description: compress string from 8 bits to 4 bits. 
	Input: _str - the string that would be compressed, should be between 'a' to 'o'.
	Return value: return error code, ERR_ILLEGAL_INPUT - if there is a char that not in the range, SUCCEEDED - on success.
*/
ErrCode Compress(char *_str);

/*
	Description: print the binary value of a decimal value.
	Input: _ch - the char value that would be printed.
	Return value: nothing returns.
*/
/* PrintAsBinary is only for debug */
void PrintAsBinary(unsigned char _ch);








#endif
