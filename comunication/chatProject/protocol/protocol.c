#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>/*TODO*/
#include <string.h>

#define META_DATA_USER 4
#define META_DATA_GROUP 5
#define META_DATA_SRV_MSG 2

/*create the buffer to send the server for user info*/
static ErrorCode ProtocolUserInfoPack(UserInfo *_userInfo, char *_buffer, size_t _bufferSize, Tag _tag);
/*create the user info struct by the given buffer*/
static ErrorCode ProtocolUserInfoUnPack(const char *_buffer, UserInfo *_userInfo);
/**/
static ErrorCode ProtocolGroupInfoPack(GroupInfo *_groupInfo, char *_buffer, size_t _bufferSize, Tag _tag);
/**/
static ErrorCode ProtocolGroupInfoUnPack(const char *_buffer, GroupInfo *_groupInfo);
/**/
static ErrorCode ProtocolGroupArrNamesPack(GroupsNames *_groupName, char *_buffer, size_t _bufferSize);
/**/
static ErrorCode ProtocolGroupArrNamesUnPack(char *_buffer, GroupsNames *_groupName);
/*create the buffer to send to the client from the server message*/
static ErrorCode ProtocolServerMsgPack(ServerMessage _message, char *_buffer, size_t _bufferSize);
/*create the message by the given buffer*/
static ErrorCode ProtocolServerMsgUnPack(char *_buffer, ServerMessage *_message);
/*set the string _str to the buffer*/
static void ProtocolSetStringToBuffer(char *_buffer, char *_str, int _sizeStr, int *_index);
/**/
static void EncryptMessage(char *_msg);


int ProtocolGetTag(char *_buffer)
{
	if(!_buffer)
	{
		return -1;
	}
	
	EncryptMessage(_buffer);
	
	return _buffer[0];
}

ErrorCode ProtocolPack(Message *_message, char *_buffer, size_t _bufferSize)
{
	ErrorCode err;
	
	if(!_message || !_message->m_messageValue || !_buffer)
	{
		return ERROR_WRONG_INPUT;
	}
	
	switch(_message->m_tag)
	{
		case SIGNIN:
		
			err = ProtocolUserInfoPack((UserInfo*)(_message->m_messageValue),_buffer,_bufferSize,SIGNIN);
			break;
		
		case LOGIN:
		
			err = ProtocolUserInfoPack((UserInfo*)(_message->m_messageValue),_buffer,_bufferSize,LOGIN);
			break;
		
		case LOGOUT:
		
			err = ProtocolUserInfoPack((UserInfo*)(_message->m_messageValue),_buffer,_bufferSize,LOGOUT);
			break;
		
		case JOIN_GROUP_CHOOSE:
		
			err = ProtocolGroupArrNamesPack((GroupsNames*)(_message->m_messageValue),_buffer,_bufferSize);
			break;
			
		case JOIN_GROUP_INSERT:
		
			err = ProtocolGroupInfoPack((GroupInfo*)(_message->m_messageValue),_buffer,_bufferSize,JOIN_GROUP_INSERT);
			break;
			
		case CREATE_GROUP:
		
			err = ProtocolGroupInfoPack((GroupInfo*)(_message->m_messageValue),_buffer,_bufferSize,CREATE_GROUP);
			break;
		
		case LEAVE_GROUP:
		
			err = ProtocolGroupInfoPack((GroupInfo*)(_message->m_messageValue),_buffer,_bufferSize,LEAVE_GROUP);
			break;
		
		case SERVER_RETURN_MSG:
		
			err = ProtocolServerMsgPack(*(ServerMessage*)(_message->m_messageValue),_buffer,_bufferSize);
			break;

	}
	
	EncryptMessage(_buffer);
	
	return err;
}

ErrorCode ProtocolUnPack(char *_buffer, void *_messageValue)
{

	if(!_buffer || !_messageValue)
	{
		return ERROR_WRONG_INPUT;
	}
	
	switch(_buffer[0])
	{
		case SIGNIN:
		
			return ProtocolUserInfoUnPack(_buffer,(UserInfo*)_messageValue);
		
		case LOGIN:
		
			return ProtocolUserInfoUnPack(_buffer,(UserInfo*)_messageValue);
		
		case LOGOUT:
		
			return ProtocolUserInfoUnPack(_buffer,(UserInfo*)_messageValue);
		
		case JOIN_GROUP_CHOOSE:
		
			return ProtocolGroupArrNamesUnPack(_buffer,(GroupsNames*)_messageValue);
			
		case JOIN_GROUP_INSERT:
		
			return ProtocolGroupInfoUnPack(_buffer,(GroupInfo*)_messageValue);
		
		case CREATE_GROUP:
		
			return ProtocolGroupInfoUnPack(_buffer,(GroupInfo*)_messageValue);
		
		case LEAVE_GROUP:
		
			return ProtocolGroupInfoUnPack(_buffer,(GroupInfo*)_messageValue);
		
		case SERVER_RETURN_MSG:
		
			return ProtocolServerMsgUnPack(_buffer,(ServerMessage*)_messageValue);

	}
	
	return OK;
}

/* SUB FUNCTIONS */

/* handle user information */

static ErrorCode ProtocolUserInfoPack(UserInfo *_userInfo, char *_buffer, size_t _bufferSize, Tag _tag)
{
	int i = 0, sizeName, sizePsw;
	
	sizeName = strlen(_userInfo->m_name);
	sizePsw = strlen(_userInfo->m_password);
	
	if(_bufferSize < (sizeName + sizePsw + META_DATA_USER))
	{
		return ERROR_UNDERFLOW;
	}

	_buffer[i++] = _tag;
	_buffer[i++] = sizeName + sizePsw + (META_DATA_USER - 2);
	
	ProtocolSetStringToBuffer(_buffer,_userInfo->m_name,sizeName,&i);
	
	i += sizeName;
	ProtocolSetStringToBuffer(_buffer,_userInfo->m_password,sizePsw,&i);
	
	_buffer[sizePsw + i] = '\0';
	
	return OK;
}

static ErrorCode ProtocolUserInfoUnPack(const char *_buffer, UserInfo *_userInfo)
{
	int i = 2;

	if(strlen(_buffer) < (META_DATA_USER + 2))
	{
		return ERROR_UNDERFLOW;
	}

	strncpy(_userInfo->m_name,_buffer + (i + 1),_buffer[i]);
	_userInfo->m_name[(int)_buffer[i]] = '\0';
			
	i += _buffer[i] + 1;
	
	strncpy(_userInfo->m_password,_buffer + (i + 1),_buffer[i]);
	_userInfo->m_password[(int)_buffer[i]] = '\0';
	
	return OK;
}

/* handle group information */

static ErrorCode ProtocolGroupInfoPack(GroupInfo *_groupInfo, char *_buffer, size_t _bufferSize, Tag _tag)
{
	int i = 0, sizeUserName, sizeGroupName, sizeIP;

	sizeUserName = strlen(_groupInfo->m_userName);
	sizeGroupName = strlen(_groupInfo->m_groupName);
	sizeIP = strlen(_groupInfo->m_ipAddresss);
	
	if(_bufferSize < (sizeUserName + sizeGroupName + sizeIP + META_DATA_GROUP))
	{
		return ERROR_UNDERFLOW;
	}
	
	_buffer[i++] = _tag;
	_buffer[i++] = sizeUserName + sizeGroupName + sizeIP + (META_DATA_GROUP - 2);
	
	ProtocolSetStringToBuffer(_buffer,_groupInfo->m_userName,sizeUserName,&i);
	
	i += sizeUserName;
	ProtocolSetStringToBuffer(_buffer,_groupInfo->m_groupName,sizeGroupName,&i);
	
	i += sizeGroupName;
	ProtocolSetStringToBuffer(_buffer,_groupInfo->m_ipAddresss,sizeIP,&i);
	
	_buffer[i + sizeIP] = '\0';
	
	return OK;
}

static ErrorCode ProtocolGroupInfoUnPack(const char *_buffer, GroupInfo *_groupInfo)
{
	int i = 2;
	
	if(strlen(_buffer) < (META_DATA_GROUP + 3))
	{
		return ERROR_UNDERFLOW;
	}
	
	strncpy(_groupInfo->m_userName,_buffer + (i + 1),_buffer[i]);
	_groupInfo->m_userName[(int)_buffer[i]] = '\0';
	
	i += _buffer[i] + 1;

	strncpy(_groupInfo->m_groupName,_buffer + (i + 1),_buffer[i]);
	_groupInfo->m_groupName[(int)_buffer[i]] = '\0';
	
	i += _buffer[i] + 1;
	
	strncpy(_groupInfo->m_ipAddresss,_buffer + (i + 1),_buffer[i]);
	_groupInfo->m_ipAddresss[(int)_buffer[i]] = '\0';

	return OK;
}

/* handle message from server */

static ErrorCode ProtocolServerMsgPack(ServerMessage _message, char *_buffer, size_t _bufferSize)
{
	int i = 0, msgSize = 1;
	
	if(_bufferSize < (msgSize + META_DATA_SRV_MSG))
	{
		return ERROR_UNDERFLOW;
	}
	
	_buffer[i++] = SERVER_RETURN_MSG;
	_buffer[i++] = msgSize;
	
	_buffer[i] = _message;
	
	_buffer[i + msgSize] = '\0';
	
	return OK;
}

static ErrorCode ProtocolServerMsgUnPack(char *_buffer, ServerMessage *_message)
{

	if(strlen(_buffer) < (META_DATA_SRV_MSG + 1))
	{
		return ERROR_UNDERFLOW;
	}

	*_message = _buffer[2];
	
	return OK;
}

/* handle choose group name */

static ErrorCode ProtocolGroupArrNamesPack(GroupsNames *_groupName, char *_buffer, size_t _bufferSize)
{
	int j, i = 0, sizeName = 0;

	if(_bufferSize < (_groupName->m_size + META_DATA_SRV_MSG))
	{
		return ERROR_UNDERFLOW;
	}
	
	_buffer[i++] = JOIN_GROUP_CHOOSE;
	_buffer[i++] = _groupName->m_size + META_DATA_SRV_MSG;
	
	for(j = 0;j < _groupName->m_size;++j)
	{
		sizeName = strlen(_groupName->m_names[j]);
		
		ProtocolSetStringToBuffer(_buffer,_groupName->m_names[j],sizeName,&i);
		i += sizeName;
		
		_buffer[1] += sizeName;
	}
	
	_buffer[i + sizeName] = '\0';
	
	return OK;
}

static ErrorCode ProtocolGroupArrNamesUnPack(char *_buffer, GroupsNames *_groupName)
{
	int j = 0, i = 2, sizeName;
	
	if(strlen(_buffer) < META_DATA_SRV_MSG)
	{
		return ERROR_UNDERFLOW;
	}
	
	_groupName->m_size = 0;
	
	while(_buffer[i] != '\0')
	{
		sizeName = _buffer[i];
		
		strncpy(_groupName->m_names[j++],_buffer + (i + 1),sizeName);
		
		i += sizeName + 1;
		
		++_groupName->m_size;
	}
	
	return OK;
}

static void ProtocolSetStringToBuffer(char *_buffer, char *_str, int _sizeStr, int *_index)
{
	_buffer[(*_index)++] = _sizeStr;
	_buffer[*_index] = '\0';
	strncat(_buffer,_str,_sizeStr);
}


/* Encrypt */

static void EncryptMessage(char *_msg)
{
    register int i;
    int size = strlen(_msg);
    char temp;
    
    for(i = 0; i < (size+1)/2; i++)
    {
        temp = ~_msg[i];
        _msg[i]= ~_msg[size-i-1]; 
        _msg[size-i-1] = temp;
    }
    _msg[size] = '\0'; 
}










