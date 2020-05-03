#include <stdio.h>

typedef int ErrCode;

enum
{
	LENGTH = 200,
	ERR_FILE_NOT_OPEN = -1,
	ILLEGAL_INPUT = -2,
	SUCCESS = 1
};


/*
	Description: prints the first n lines from the file.
	Input: _file - the file the function reads from, _n - the number of lines to print, must be positive.
	Return: return ErrCode , ERR_FILE_NOT_OPEN if the file failed to open or SUCCESS.
*/
ErrCode PrintFirstN(size_t _numOfLines, char *_fileName);

/*
	Description: prints the last n lines from the file.
	Input: _file - the file the function reads from, _n - the number of lines to print, must be positive.
	Return: return ErrCode , ERR_FILE_NOT_OPEN if the file failed to open or SUCCESS.
*/
ErrCode PrintLastN(size_t _numOfLines, char *_fileName);

/*
	Description: compare two files and print the different lines.
	Input: _firstFile , _secondFile - the two file the function compare.
	Return: return ErrCode, ERR_FILE_NOT_OPEN if the file failed to open or SUCCESS.
*/
ErrCode CompareFiles(char *_fisrtFileName, char *_secondFileName);

/*
	Description: gets a word and check how many times it occur in the file
	Input: _file - the file the function reads from, _word - the word that is checked.
	Return: return the number of times the _word occur in the file.
*/
int NumOfOccurrences(char *_word, char *_fileName);

