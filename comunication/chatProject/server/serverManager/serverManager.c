#include "socketServerSelect.h"
#include "protocol.h"
#include "usersDataBase.h"
#include "groupsDB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_MAGIC_NUMBER 0xe1e1e1e1
#define SERVER_NO_MAGIC_NUMBER 0xe0e0e0e0

#define IS_NO_EXIST(_srvMsg)(!_srvMsg || SERVER_NO_MAGIC_NUMBER == _srvMsg->m_magicNumber)

typedef struct ServerManag
{
	size_t m_magicNumber;
	server *m_server;
	usersDB *m_usersDB;
	groupsDB *m_groupsDB;
}ServerManag;

/*destroy the server manager*/
static void ServerManagerDestroy(ServerManag *_srvMng);
/*get the event that occur and handle it*/
static void RunApp(ServerManag *_srvMng);
/*handle the message the server got from a client*/
static void MessageHandler(char *_buffer, int _clientSock, void *_context);
/*handle the sign in buffer from the client and send a message back*/
static ServerMessage SignInGetUserInfoByBuffer(char *_buffer,usersDB *_userDB);
/*handle the log in buffer from the client and send a message back*/
static ServerMessage LogInGetUserInfoByBuffer(char *_buffer,usersDB *_userDB);
/*handle the log out buffer from the client and send a message back*/
static ServerMessage LogOutGetUserInfoByBuffer(char *_buffer,usersDB *_userDB);
/*handle the create group buffer from the client and send a message/group info back*/
static ServerMessage CreateNewGroupByBuffer(char *_buffer, groupsDB *_groupDB, GroupInfo *_groupInfo);
/**/
static void JoinGroupSetGroupsNames(groupsDB *_groupDB, GroupsNames *_groupsNames, Message *_msg);
/**/
static ServerMessage JoinGroupByBuffer(char *_buffer, groupsDB *_groupDB, GroupInfo *_groupInfo);
/**/
static ServerMessage LeaveGroupByBuffer(char *_buffer, groupsDB *_groupDB, GroupInfo *_groupInfo);

void ServerManagerRun()
{
	ServerManag *srvMng;
	
	srvMng = (ServerManag*)malloc(sizeof(ServerManag));

	srvMng->m_server = ServerCreate(NULL, 1234);
	if(!srvMng->m_server)
	{
		perror("server failed to create!");
		return;
	}
	
	srvMng->m_usersDB = UsersDBCreate();
	if(!srvMng->m_usersDB)
	{
		ServerDestroy(srvMng->m_server);
		free(srvMng);
		perror("user DB failed to create!");
		return;
	}
	
	if(!(srvMng->m_groupsDB = GroupsDBCreate()))
	{
		UsersDBDestroy(srvMng->m_usersDB);
		ServerDestroy(srvMng->m_server);
		free(srvMng);
		perror("user DB failed to create!");
		return;
	}
	
	srvMng->m_magicNumber = SERVER_MAGIC_NUMBER;
	
	RunApp(srvMng);
	
	ServerManagerDestroy(srvMng);
}

static void ServerManagerDestroy(ServerManag *_srvMng)
{
	if(IS_NO_EXIST(_srvMng))
	{
		return;
	}
	
	_srvMng->m_magicNumber = SERVER_NO_MAGIC_NUMBER;
	
	ServerDestroy(_srvMng->m_server);
	UsersDBDestroy(_srvMng->m_usersDB);
	GroupsDBDestroy(_srvMng->m_groupsDB);
	
	free(_srvMng);
}

static void RunApp(ServerManag *_srvMng)
{
	while(1)
	{
		if(ServerNewActivity(_srvMng->m_server) == SOCK_SUCCESS)
		{
			ServerAcceptServer(_srvMng->m_server);
			
			ServerRunAndReceive(_srvMng->m_server,MessageHandler,_srvMng);
		}
	}
}

static void MessageHandler(char *_buffer, int _clientSock, void *_context)
{
	char sendBuffer[BUFFER_SIZE];
	Message msg;
	ServerMessage message;
	GroupInfo groupInfo;
	GroupsNames groupsNames;
	
	if(IS_NO_EXIST(((ServerManag*)_context)) || !_buffer)
	{
		return;
	}

	switch(ProtocolGetTag(_buffer))
	{
		case SIGNIN:
		
			message = SignInGetUserInfoByBuffer(_buffer,((ServerManag*)_context)->m_usersDB);
			
			msg.m_tag = SERVER_RETURN_MSG;
			msg.m_messageValue = &message;
			
			break;
		
		case LOGIN:
		
			message = LogInGetUserInfoByBuffer(_buffer,((ServerManag*)_context)->m_usersDB);
			
			msg.m_tag = SERVER_RETURN_MSG;
			msg.m_messageValue = &message;
			
			break;
	
		case LOGOUT:
		
			message = LogOutGetUserInfoByBuffer(_buffer,((ServerManag*)_context)->m_usersDB);
			
			msg.m_tag = SERVER_RETURN_MSG;
			msg.m_messageValue = &message;
			
			break;
		
		case CREATE_GROUP:
		
			message = CreateNewGroupByBuffer(_buffer,((ServerManag*)_context)->m_groupsDB,&groupInfo);
		
			if(CREATE_GROUP_SUCCESS != message)
			{
				msg.m_tag = SERVER_RETURN_MSG;
				msg.m_messageValue = &message;
			}
			else
			{
				msg.m_tag = CREATE_GROUP;
				msg.m_messageValue = &groupInfo;
			}
			
			break;

		case JOIN_GROUP_CHOOSE:
		
			JoinGroupSetGroupsNames(((ServerManag*)_context)->m_groupsDB,&groupsNames,&msg);
		
			break;
		
		case JOIN_GROUP_INSERT:
		
			message = JoinGroupByBuffer(_buffer,((ServerManag*)_context)->m_groupsDB,&groupInfo);
			
			if(JOIN_GROUP_SUCCESS != message)
			{
				msg.m_tag = SERVER_RETURN_MSG;
				msg.m_messageValue = &message;
			}
			else
			{
				msg.m_tag = JOIN_GROUP_INSERT;
				msg.m_messageValue = &groupInfo;
			}
		
			break;
			
		case LEAVE_GROUP:
		
			message = LeaveGroupByBuffer(_buffer,((ServerManag*)_context)->m_groupsDB,&groupInfo);
			
			if(LEAVE_GROUP_SUCCESS != message)
			{
				msg.m_tag = SERVER_RETURN_MSG;
				msg.m_messageValue = &message;
			}
			else
			{
				msg.m_tag = LEAVE_GROUP;
				msg.m_messageValue = &groupInfo;
			}
			
			break;
			
		default:
		
			message = INVALID_TAG;
			
			break;
	}
	
	ProtocolPack(&msg,sendBuffer,BUFFER_SIZE);
	ServerSend(((ServerManag*)_context)->m_server,_clientSock,sendBuffer);
}

/* User info un  pack */

static ServerMessage SignInGetUserInfoByBuffer(char *_buffer,usersDB *_userDB)
{
	UserInfo userInfo;
	ServerMessage message;
	
	ProtocolUnPack(_buffer,&userInfo);
	
	switch(UsersDBAddUser(_userDB,userInfo.m_name,userInfo.m_password))
	{
		case USERS_DUPLICATE_USERNAME:
		
			message = SIGN_IN_ALREADY_EXIST;
			break;
		
		case USERS_SUCCESS:
		
			message = SIGN_IN_SUCCESS;
			break;
		
		default:
		
			message = SIGN_IN_FAILED;
			break;
	}
	
	return message;
}

static ServerMessage LogInGetUserInfoByBuffer(char *_buffer,usersDB *_userDB)
{
	UserInfo userInfo;
	ServerMessage message;
	
	ProtocolUnPack(_buffer,&userInfo);
	
	switch(UsersDBLogin(_userDB,userInfo.m_name,userInfo.m_password))
	{
		case USERS_ALREADY_CONNECTED:
		
			message = LOG_IN_ALREADY_CONNECTED;
			break;
			
		case USERS_INCORRECT_PASSWORD:
		
			message = LOG_IN_INCORRECT_PASSWORD;
			break;
			
		case USERS_NOT_IN_DB:
		
			message = LOG_IN_NOT_EXIST;
			break;
			
		default:
		
			message = LOG_IN_SUCCESS;
			break;
	}
	
	return message;
}

static ServerMessage LogOutGetUserInfoByBuffer(char *_buffer,usersDB *_userDB)
{
	UserInfo userInfo;
	
	ProtocolUnPack(_buffer,&userInfo);
	
	if(USERS_NOT_IN_DB == UsersDBLogout(_userDB,userInfo.m_name))
	{
			return LOG_OUT_NOT_EXIST;
	}
	
	return LOG_OUT_SUCCESS;
}

/* Group info un pack */

static ServerMessage CreateNewGroupByBuffer(char *_buffer, groupsDB *_groupDB, GroupInfo *_groupInfo)
{
	ServerMessage message;
	
	ProtocolUnPack(_buffer,_groupInfo);
	
	switch(GroupsDBOpenNewGroup(_groupDB,_groupInfo->m_groupName,_groupInfo->m_userName,_groupInfo->m_ipAddresss))
	{
		case GROUPS_DUPLICATE_GROUP_NAME:
		
			message = CREATE_GROUP_ALREADY_EXIST;
			break;
			
		case GROUPS_WRONG_INPUT:
		
			message = CREATE_GROUP_WRONG_NAME;
			break;
			
		case GROUPS_SUCCESS:
		
			message = CREATE_GROUP_SUCCESS;
			break;
			
		default:
		
			message = CREAT_GROUP_FAILED;
			break;
	}
	
	return message;
}

static void JoinGroupSetGroupsNames(groupsDB *_groupDB, GroupsNames *_groupsNames, Message *_msg)
{
	int i;
	char *groupsArrNames[MAX_NUM_OF_GROUP];

	_groupsNames->m_size = GroupsDBGetGroupNames(_groupDB,groupsArrNames);
	
	for(i = 0;i < _groupsNames->m_size;++i)
	{
		strcpy(_groupsNames->m_names[i],groupsArrNames[i]);
	}
	
	_msg->m_tag = JOIN_GROUP_CHOOSE;
	_msg->m_messageValue = _groupsNames;
}

static ServerMessage JoinGroupByBuffer(char *_buffer, groupsDB *_groupDB, GroupInfo *_groupInfo)
{
	ServerMessage message;
	
	ProtocolUnPack(_buffer,_groupInfo);
	
	switch(GroupsDBAddClientToGroup(_groupDB,_groupInfo->m_groupName,_groupInfo->m_userName,_groupInfo->m_ipAddresss))
	{
		case GROUPS_NOT_IN_DB:
		
			message = JOIN_GROUP_NOT_EXIST;
			break;
			
		case GROUPS_SUCCESS:
		
			message = JOIN_GROUP_SUCCESS;
			break;
				
		default:
		
			message = JOIN_GROUP_FAILED;
			break;
	}
	
	return message;
}

static ServerMessage LeaveGroupByBuffer(char *_buffer, groupsDB *_groupDB, GroupInfo *_groupInfo)
{
	ServerMessage message;
	
	ProtocolUnPack(_buffer,_groupInfo);
	
	switch(GroupsDBRemoveClientFromGroup(_groupDB,_groupInfo->m_groupName,_groupInfo->m_userName))
	{
		case GROUPS_NOT_IN_DB:
		
			message = LEAVE_GROUP_NOT_EXIST;
			break;
			
		case GROUPS_SUCCESS:
		
			message = LEAVE_GROUP_SUCCESS;
			break;
		
		case GROUPS_CLOSED:
		
			message = LEAVE_GROUP_SUCCESS;
			break;
				
		default:
		
			message = LEAVE_GROUP_FAILED;
			break;
	}
	
	return message;
}



