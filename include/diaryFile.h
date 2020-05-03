#include <stdio.h>
#include "appointmentDiary.h"

enum
{
	ERR_FILE_NOT_OPEN = -6,
	FILE_NOT_EMPTY = -7,
	OVERFLOW_OR_ILLEGAL_INPUT = -8
};


/*
	Description: gets meetings information and insert it to a file.
	Input: _fileName - the name of the file the meetings insert to.
	Return: return error code, ERR_FILE_NOT_OPEN - if the file fails to open, FILE_NOT_EMPTY - if the file already have meetings in, SUCCEEDED - on success. 
*/
ErrCode StoreMeet(char *_fileName);

/*
	Description: creates a new appointment diary and insert the meetings from the file to the diary, insert only the meetings with no overlap or NULL.
	Input: _fileName - the name of the file, _ad - pointer to the appointment diary it creates,
		initialSize - initial size of meeting array, incremetBlockSize - block size to increase the meeting array when is full. 
	Return: return error code, ERR_FILE_NOT_OPEN - if the file fails to open, OVERFLOW_OR_ILLEGAL_INPUT - if it fails to create the new diary,
				ERR_OVERFLOW - if the memory is overflow and it fails to create new meeting or if the diary is full and the memory is overflow,
				SUCCEEDED - on success.
*/
ErrCode LoadMeet(char *_fileName, AD_t** _ad, size_t _initialSize, size_t _incremetBlockSize);
