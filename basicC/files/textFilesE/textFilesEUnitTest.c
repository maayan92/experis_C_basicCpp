#include <stdio.h>
#include "textFilesE.h"

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

/* COUNT WORD */

Result TestCountWordValid_SmallFile()
{

	if(2 != CountWord("details.txt"))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCountWordValid_BigFile()
{

	if(58 != CountWord("details1.txt"))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCountWord_FileNameNValid()
{

	if(CountWord("details1"))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCountWordNULL()
{

	if(CountWord(NULL))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCountWordNotExist()
{
	
	if(CountWord("detail.txt"))
	{
		return FAILED;
	}

	return SUCCEDD;
}

/* COUNT ALL CHARS */

Result TestCountChar_FileNameNValid()
{

	if(CountWord("details1"))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCountCharNULL()
{

	if(CountWord(NULL))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCountCharNotExist()
{
	
	if(CountWord("detail.txt"))
	{
		return FAILED;
	}

	return SUCCEDD;
}

/* COUNT ALL WORDS */

Result TestCountAllWords_FileNameNValid()
{

	if(CountWord("details1"))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCountAllWordsNULL()
{

	if(CountWord(NULL))
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestCountAllWordsNotExist()
{
	
	if(CountWord("detail.txt"))
	{
		return FAILED;
	}

	return SUCCEDD;
}

int main()
{
	Result res;

	/*Count word*/
	/*POS*/
	res = TestCountWordValid_SmallFile();
	printf("\nTestCountWordValid_SmallFile: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");

	res = TestCountWordValid_BigFile();
	printf("\nTestCountWordValid_SmallFile: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestCountWord_FileNameNValid();
	printf("\nTestCountWord_FileNameNValid: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");
	
	res = TestCountWordNULL();
	printf("\nTestCountWordNULL: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");

	res = TestCountWordNotExist();
	printf("\nTestCountWordNotExist: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");

	/*Count all chars*/
	/*NEG*/
	res = TestCountChar_FileNameNValid();
	printf("\nTestCountWord_FileNameNValid: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");
	
	res = TestCountCharNULL();
	printf("\nTestCountWordNULL: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");

	res = TestCountCharNotExist();
	printf("\nTestCountWordNotExist: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");

	/*Count all words*/
	/*NEG*/
	res = TestCountAllWords_FileNameNValid();
	printf("\nTestCountWord_FileNameNValid: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");
	
	res = TestCountAllWordsNULL();
	printf("\nTestCountWordNULL: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");

	res = TestCountAllWordsNotExist();
	printf("\nTestCountWordNotExist: \t %s \n",(SUCCEDD == res) ? "succedded" : "failed");

	/*Count all chars*/
	/*POS*/
	printf("\ncount all chars: \n");
	CountChars("iso_8859-1.txt");
	
	/*Count all words*/
	/*POS*/
	printf("\ncount all words: \n");
	CountAllWords("iso_8859-1.txt");


	return 0;
}



