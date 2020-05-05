#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textFilesE.h"

#define LINE_LENGTH 50

#define IS_NOT_EXIST(_listWord) (NULL == _listWord || (*_listWord).m_MagicNumber != MAGIC_NUMBER)

typedef struct ListWord
{
	size_t m_MagicNumber;
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

static void CheckLineChars(char *_ch,char *_letterArr, int *_countArr)
{
	int position, i, size = strlen(_ch);

	for(i = 0;i < size;++i)
	{
		if((-1) != (position = GetPosition(_ch[i])))
		{
			_letterArr[position] = _ch[i];
			_countArr[position]++;
		}	
	}

}

static void ScanFileChars(FILE *file)
{
	char letterArr[52], ch[LINE_LENGTH];
	int countArr[52] = {0};
	
	fgets(ch,LINE_LENGTH,file);

	while(!feof(file))
	{
		CheckLineChars(ch,letterArr,countArr);
		
		fgets(ch,LINE_LENGTH,file);
	}

	PrintResult(letterArr,countArr,52);

}

ErrCode CountChars(char *_fileName)
{
	FILE *file;
	
	file = fopen(_fileName,"r");
	if(NULL == file)
	{
		return ERR_FAILED_TO_OPEN;
	}

	ScanFileChars(file);
	
	fclose(file);

	return SUCCEEDED;
}

/* count all words */

static ListWord* CheckIfExist(char *_word, ListWord *_listWord)
{
	while(_listWord && (0 >= strcmp(_listWord->m_word,_word)))
	{
		if(!strcmp(_listWord->m_word,_word))
		{
			return _listWord;
		}
	
		_listWord = _listWord->m_next;
	}

	return NULL;
}

static ListWord* SetAtPosition(ListWord *_listWord, ListWord *_newWord)
{
	ListWord *temp = _listWord;

	if(IS_NOT_EXIST(_listWord) || (0 < strcmp(_listWord->m_word,_newWord->m_word)))
	{
		_newWord->m_next = _listWord;
		return _newWord;
	}

	while(!IS_NOT_EXIST(temp->m_next) && (0 > strcmp(temp->m_next->m_word,_newWord->m_word)))
	{
		temp = temp->m_next;
	}

	if(!IS_NOT_EXIST(temp->m_next))
	{
		_newWord->m_next = temp->m_next;
	}
	
	temp->m_next = _newWord; 

	return _listWord;
}

static ListWord* CreateNewWord(char *_word, ListWord *_listWord)
{
	ListWord *newWord;

	newWord = (ListWord *)malloc(sizeof(ListWord));
	if(NULL == newWord)
	{
		return NULL;
	}

	strcpy(newWord->m_word,_word);
	newWord->m_next = NULL;
	newWord->m_count = 1;
	newWord->m_MagicNumber = MAGIC_NUMBER;

	return SetAtPosition(_listWord,newWord);
}

static void DestroyListR(ListWord *_listWord)
{
	if(IS_NOT_EXIST(_listWord))
	{
		return;
	}

	DestroyListR(_listWord->m_next);

	_listWord->m_MagicNumber = NO_MAGIC_NUMBER;
	free(_listWord);
	
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
			_listWord = CreateNewWord(word, _listWord);
			if(NULL == _listWord)
			{
				return NULL;
			}
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
	if(IS_NOT_EXIST(_listWord))
	{
		return;
	}

	printf("%-10s \t %d \n", _listWord->m_word, _listWord->m_count);

	PrintListR(_listWord->m_next);
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

	if(IS_NOT_EXIST(listWord))
	{
		return ERR_OVERFLOW;
	}

	PrintListR(listWord);

	DestroyListR(listWord);

	return SUCCEEDED; 
}


