#include <stdio.h>
#include <string.h>
#include "squeezeAndLocation.h"

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

/* SQUEEZE STRING */

Result TestSqueeze_Valid()
{
	char str1[LENGTH] = "Characters squeeze from string";
	char str2[LENGTH] = "csa";
	char res[LENGTH] = "Chrter queeze from tring";

	if(SUCCEEDED != Squeeze(str1,str2))
	{
		return FAILED;
	}

	if(0 != strcmp(str1,res))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestSqueeze_NULLfirstStr()
{
	char str[LENGTH] = "od";

	if(ERR_NOT_INITIALIZE == Squeeze(NULL,str))
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestSqueeze_NULLsecondStr()
{
	char str[LENGTH] = "Characters squeeze from string";

	if(SUCCEEDED == Squeeze(str,NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* FIND LOCATION */

Result TestLocation_Valid()
{
	char str1[LENGTH] = "string search in another string";
	char str2[LENGTH] = "another";

	if(17 != Location(str1,str2))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestLocation_NotExist()
{
	char str1[LENGTH] = "string search in another string";
	char str2[LENGTH] = "anotherr";

	if(-1 == Location(str1,str2))
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestLocation_NULLfirstStr()
{
	char str[LENGTH] = "another";

	if(-1 == Location(NULL,str))
	{
		return SUCCEDD;
	}

	return FAILED;
}

Result TestLocation_NULLsecondStr()
{
	char str[LENGTH] = "string search in another string";

	if(-1 == Location(str,NULL))
	{
		return SUCCEDD;
	}

	return FAILED;
}


int main()
{
	Result res;

	/*Binary search*/
	/*POS*/
	res = TestSqueeze_Valid();
	printf("\n%-40s %s \n", "TestSqueeze_Valid: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	/*NEG*/
	res = TestSqueeze_NULLfirstStr();
	printf("\n%-40s %s \n", "TestSqueeze_NULLfirstStr: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	res = TestSqueeze_NULLsecondStr();
	printf("\n%-40s %s \n", "TestSqueeze_NULLsecondStr: ", (SUCCEDD == res) ? "succedded" : "failed");

	/*Binary search*/
	/*POS*/
	res = TestLocation_Valid();
	printf("\n%-40s %s \n", "TestLocation_Valid: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	/*NEG*/
	res = TestLocation_NotExist();
	printf("\n%-40s %s \n", "TestLocation_NotExist: ", (SUCCEDD == res) ? "succedded" : "failed");
	
	res = TestLocation_NULLfirstStr();
	printf("\n%-40s %s \n", "TestLocation_NULLfirstStr: ", (SUCCEDD == res) ? "succedded" : "failed");
		
	res = TestLocation_NULLsecondStr();
	printf("\n%-40s %s \n", "TestLocation_NULLsecondStr: ", (SUCCEDD == res) ? "succedded" : "failed");


	return 0;
}












