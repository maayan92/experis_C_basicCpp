#include <stdio.h>
#include <string.h>
#include "squeezeAndLocation.h"

enum
{
	false,
	true
};

/* SQUEEZE */
 
static void CatString(char *_str1, const char *_str2)
{
	char newStr[LENGTH] = "", *token;

	token = strtok(_str1,_str2);

	while(NULL != token)
	{
		strcat(newStr,token);
		token = strtok(NULL,_str2);
	}

	strcpy(_str1,newStr);
}

ErrCode Squeeze(char *_str1, const char *_str2)
{

	if(NULL == _str1)
	{
		return ERR_NOT_INITIALIZE;
	}

	if(NULL != _str2)
	{
		CatString(_str1,_str2);
	}
	
	return SUCCEEDED;
}

/* LOCATION */
/*
static int IsExist(char *_str1, char *_str2, int _position, int _size)
{
	int i = 0, size2 = strlen(_str2);

	while(i < size2 && '\n' != _str2[i] && _position < _size)
	{
		if(_str1[_position] != _str2[i])
		{
			return false;
		}

		++_position;
		++i;
	}
	
	return true;
}
*/
static int FindPosition(const char *_str1, const char *_str2)
{
	int i = 0, size = strlen(_str1), size2 = strlen(_str2); 
	char *res;
	res = memchr(_str1,_str1[0],size);

	while(i < size && '\n' != _str1[i])
	{
		
		if(_str1[i] == _str2[0])
		{
			res = memchr(res,_str2[0],size);
			if(!strncmp(res,_str2,size2))
			{
				return i;
			}
		}

		++i;
	}
	
	return -1;
}

int Location(const char *_str1, const char *_str2)
{

	if(NULL == _str1 || NULL == _str2)
	{
		return -1;
	}

	return FindPosition(_str1, _str2);
}








