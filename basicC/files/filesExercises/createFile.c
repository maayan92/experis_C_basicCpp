#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "createFile.h"

static void PrintTheLines(FILE *_file, size_t _numOfLines)
{
	char str[LENGTH];

	while(0 < _numOfLines && !feof(_file))
	{
		if(NULL != fgets(str, LENGTH, _file))
		{
			printf("%s",str);
		}		

		--_numOfLines;
	}
}

ErrCode PrintFirstN(size_t _numOfLines, char *_fileName)
{
	FILE *_file;

	_file = fopen(_fileName,"r");

	if(0 > _numOfLines || NULL == _fileName)
	{
		return ILLEGAL_INPUT;
	}

	if(NULL == _file)
	{
		return ERR_FILE_NOT_OPEN;
	}

	PrintTheLines(_file,_numOfLines);

	fclose(_file);

	return SUCCESS;
	
}

static void PutLinesInArr(FILE *_file, char **_lines, int _size)
{
	int i = 0;
	fgets(_lines[i%_size], LENGTH, _file);

	while(!feof(_file))
	{
		++i;
		fgets(_lines[i%_size], LENGTH, _file);
	}

}

static void PrintArrLines(char **_lines, int _size)
{
	int i;

	for(i = 0;i < _size && '\0' != _lines[i];++i)
	{
		printf("%s\n",_lines[i]);
	}
}

ErrCode PrintLastN(size_t _numOfLines, char *_fileName)
{
	FILE *_file;
	char *_linesToPrint;

	_file = fopen(_fileName,"r");
	
	if(0 > _numOfLines || NULL == _fileName)
	{
		return ILLEGAL_INPUT;
	}

	if(NULL == _file)
	{
		return ERR_FILE_NOT_OPEN;
	}

	_linesToPrint = (char*)calloc(_numOfLines,sizeof(char));

	PutLinesInArr(_file,&_linesToPrint,_numOfLines);

	PrintArrLines(&_linesToPrint,_numOfLines);

	fclose(_file);

	return SUCCESS;
}

static int CheckIfExist(FILE *_firstFile, FILE *_secondFile, char *_str)
{
	char secondStr[LENGTH];

	fgets(secondStr, LENGTH, _secondFile);

	while(!feof(_secondFile))
	{	
		if(0 == strcmp(_str,secondStr))
		{
			return  1;
			
		}

		fgets(secondStr, LENGTH, _secondFile);
	}

	return 0;
}

static void CheckEveryLine(FILE *_firstFile, FILE *_secondFile, char *_filename)
{
	char firstStr[LENGTH];

	fgets(firstStr, LENGTH, _firstFile);

	while(!feof(_firstFile))
	{
		if(0 == CheckIfExist(_firstFile,_secondFile,firstStr))
		{
			printf("%s",firstStr);
		}

		fgets(firstStr, LENGTH, _firstFile);

		_secondFile = fopen(_filename,"r");
	}
} 

ErrCode CompareFiles(char *_fisrtFileName, char *_secondFileName)
{
	FILE *_firstFile, *_secondFile;

	_firstFile = fopen(_fisrtFileName,"r");
	_secondFile = fopen(_secondFileName,"r");

	if(NULL == _firstFile || NULL == _secondFile)
	{
		return ERR_FILE_NOT_OPEN;
	}

	CheckEveryLine(_firstFile,_secondFile,"clients2.txt");

	_firstFile = fopen("clients.txt","r");

	CheckEveryLine(_secondFile,_firstFile,"clients.txt");

	printf("\n");

	fclose(_firstFile);
	fclose(_secondFile);

	return SUCCESS;
}

static int CheckWords(FILE *_file,char *_word)
{
	char str[LENGTH];
	int count = 0;

	while(!feof(_file))
	{
		fscanf(_file, "%s", str);
	
		if(0 == strcmp(str,_word))
		{
			++count;
		}
	}
	
	return count;
}

int NumOfOccurrences(char *_word, char *_fileName)
{
	FILE *_file;

	_file = fopen(_fileName,"r");

	if(NULL == _file)
	{
		return ERR_FILE_NOT_OPEN;
	}

	return CheckWords(_file,_word);
}


