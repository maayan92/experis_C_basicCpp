#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "ADTerror.h"
#include <stdio.h>

#define NAME_LENGTH 50
#define PASSWORD_LENGTH 40
#define IP_ADDRESS_LENGTH 40
#define BUFFER_SIZE 100
#define MAX_NUM_OF_NAMES 100

typedef enum
{
	SIGNIN = 1,
	LOGIN,
	LOGOUT,
	
	CREATE_GROUP,
	JOIN_GROUP_CHOOSE,
	JOIN_GROUP_INSERT,
	LEAVE_GROUP,
	
	SERVER_RETURN_MSG
}Tag;

typedef enum
{
	SIGN_IN_SUCCESS = 1,
	SIGN_IN_FAILED,
	SIGN_IN_ALREADY_EXIST,
	
	LOG_IN_SUCCESS,
	LOG_IN_NOT_EXIST,
	LOG_IN_ALREADY_CONNECTED,
	LOG_IN_INCORRECT_PASSWORD,
	
	LOG_OUT_SUCCESS,
	LOG_OUT_NOT_EXIST,
	
	CREATE_GROUP_SUCCESS,
	CREATE_GROUP_ALREADY_EXIST,
	CREATE_GROUP_WRONG_NAME,
	CREAT_GROUP_FAILED,
	
	JOIN_GROUP_CHOOSE_SUCCESS,
	JOIN_GROUP_SUCCESS,
	JOIN_GROUP_NOT_EXIST,
	JOIN_GROUP_FAILED,
	
	LEAVE_GROUP_SUCCESS,
	LEAVE_GROUP_NOT_EXIST,
	LEAVE_GROUP_FAILED,
	
	INVALID_TAG
	
}ServerMessage;

typedef struct Message
{
	Tag m_tag;
	void *m_messageValue; /* -> UserInfo/GroupInfo/ServerMessage */
}Message;

typedef struct UserInfo
{
	char m_name[NAME_LENGTH];
	char m_password[PASSWORD_LENGTH];
}UserInfo;

typedef struct GroupInfo
{
	char m_userName[NAME_LENGTH];
	char m_groupName[NAME_LENGTH];
	char m_ipAddresss[IP_ADDRESS_LENGTH];
}GroupInfo;

typedef struct GroupsNames
{
	char m_names[MAX_NUM_OF_NAMES][NAME_LENGTH];
	size_t m_size;
}GroupsNames;

/*
	Description: create the buffer to send the server for every message.
	Input: _message - pointer to the message information,
		_buffer - the buffer created from the _userInfo, 
		_bufferSize - size of buffer.
	Return: return error code, ERROR_WRONG_INPUT - if _userInfo or _buffer are NULL, 
					ERROR_UNDERFLOW - if the buffer size is too small, 
					OK on success.
*/
ErrorCode ProtocolPack(Message *_message, char *_buffer, size_t _bufferSize);

/*
	Description: create the message struct by the given buffer.
	Input: _buffer - buffer of a message, _messageValue - pointer to returned struct.
	Return: return error code, ERROR_WRONG_INPUT - if _messageValue or _buffer are NULL, OK on success.
*/
ErrorCode ProtocolUnPack(char *_buffer, void *_messageValue);

/*
	Description: give the tag of the _buffer.
	Input: _buffer - buffer of a message.
	Return: return the tag of the buffer, or -1 if the buffer is NULL.
*/
int ProtocolGetTag(char *_buffer);






#endif
