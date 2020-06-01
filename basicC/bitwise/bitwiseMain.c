#include <stdio.h>
#include "bitWise.h"

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

/* BIT COUNT */

Result TestBitCount_Valid()
{
	size_t num = 171;

	if(5 != BitCount(num))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestBitCount_ValidZero()
{
	size_t num = 0;

	if(0 != BitCount(num))
	{
		return FAILED;
	}

	return SUCCEDD;
}

/* FLIP */

Result TestFlip_Valid()
{
	int num = 211;

	if(213 != Flip(num,1,2))
	{
		return FAILED;
	}

	return SUCCEDD;
}
 
/* FLIP BY RANGE */

Result TestFlipByRange_Valid()
{
	int num = 103;

	if(91 != FlipByRange(num,2,5))
	{
		return FAILED;
	}

	return SUCCEDD;
}
 
/* ROTATE BITS TO RIGHT */

Result TestRotateRightBits_Valid()
{
	int num = 103;

	if(236 != RotateRightBits(num,3))
	{
		return FAILED;
	}

	return SUCCEDD;
}
 
/* ROTATE BITS TO LEFT */

Result TestRotateLeftBits_Valid()
{
	int num = 211;

	if(158 != RotateLeftBits(num,3))
	{
		return FAILED;
	}

	return SUCCEDD;
}
 
/* ROTATE BITS TO LEFT */

Result TestComposeNumToNum_Valid()
{
	int num = 211, num2 = 61;

	if(272 != ComposeNumToNum(num,num2))
	{
		return FAILED;
	}

	return SUCCEDD;
}

/* PRINT IN HEX */

Result TestPrintInHex_Valid()
{
	size_t num = 171;

	PrintInHex(num);

	return SUCCEDD;
}

static void PrintRes(char *_str, Result(*ptrPrint)(void))
{
	static int count = 0;
	++count;
	
	printf("\n%d. %-40s \t %s \n", count, _str, (SUCCEDD == (*ptrPrint)()) ? "succedded" : "failed");
}


int main()
{
	/*Count 1 bit*/
	PrintRes("TestBitCount_Valid",TestBitCount_Valid);
	PrintRes("TestBitCount_ValidZero",TestBitCount_ValidZero);
	
	/*Flip bits*/
	PrintRes("TestFlip_Valid",TestFlip_Valid);
	
	/*Flip in range*/
	PrintRes("TestFlipByRange_Valid",TestFlipByRange_Valid);
	
	/*Rotate bits to right*/
	PrintRes("TestRotateRightBits_Valid",TestRotateRightBits_Valid);
	
	/*Rotate bits to left*/
	PrintRes("TestRotateLeftBits_Valid",TestRotateLeftBits_Valid);
	
	/*Compose two numbers*/
	PrintRes("TestComposeNumToNum_Valid",TestComposeNumToNum_Valid);

	/*Print in hex*/
	PrintRes("TestPrintInHex_Valid",TestPrintInHex_Valid);
	
	
	
	return 0;
}
