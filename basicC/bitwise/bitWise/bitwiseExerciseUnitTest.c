#include <stdio.h>
#include <stdlib.h>
#include "bitwiseExercise.h"

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

/* INVERT BIT */

Result TestInvertBits_Valid()
{
	unsigned char ch = 'A';

	if(2 != BitCount(ch) || 6 != BitCount((int)InvertBits(ch)))
	{
		return FAILED;
	}

	return SUCCEDD;
}
 
/* ROTATE BITS TO RIGHT */

Result TestRotateRightBits_Valid()
{
	unsigned char ch = 'A';

	if('(' != RotateRightBits(ch,3))
	{
		return FAILED;
	}

	return SUCCEDD;
}

/* SET BITS */

Result TestSetBits_ValidN3()
{
	unsigned char a = 'A', b = 'B';

	if('!' != SetBits(a,6,3,b))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestSetBits_ValidN0()
{
	unsigned char a = 'A', b = 'B';

	if('A' != SetBits(a,6,0,b))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestSetBits_ValidN8()
{
	unsigned char a = 'A', b = 'B';

	if('B' != SetBits(a,7,8,b))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestSetBits_ValidN9()
{
	unsigned char a = 'A', b = 'B';

	if('B' != SetBits(a,7,9,b))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestSetBits_N9P5()
{
	unsigned char a = 'A', b = 'B';

	if('P' != SetBits(a,5,8,b))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestSetBits_PNeg()
{
	unsigned char a = 'A', b = 'B';

	if('A' != SetBits(a,-1,5,b))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestSetBits_PBig()
{
	unsigned char a = 'A', b = 'B';

	if('A' != SetBits(a,9,5,b))
	{
		return FAILED;
	}

	return SUCCEDD;
}

/* COMPRESS STRING */

Result TestCompress_ValidEvenSize()
{
	char str[] = "cjba";

	if(SUCCEEDED != Compress(str))
	{
		return FAILED;
	}

	if(':' != str[0])
	{
		return FAILED;
	}
	if('!' != str[1])
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCompress_ValidOddSize()
{
	char str[] = "bhg";

	if(SUCCEEDED != Compress(str))
	{
		return FAILED;
	}

	if('(' != str[0])
	{
		return FAILED;
	}
	if('p' != str[1])
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCompress_NotValid()
{
	char str[] = "abAcd";

	if(ERR_ILLEGAL_INPUT == Compress(str))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* SET BITS INT */

Result TestSetBitsInt_ValidOne()
{
	unsigned int afterSet, beforeSet = 100001;

	afterSet = SetBitsInt(beforeSet,5,17,1);

	if(262113 != afterSet)
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestSetBitsInt_ValidZero()
{
	unsigned int afterSet, beforeSet = 100001;

	afterSet = SetBitsInt(beforeSet,5,17,0);

	if(1 != afterSet)
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestSetBitsInt_NotValidSmallerTo()
{
	unsigned int afterSet, beforeSet = 100001;

	afterSet = SetBitsInt(beforeSet,5,3,0);

	if(beforeSet == afterSet)
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestSetBitsInt_NotValidBiggerFrom()
{
	unsigned int afterSet, beforeSet = 100001;

	afterSet = SetBitsInt(beforeSet,25,17,0);

	if(beforeSet == afterSet)
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestSetBitsInt_NotValidTo()
{
	unsigned int afterSet, beforeSet = 100001;

	afterSet = SetBitsInt(beforeSet,5,32,0);

	if(beforeSet == afterSet)
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestSetBitsInt_NotValidFrom()
{
	unsigned int afterSet, beforeSet = 100001;

	afterSet = SetBitsInt(beforeSet,33,17,0);

	if(beforeSet == afterSet)
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* COMPRESS STRING BIT FIELD */

Result TestCompressBitF_ValidEvenSize()
{
	char str[] = "cjba";

	if(SUCCEEDED != CompressBitF(str))
	{
		return FAILED;
	}

	if(':' != str[0])
	{
		return FAILED;
	}
	if('!' != str[1])
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCompressBitF_ValidOddSize()
{
	char str[] = "bhg";

	if(SUCCEEDED != CompressBitF(str))
	{
		return FAILED;
	}

	if('(' != str[0])
	{
		return FAILED;
	}
	if('p' != str[1])
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCompressBitF_NotValid()
{
	char str[] = "abAcd";

	if(ERR_ILLEGAL_INPUT == CompressBitF(str))
	{
		return SUCCEDD;
	}

	return FAILED;
}

int main()
{
	Result res;

	/*count bits*/
	/*POS*/
	res = TestBitCount_Valid();
	printf("\n%-40s %s \n", "TestBitCount_Valid: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	/*NEG*/
	res = TestBitCount_ValidZero();
	printf("\n%-40s %s \n", "TestBitCount_ValidZero: ", (SUCCEDD == res) ? "succedded" : "failed");

	/*Invert bits*/
	/*POS*/
	res = TestInvertBits_Valid();
	printf("\n%-40s %s \n", "TestInvertBits_Valid: ", (SUCCEDD == res) ? "succedded" : "failed");

	/*Rotate bits*/
	/*POS*/
	res = TestRotateRightBits_Valid();
	printf("\n%-40s %s \n", "TestRotateRightBits_Valid: ", (SUCCEDD == res) ? "succedded" : "failed");

	/*Set bits*/
	/*POS*/
	res = TestSetBits_ValidN3();
	printf("\n%-40s %s \n", "TestSetBits_ValidN3: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestSetBits_ValidN0();
	printf("\n%-40s %s \n", "TestSetBits_ValidN0: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestSetBits_ValidN8();
	printf("\n%-40s %s \n", "TestSetBits_ValidN8: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestSetBits_ValidN9();
	printf("\n%-40s %s \n", "TestSetBits_ValidN9: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	/*NEG*/
	res = TestSetBits_N9P5();
	printf("\n%-40s %s \n", "TestSetBits_N9P5: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestSetBits_PNeg();
	printf("\n%-40s %s \n", "TestSetBits_PNeg: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestSetBits_PBig();
	printf("\n%-40s %s \n", "TestSetBits_PBig: ", (SUCCEDD == res) ? "succedded" : "failed");

	/*Compress string*/
	/*POS*/
	res = TestCompress_ValidEvenSize();
	printf("\n%-40s %s \n", "TestCompress_ValidEvenSize: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestCompress_ValidOddSize();
	printf("\n%-40s %s \n", "TestCompress_ValidOddSize: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	/*NEG*/
	res = TestCompress_NotValid();
	printf("\n%-40s %s \n", "TestCompress_NotValid: ", (SUCCEDD == res) ? "succedded" : "failed");

	/*Compress string*/
	/*POS*/
	res = TestSetBitsInt_ValidOne();
	printf("\n%-40s %s \n", "TestSetBitsInt_ValidOne: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestSetBitsInt_ValidZero();
	printf("\n%-40s %s \n", "TestSetBitsInt_ValidZero: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	/*NEG*/
	res = TestSetBitsInt_NotValidSmallerTo();
	printf("\n%-40s %s \n", "TestSetBitsInt_NotValidSmallerTo: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestSetBitsInt_NotValidBiggerFrom();
	printf("\n%-40s %s \n", "TestSetBitsInt_NotValidBiggerFrom: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestSetBitsInt_NotValidTo();
	printf("\n%-40s %s \n", "TestSetBitsInt_NotValidTo: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestSetBitsInt_NotValidFrom();
	printf("\n%-40s %s \n", "TestSetBitsInt_NotValidFrom: ", (SUCCEDD == res) ? "succedded" : "failed");

	/*Compress string with bit field*/
	/*POS*/
	res = TestCompressBitF_ValidEvenSize();
	printf("\n%-40s %s \n", "TestCompressBitF_ValidEvenSize: ", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestCompressBitF_ValidOddSize();
	printf("\n%-40s %s \n", "TestCompressBitF_ValidOddSize: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	/*NEG*/
	res = TestCompressBitF_NotValid();
	printf("\n%-40s %s \n", "TestCompressBitF_NotValid: ", (SUCCEDD == res) ? "succedded" : "failed");


	return 0;
}






















