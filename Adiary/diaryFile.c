#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "diaryFile.h"

struct meet
{
	float beginH;
	float endH;
	size_t room;
};

struct AD_t
{
	meet** meetingArray;
	size_t adSize;
	size_t numOfMeetings;
	size_t blockSize;
};

static void GetMeetValues(float *_beginH, float *_endH, size_t *_room)
{
	printf("Please enter begin hour:");
	scanf("%f",_beginH);
	printf("Please enter end hour:");
	scanf("%f",_endH);
	printf("Please enter room:");
	scanf("%lu",_room);
	getchar();
}

static void InsertToFile(FILE *_file)
{
	int anotherMeet;
	float beginH, endH;
	size_t room;

	printf("Please enter all the meeting for you diary: \n");

	do
	{
		GetMeetValues(&beginH,&endH,&room);
		fprintf(_file, "%f %f %ld\n" , beginH, endH, room);

		printf("if you want to insert another meeting press 1: ");
		scanf("%d", &anotherMeet);

	}while(1 == anotherMeet);

}

ErrCode StoreMeet(char *_fileName)
{
	FILE *_file;

	_file = fopen(_fileName,"a");

	if(NULL == _file)
	{
		return ERR_FILE_NOT_OPEN;
	}

	if(0 < ftell(_file))
	{
		return FILE_NOT_EMPTY;
	}

	InsertToFile(_file);

	fclose(_file);

	return SUCCEEDED;
}

static ErrCode InsertToDiary(FILE *_file, AD_t* _ad)
{
	float beginH, endH;
	size_t room;
	meet *newMeet;
	ErrCode err;

	fscanf(_file, "%f%f%lu",&beginH, &endH, &room);

	while(!feof(_file))
	{
		err = CreateMeeting(&newMeet,beginH,endH,room);

		if(ERR_OVERFLOW == err)
		{
			return err;
		}

		err = InsertMeet(_ad,&newMeet);

		if(ERR_OVERFLOW == err)
		{
			return err;
		}

		fscanf(_file, "%f%f%lu",&beginH, &endH, &room);

	}

	return SUCCEEDED;

}

ErrCode LoadMeet(char *_fileName, AD_t** _ad, size_t _initialSize, size_t _incremetBlockSize)
{
	FILE *_file;

	_file = fopen(_fileName,"r");

	if(NULL == _file)
	{
		return ERR_FILE_NOT_OPEN;
	}

	(*_ad) = CreateAD(_initialSize,_incremetBlockSize);

	if(NULL == _ad)
	{
		return OVERFLOW_OR_ILLEGAL_INPUT;
	}

	InsertToDiary(_file, (*_ad));

	_file = fopen(_fileName,"w");

	fclose(_file);

	return SUCCEEDED;
}










