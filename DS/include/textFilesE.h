#ifndef _TEXTFILES_H
#define _TEXTFILES_H

#include <stdio.h>
#include "ADTErrors.h"

#define LENGTH 50

/*
	Description: count the number of time a specific word occur in a file.
	Input: _fileName - the name of the file that contains the word and the filename to search in.
	Return value: return the number of time the word occur in the file.
*/
size_t CountWord(char *_fileName);

/*
	Description: count the number of time every char occur in the file, and prins every char with its number of occurrences.
	Input: _fileName - the name of the file.
	Return value: return ErrCode, ERR_FAILED_TO_OPEN - if the file failed to open, SUCCEEDED - on success.
*/
ErrCode CountChars(char *_fileName);

/*
	Description: count the number of time every word occur in the file, and print every word with its number of occurrences.
	Input: _fileName - the name of the file.
	Return value: return ErrCode, ERR_FAILED_TO_OPEN - if the file failed to open, ERR_OVERFLOW - if there was a memory overflow, 
					ERR_FILE_EMPTY - if the file is empty, SUCCEEDED - on success.
*/
ErrCode CountAllWords(char *_fileName);


#endif
