#include <stdlib.h>

typedef int ErrCode;

typedef struct AD_t AD_t;

typedef struct meet meet;

enum
{
	ERR_ILLEGAL_INPUT = -1,
	ERR_FAILED = -2,
	ERR_OVERLAP = -3,
	ERR_OVERFLOW = -4,
	ERR_NOT_EXIST = -5,
	SUCCEEDED = 0
};



/*
	Description: create dynamic struct appointment diary, and inside dynamic struct meeting array.
	Input: initialSize - initial size of meeting array, incremetBlockSize - block size to increase the meeting array when is full, 
			both should to be positive.
	Return value: return pointer to allocated appointment diary, or NULL in case it fails.
*/
AD_t* CreateAD(size_t _initialSize, size_t _incremetBlockSize);

/*
	Description: create dynamic struct meeting with the input values.
	Input: newMeet - pointer to the new meeting the function create, 
			the new meeting values -> beginH - begin hour, endH - end hour, room - room number, should be positive.
	Return value: return  error code, SUCCEEDED if succeeded, ERR_OVERFLOW if the memory is overflow, and ERR_ILLEGAL_INPUT if illegal input,
*/
ErrCode CreateMeeting(meet** _newMeet, float _beginH, float _endH, size_t _room);

/*
	Description: add the new meeting to the appointment diary if there isn't an overlap, resize the diary in case that the diary is full.
	Input: ad - dynamic struct appointment diary, 
			newMeet - pointer to the new meeting to be insert to the appointment diary, should not be NULL.
	Return value:return error code, ERR_ILLEGAL_INPUT if newMeet is NULL, ERR_OVERLAP if there is an overlap with the newMeet,
									ERR_OVERFLOW if the diary is full and the memory is overflow, 
									SUCCEEDED if succeeded in inserting the new meeting.
*/
ErrCode InsertMeet(AD_t* _ad , meet** _newMeet);

/*
	Description: remove the meeting with the begin hour beginH if it's exist in the diary.
	Input: ad - dynamic struct appointment diary, beginH - the begin hour of the meeting to remove, should be positive.
	Return value: return error code, ERR_ILLEGAL_INPUT if beginH is not positive, ERR_NOT_EXIST if the meeting is not exist in tha diary,
									SUCCEEDED if succeeded in removing the meeting.
*/
ErrCode RemoveMeet(AD_t* _ad, float _beginH);

/*
	Description: search for a specific meeting by its begin hour.
	Input: ad - dynamic struct appointment diary, beginH - the begin hour of the meeting to find, should be positive.
	Return value: return the number of the meeting, or ERR_NOT_EXIST if the meeting doesn't exist in the diary.
*/
int FindMeet(AD_t* _ad, float _BeginH);

/*
	Description: destroy the appointment diary, after calling this function the appointment diary should be reset with NULL.
	Input: ad - dynamic struct appointment diary.
	Return value: nothing returns.  
*/

void DestroyAD(AD_t* _ad);

/*
	Description: print the appointment diary.
	Input: ad - dynamic struct appointment diary.
	Return value: return the number of meetings who got printed, or ERR_NOT_EXIST if the diary is NULL.
*/
int PrintAD(AD_t* _ad);









