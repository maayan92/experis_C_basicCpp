#include <stdio.h>
#include <stdlib.h>
#include "appointmentDiary.h"

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

/* CREATE AD */

AD_t* CreateAD(size_t _initialSize, size_t _incremetBlockSize)
{
	AD_t *appointmentDiary;
	meet** meetingArray;

	if(0 > _initialSize || 0 > _incremetBlockSize)
	{
		return NULL;
	}

	appointmentDiary = (AD_t*)malloc(sizeof(AD_t));

	if(NULL == appointmentDiary)
	{
		return NULL;
	}
	
	meetingArray = (meet**)calloc(_initialSize,sizeof(meet));

	if(NULL == meetingArray)
	{
		free(appointmentDiary);
		appointmentDiary = NULL;

		return NULL;
	}

	appointmentDiary->meetingArray = meetingArray;
	appointmentDiary->adSize = _initialSize;
	appointmentDiary->numOfMeetings = 0;
	appointmentDiary->blockSize = _incremetBlockSize;

	return appointmentDiary;
}

/* DESTROY AD */

static void FreeMeetings(meet** _meetingArray, size_t _numOfMeetings)
{
	int i;

	for(i = 0;i < _numOfMeetings;++i)
	{
		free(_meetingArray[i]);
	}
}

void DestroyAD(AD_t* _ad)
{
	if(NULL != _ad)
	{
		FreeMeetings(_ad->meetingArray,_ad->numOfMeetings);

		free(_ad->meetingArray);

		free(_ad);
	}
}

/* CREATE MEET */

static ErrCode ValidTime(float _time)
{
	if(0 > _time || 24 < _time)
	{
		return ERR_ILLEGAL_INPUT;
	}

	return SUCCEEDED;
}

ErrCode CreateMeeting(meet** _newMeet, float _beginH, float _endH, size_t _room)
{
	if(ValidTime(_beginH) || ValidTime(_endH) || 0 > _room)
	{
		return ERR_ILLEGAL_INPUT;
	}

	(*_newMeet) = (meet*)malloc(sizeof(meet));

	if(NULL == (*_newMeet))
	{
		return ERR_OVERFLOW;
	}

	(*_newMeet)->beginH = _beginH;
	(*_newMeet)->endH = _endH;
	(*_newMeet)->room = _room;

	return SUCCEEDED;
}

/* INSERT MEET */

static int FindPositionForMeet(meet** _adMeet , meet** _newMeet, size_t _numOfMeetings)
{
	int i = 0;

	if(0 == _numOfMeetings)
	{
		return 0;
	}

	if((*_newMeet)->beginH < _adMeet[i]->beginH)
	{
		if((*_newMeet)->endH <= _adMeet[i]->beginH)
		{
			return 0;
		}
		return ERR_OVERLAP;
	}

	while(i < _numOfMeetings-1)
	{
		if((*_newMeet)->beginH >= _adMeet[i]->endH && (*_newMeet)->endH <= _adMeet[i+1]->beginH)
		{		
			return i+1;
		}

		++i;
	}

	if((*_newMeet)->beginH < _adMeet[i]->endH)
	{
		return ERR_OVERLAP;
	}

	return i+1;
}

static meet ** ReSizeMeet(meet **_meetingArray, size_t _adSize)
{
	_meetingArray = (meet**)realloc(_meetingArray,_adSize*sizeof(meet));

	return _meetingArray;
}

static void PushMeetingsDown(meet **_meetingArray, size_t _numOfMeetings, int _position)
{
	while(_numOfMeetings > _position)
	{
		_meetingArray[_numOfMeetings] = _meetingArray[_numOfMeetings-1];
		_numOfMeetings--;
	}
}

void InsertNewMeet(AD_t* _ad , meet** _newMeet, int _position)
{
	(*_ad).numOfMeetings++;
	PushMeetingsDown(_ad->meetingArray,_ad->numOfMeetings,_position);

	(*_ad).meetingArray[_position] = (*_newMeet);
}

ErrCode InsertMeet(AD_t* _ad , meet** _newMeet)
{
	int position;
	meet **newMeetArray;

	if(NULL == (*_newMeet))
	{
		return ERR_ILLEGAL_INPUT;
	}

	if(NULL == _ad)
	{
		return ERR_NOT_EXIST;
	}

	position = FindPositionForMeet(_ad->meetingArray,_newMeet,_ad->numOfMeetings);
	
	if(ERR_OVERLAP == position)
	{
		return ERR_OVERLAP;
	}

	if(_ad->adSize <= _ad->numOfMeetings)
	{
		newMeetArray = ReSizeMeet(_ad->meetingArray,_ad->adSize += _ad->blockSize);

		if(NULL == newMeetArray)
		{
			return ERR_OVERFLOW;
		}
		
		_ad->meetingArray = newMeetArray;
	}
	
	InsertNewMeet(_ad,_newMeet,position);
	
	return SUCCEEDED;
}

/* REMOVE MEET */

static void PushMeetingsUp(meet **_meetingArray, size_t _numOfMeetings, int _position)
{
	while(_position < _numOfMeetings)
	{
		_meetingArray[_position] = _meetingArray[_position+1];
		_position++;
	}
}

ErrCode RemoveMeet(AD_t* _ad, float _beginH)
{
	int position;

	if(0 > _beginH)
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	if(NULL == _ad)
	{
		return ERR_NOT_EXIST;
	}

	position = FindMeet(_ad,_beginH)-1;

	if(ERR_FAILED == position)
	{
		return ERR_FAILED;
	}

	PushMeetingsUp(_ad->meetingArray,_ad->numOfMeetings,position);
	_ad->numOfMeetings--;
	
	return SUCCEEDED;
}

/* FIND MEET */

int FindMeet(AD_t* _ad, float _BeginH)
{
	int i;

	if(NULL == _ad)
	{
		return ERR_NOT_EXIST;
	}

	for(i = 0;i < _ad->numOfMeetings;++i)
	{
		if((int)(_BeginH*100) == (int)(_ad->meetingArray[i]->beginH*100))
		{
			return i+1;
		}
	}

	return ERR_FAILED;
}

/* PRINT AD */

static int PrintOneMeet(meet* _meet)
{
	return printf("Begin time: %f , End time: %f , Room: %ld \n", _meet->beginH, _meet->endH, _meet->room);
}

static int PrintMeet(meet** _MeetArr, size_t _size)
{
	int i = 0, meetSuccess = 0;

	while(i < _size)
	{
		printf("Meeting %d: ",i+1);
		meetSuccess = PrintOneMeet(_MeetArr[i]);

		if(0 > meetSuccess)
		{
			return meetSuccess;
		}

		++i;
	}
	
	return i;
}

int PrintAD(AD_t* _ad)
{
	int meetSuccess;

	if(NULL == _ad)
	{
		return ERR_NOT_EXIST;
	}

	printf("Appointment Diary:\n");
	printf("Diary size: %ld \n",  _ad->adSize);
	printf("Diary meeting amount: %ld \n",  _ad->numOfMeetings);
	printf("Diary block size: %ld \n",  _ad->blockSize);

	meetSuccess = PrintMeet(_ad->meetingArray,_ad->numOfMeetings);

	if(0 > meetSuccess)
	{
		return ERR_FAILED;
	}

	return meetSuccess;
}


