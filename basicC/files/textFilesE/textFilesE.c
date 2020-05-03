#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textFilesE.h"

typedef struct ListWord
{
	char m_word[LENGTH];
	int m_count;
	struct ListWord *m_next;

}ListWord;

/* count one word */

static size_t Count(FILE *_file, char *_word)
{
	int count = 0;
	char compareWord[LENGTH];

	while(!feof(_file))
	{
		fscanf(_file, "%s", compareWord);

		if(!strcmp(compareWord,_word))
		{
			++count;
		}
	}

	fclose(_file);
	return count;
}

size_t CountWord(char *_fileName)
{
	FILE *fileHead, *InFile;
	char InFileName[LENGTH], word[LENGTH];

	fileHead = fopen(_fileName,"r");
	if(NULL == fileHead)
	{
		return 0;
	}

	fscanf(fileHead, "%s%s", InFileName, word);

	fclose(fileHead);

	InFile = fopen(InFileName,"r");
	if(NULL == InFile)
	{
		return 0;
	}
	
	return Count(InFile,word);
}

/* count chars */

static int GetPosition(char _ch)
{
	int diff = ('a'-'Z');

	if(_ch >= 'A' && _ch <= 'Z')
	{
		return (_ch - 65);
	}

	if(_ch >= 'a' && _ch <= 'z')
	{
		return (_ch - 65 - diff);
	}
	
	return -1;

}

static void PrintResult(char *_letterArr, int *_countArr, int _size)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		if(0 < _countArr[i])
		{
			printf("%c \t %d \n",_letterArr[i],_countArr[i]);
		}
	}
}

ErrCode CountChars(char *_fileName)
{
	FILE *file;
	char letterArr[52], ch;
	int countArr[52] = {0}, position;

	file = fopen(_fileName,"r");
	if(NULL == file)
	{
		return ERR_FAILED_TO_OPEN;
	}

	ch = fgetc(file);

	while(!feof(file))
	{
		if((-1) != (position = GetPosition(ch)))
		{
			letterArr[position] = ch;
			countArr[position]++;
		}	

		ch = fgetc(file);	
	}

	PrintResult(letterArr,countArr,52);

	fclose(file);

	return SUCCEEDED;
}

/* count all words */

static ListWord* NewWord(char *_word, ListWord *_listWord)
{
	ListWord *newWord;

	newWord = (ListWord *)malloc(sizeof(ListWord));
	if(NULL == newWord)
	{
		return NULL;
	}

	strcpy(newWord->m_word,word);
	newWord->m_next = _listWord;
	newWord->m_count = 1;

	return newWord;
}

static ListWord* CheckIfExist(char *_word, ListWord *_listWord)
{
	while(_listWord)
	{
		if(!strcmp(_listWord->m_word,_word))
		{
			return _listWord;
		}
	
		_listWord = _listWord->m_next;
	}

	return NULL;
}

static ListWord* ScanFile(FILE *_file, ListWord *_listWord)
{
	ListWord *newWord;
	char word[LENGTH];

	while(!feof(_file))
	{
		fscanf(_file, "%s",word);

		newWord = CheckIfExist(word, _listWord);

		if(NULL == newWord)
		{
			_listWord = NewWord(word, _listWord);
		}
		else
		{
			newWord->m_count++;
		}
	}

	fclose(_file);

	return _listWord;
}

static void PrintListR(ListWord *_listWord)
{
	if(NULL == _listWord)
	{
		return;
	}

	printf("%-10s \t %d \n", _listWord->m_word, _listWord->m_count);

	PrintListR(_listWord->m_next);
}

static void DestroyListR(ListWord *_listWord)
{
	if(NULL == _listWord)
	{
		return;
	}

	DestroyListR(_listWord->m_next);

	free(_listWord);
}

ErrCode CountAllWords(char *_fileName)
{
	ListWord *listWord = NULL;
	FILE *file;

	file = fopen(_fileName, "r");
	if(NULL == file)
	{
		return ERR_FAILED_TO_OPEN;
	}

	if(feof(file))
	{
		return ERR_FILE_EMPTY;
	}

	listWord = ScanFile(file,listWord);

	if(NULL == listWord)
	{
		return ERR_OVERFLOW;
	}

	PrintListR(listWord);

	DestroyListR(listWord);

	return SUCCEEDED; 
}











