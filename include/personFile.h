#include <stdio.h>

typedef struct person person;

typedef int ErrCode;

enum
{
	LENGTH = 200,
	ERR_FILE_NOT_OPEN = -1,
	SUCCEEDED = 0
};


/*
	Description: create a new person and insert its details to a file.
	Input: _fileName - the name of the file, _numOfPerson - the number of persons to create and insert to the file.
	Return: return error code, ERR_FILE_NOT_OPEN - if the file fails to open, SUCCEEDED - on success.
*/
ErrCode CreatePersons(char *_fileName, int _numOfPerson);

/*
	Description: prints all the details of the persons from the file.
	Input: _fileName - the name of the file.
	Return: return error code, ERR_FILE_NOT_OPEN - if the file fails to open, SUCCEEDED - on success.
*/
ErrCode PrintPersons(char *_fileName);
