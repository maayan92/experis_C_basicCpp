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
unsigned char RotateRightBits(unsigned char _ch, size_t _n);

/*
	Description: set the last _n bits of char y in char x at the positions _p and descending.
	Input: _x - the char that would be changed, _p - the first position, _n - number of bits, _y - the char the function takes the last _n bits from.
	Return value: return the new char of _x after the changes.
*/
unsigned char SetBits(unsigned char _x, int _p, int _n, unsigned char _y);

/*
	Description: compress string from 8 bits to 4 bits. 
	Input: _str - the string that would be compressed, should be between 'a' to 'o'.
	Return value: return error code, ERR_ILLEGAL_INPUT - if there is a char that not in the range, SUCCEEDED - on success.
*/
ErrCode Compress(char *_str);

/*
	Description: compress string from 8 bits to 4 bits. 
	Input: _str - the string that would be compressed, should be between 'a' to 'o'.
	Return value: return error code, ERR_ILLEGAL_INPUT - if there is a char that not in the range, SUCCEEDED - on success.
*/
ErrCode CompressBitF(char *_str);

/*
	Description: set the bit _value in _w at the positions _from and descending to _to.
	Input: _w - the number that would be changed, _from - the first position, _to - the last position, _value - the bit that would be set. 
	Return value: return the new number of _x after the changes.
*/
unsigned int SetBitsInt(unsigned int _w, size_t _from, size_t _to, int _value);

/*
	Description: print the binary value of a decimal value.
	Input: _ch - the char value that would be printed.
	Return value: nothing returns.
*/
/* PrintAsBinaryChar is only for debug */
void PrintAsBinaryChar(unsigned char _ch);

/*
	Description: print the binary value of a decimal value.
	Input: _num - the decimal number.
	Return value: nothing returns.
*/
/* PrintAsBinaryInt is only for debug */
void PrintAsBinaryInt(unsigned int _num);



#endif
