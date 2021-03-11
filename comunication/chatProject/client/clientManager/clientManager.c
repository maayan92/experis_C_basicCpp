#include "socketClient.h"
#include "clientGroups.h"
#include "protocol.h"
#include "ui.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  /* for create new terminal (system call) */
#include <string.h>  /* for strcpy, strcat and strlen */
#include <sys/types.h> /*for kill (system call)*/
#include <signal.h>    /*for kill (system call)*/
#include <unistd.h>    /*for sleep (system call)*/

#define CONFIG_FILE "config.txt"
#define IP_SIZE 16
#define BUFFER 400
#define MIN_NAME_SIZE 2
#define MIN_PSW_SIZE 6
#define IP_LEN 20
#define MAX_PORT_SIZE 6

#define BEGINNING_BIG "gnome-terminal command  --geometry=40x20"
#define BEGINNING_SMALL "gnome-terminal command  --geometry=40x10"
#define POSITION_BIG "+40+100 "
#define POSITION_SMALL "+40+500 "
#define BASH_READ " -- ./chatRead.out "
#define BASH_WRITE " -- ./chatWrite.out "

typedef struct clientInfo
{
    client *m_clntNet;
    clientGroups *m_groups;
    size_t m_port;
    int m_isInMainMenu;
}clientInfo;

typedef struct openChatArgs
{
    char *m_ip;
    char m_port[MAX_PORT_SIZE];
    char *m_fileName;
    char *m_userName;
    char *m_groupName;
}openChatArgs;

/*initialize the client info*/
static int ClientManagerInitialize(clientInfo *_clntInfo);
/*open socket and connect to the server*/
static int ClientManagerOpenSockAndConnect(client *_client);
/*get the server's details*/
static int ClientManagerGetServerDetails(char *_ip, int *_port);
/*destroy client manager*/
static void ClientManagerDestroy(clientInfo *_clntInfo);
/*send a request to the server and recieve the response*/
static void ClientManagerSendAndRecieve(clientInfo *_clntInfo, Action _act, UserInfo *_userInfo);
/*send the request to sign in / log in*/
static int ClientManagerSignInLogIn(clientInfo *_clntInfo, Tag _tag, UserInfo *_userInfo);
/*send and receive response from server for sigh in / log in / log out request*/
static int ClientManagerUserInfoSendAndReceive(clientInfo *_clntInfo, Tag _tag, UserInfo _userInfo);
/*check the name and password we received from the user*/
static int ClientManagerUsersInfoValidation(char *_name, char *_password, Error *_message);
/*send request to create a new group*/
static int ClientManagerCreateGroup(clientInfo *_clntInfo, UserInfo _userInfo);
/*send request to join a group*/
static int ClientManagerJoinGroup(clientInfo *_clntInfo, UserInfo _userInfo);
/*send group create/join/leave request and get respons from server*/
static int GroupSendAndRecieve(clientInfo *_clntInfo, UserInfo _userInfo, char *_groupName, Tag _tag);
/*handle the leave group request*/
static int ClientManagerLeaveGroup(clientInfo *_clntInfo, UserInfo _userInfo);
/*receive message from the server and handle it*/
static void RecieveMessageFromServer(clientInfo *_clntInfo, GroupInfo *_groupInfo, char *_buffer, Tag _tag);
/*check the server message and send it to print*/
static void PrintServerMessage(ServerMessage _message);
/*print all the existing groups in the DB*/
static void ClientManagerPrintGroupNamesStruct(GroupsNames *_groupNames);
/*print the client's groups*/
static void ClientManagerPrintGroupNamesArr(char *_groupNames[], size_t _numOfGroups);
/*pull out the user from all its groups*/
static void LeaveAllGroups(clientInfo *_clntInfo, UserInfo _userInfo);
/*get the group name from the user*/
static void GetGroupNameFromUser(char *_groupName);

static void ClientManagerOpenChatWindows(char *_ip, int _port, char *_filename, char *_userName, char *_groupName);
static void ClientManagerCloseChatWindows(char *_filename);
static void ClientManagerInitOpenChatArgs(openChatArgs *_charArgs, char *_ip, int _port, char *_filename, char *_userName, char *_groupName);
static void ClientManagerOpenTerminal(openChatArgs *_charArgs, char *_beginning, char *_position, char *_out);
static void ConvertIntToString(int _i, char *_str);
static void MirrorStrChars(char *_str);


void ClientManagerRun()
{
    clientInfo clntInfo;
    Action act;
    UserInfo userInfo;
    
    if(!ClientManagerInitialize(&clntInfo))
    {
        return;
    }
    UIPrintBanner();
    do
    {
        act = UIPrintMenuGetAction(clntInfo.m_isInMainMenu? MAIN_MENU: START_MENU);
        if(act != UI_EXIT)
        {
            ClientManagerSendAndRecieve(&clntInfo, act,&userInfo);
        }
        
    }while(act != UI_EXIT);
    
    ClientManagerDestroy(&clntInfo);
}

static int ClientManagerInitialize(clientInfo *_clntInfo)
{
    char ip[IP_SIZE];
    int port;
    
	if(ClientManagerGetServerDetails(ip, &port))
	{
		if((_clntInfo->m_groups = ClientGroupsCreate()))
		{
	    	if((_clntInfo->m_clntNet = ClientCreate(ip, port)))
	    	{
	    		if(ClientManagerOpenSockAndConnect(_clntInfo->m_clntNet))
	    		{
	    			_clntInfo->m_port = port;
	    			_clntInfo->m_isInMainMenu = false;
	    			return true;
	    		}

	      	    ClientDestroy(_clntInfo->m_clntNet);
	    	}
            ClientGroupDestroy(_clntInfo->m_groups);
		}
	}
    
    return false;
}

static int ClientManagerOpenSockAndConnect(client *_client)
{
	if(ClientOpenSock(_client) == SOCK_SUCCESS)
	{
		if(ClientConnect(_client) == SOCK_SUCCESS)
        {
            return true;
        }
	}
	
	return false;
}

static int ClientManagerGetServerDetails(char *_ip, int *_port)
{
    FILE *configFile;
    
    if(!(configFile = fopen(CONFIG_FILE, "r")))
    {
        return false;
    }
    fscanf(configFile, "%s", _ip);
    fscanf(configFile, "%d", _port);
    
    fclose(configFile);
    
    return true;
}

static void ClientManagerDestroy(clientInfo *_clntInfo)
{
    ClientDestroy(_clntInfo->m_clntNet);
    ClientGroupDestroy(_clntInfo->m_groups);
}

static void ClientManagerSendAndRecieve(clientInfo *_clntInfo, Action _act, UserInfo *_userInfo)
{
	int result;
	
	switch(_act)
	{
		case UI_SIGN_IN:
		    
			result = ClientManagerSignInLogIn(_clntInfo,SIGNIN,_userInfo);
		        break;
		    
		case UI_LOG_IN:
		
			result = ClientManagerSignInLogIn(_clntInfo,LOGIN,_userInfo);
			_clntInfo->m_isInMainMenu = result;
		        break;
		    
		case UI_CREATE_GROUP:
		
			result = ClientManagerCreateGroup(_clntInfo,*_userInfo);
		        break;
		    
		case UI_LEAVE_GROUP:
		
			result = ClientManagerLeaveGroup(_clntInfo,*_userInfo);
		        break;
		    
		case UI_JOIN_GROUP:

			result = ClientManagerJoinGroup(_clntInfo,*_userInfo);
		        break;
		    
		case UI_LOG_OUT:
		
			result = ClientManagerUserInfoSendAndReceive(_clntInfo,LOGOUT,*_userInfo);
			_clntInfo->m_isInMainMenu = (result) ? false : true;
		        break;
		
		default:
		
			break;   
        }
}

/* sign/log request */

static int ClientManagerSignInLogIn(clientInfo *_clntInfo, Tag _tag, UserInfo *_userInfo)
{
	char name[NAME_LENGTH], password[PASSWORD_LENGTH];
	Error message;
	
	GetUsersDetails(name, password);
	
	while(!ClientManagerUsersInfoValidation(name,password,&message))
	{
		PrintError(message);
		GetUsersDetails(name, password);
	}
	
	strcpy(_userInfo->m_name,name);
	strcpy(_userInfo->m_password,password);
        
	return ClientManagerUserInfoSendAndReceive(_clntInfo,_tag,*_userInfo);
}

static int ClientManagerUserInfoSendAndReceive(clientInfo *_clntInfo, Tag _tag, UserInfo _userInfo)
{
	static int timesToTry = 1;
	char buffer[BUFFER_SIZE];
	Message _sendMsg;
	ServerMessage message;
	
	_sendMsg.m_tag = _tag;
	_sendMsg.m_messageValue = &_userInfo;
        
	ProtocolPack(&_sendMsg,buffer,BUFFER_SIZE);
        
	if(SOCK_SUCCESS != ClientSend(_clntInfo->m_clntNet, buffer))
	{
    		PrintError(SEND_MESSAGE_FAILED);
    		return false;
	}
    
	if(SOCK_SUCCESS != ClientReceive(_clntInfo->m_clntNet,buffer,BUFFER_SIZE))
	{
		if(2 <= timesToTry)
		{
			PrintError(CONNECTION_FAILED);
			ClientManagerUserInfoSendAndReceive(_clntInfo,LOGOUT,_userInfo);
		}
		
		++timesToTry;
		ClientManagerOpenSockAndConnect(_clntInfo->m_clntNet);
    		return ClientManagerUserInfoSendAndReceive(_clntInfo,_tag,_userInfo);
	}
	
	ProtocolGetTag(buffer);
	ProtocolUnPack(buffer,&message);
    
	PrintServerMessage(message);
	if(LOGOUT == _tag && LOG_OUT_SUCCESS == message)
	{
		LeaveAllGroups(_clntInfo,_userInfo);
	}
    
	return (SIGN_IN_SUCCESS != message && LOG_IN_SUCCESS != message && LOG_OUT_SUCCESS != message) ? false : true;
}

static void LeaveAllGroups(clientInfo *_clntInfo, UserInfo _userInfo)
{
	int i, size;
	char *allClientGroups[MAX_NUM_OF_GROUP];
	
	size = GroupsDBGetGroupNames(_clntInfo->m_groups,allClientGroups);
	
	for(i = 0;i < size;++i)
	{
		GroupSendAndRecieve(_clntInfo,_userInfo,allClientGroups[i],LEAVE_GROUP);
	}
	
}

static int ClientManagerUsersInfoValidation(char *_name, char *_password, Error *_message)
{
	if(strlen(_name) < MIN_NAME_SIZE)
	{
		*_message = INVALID_NAME;
		return false;
	}
	if(strlen(_password) < MIN_PSW_SIZE)
	{
		*_message = INVALID_PASSWORD;
		return false;
	}
	return true;
}

/* group request */

static int ClientManagerCreateGroup(clientInfo *_clntInfo, UserInfo _userInfo)
{
	char groupName[NAME_LENGTH]; 

	PrintError(NEW_GROUP_NAME);
	GetGroupName(groupName);
	while(strlen(groupName) < MIN_NAME_SIZE)
	{
		PrintError(INVALID_GROUP_NAME);
		GetGroupName(groupName);
	}
	
	return GroupSendAndRecieve(_clntInfo,_userInfo,groupName,CREATE_GROUP);
}

static int ClientManagerJoinGroup(clientInfo *_clntInfo, UserInfo _userInfo)
{
	static int timesToTry = 1; 
	char buffer[BUFFER_SIZE], groupName[NAME_LENGTH];
	Message sendMsg;
	GroupsNames groupsAllName;
	
	groupsAllName.m_size = 0;
	
	sendMsg.m_tag = JOIN_GROUP_CHOOSE;
	sendMsg.m_messageValue = &groupsAllName;
	
	ProtocolPack(&sendMsg,buffer,BUFFER_SIZE);
	
	if(SOCK_SUCCESS != ClientSend(_clntInfo->m_clntNet,buffer))
	{
    		PrintError(SEND_MESSAGE_FAILED);
    		return false;
	}
	if(SOCK_SUCCESS != ClientReceive(_clntInfo->m_clntNet,buffer,BUFFER_SIZE))
	{
		if(2 <= timesToTry)
		{
			PrintError(CONNECTION_FAILED);
			ClientManagerUserInfoSendAndReceive(_clntInfo,LOGOUT,_userInfo);
		}
		++timesToTry;
		ClientManagerOpenSockAndConnect(_clntInfo->m_clntNet);
    		return ClientManagerJoinGroup(_clntInfo,_userInfo);
	}
	
	ProtocolGetTag(buffer);
	ProtocolUnPack(buffer,&groupsAllName);

	ClientManagerPrintGroupNamesStruct(&groupsAllName);
	
	GetGroupNameFromUser(groupName);

	if(ClientFindGroup(_clntInfo->m_groups,groupName))
	{
		PrintError(ALREADY_IN_GROUP);
		return false;
	}
	
	return GroupSendAndRecieve(_clntInfo,_userInfo,groupName,JOIN_GROUP_INSERT);
}

static int ClientManagerLeaveGroup(clientInfo *_clntInfo, UserInfo _userInfo)
{
	char groupName[NAME_LENGTH], *groupsNames[MAX_NUM_OF_GROUP];
	size_t groupsNamesSize;
	
	groupsNamesSize = GroupsDBGetGroupNames(_clntInfo->m_groups,groupsNames);
	
	ClientManagerPrintGroupNamesArr(groupsNames, groupsNamesSize);
	
	GetGroupNameFromUser(groupName);
	
	if(!ClientFindGroup(_clntInfo->m_groups,groupName))
	{
		PrintError(NOT_IN_GROUP);
		return false;
	}
	
	return GroupSendAndRecieve(_clntInfo,_userInfo,groupName,LEAVE_GROUP);
}

static int GroupSendAndRecieve(clientInfo *_clntInfo, UserInfo _userInfo, char *_groupName, Tag _tag)
{
	static int timesToTry = 1;
	char buffer[BUFFER_SIZE];
	Message sendMsg;
	GroupInfo groupInfo;
	groupInfo.m_ipAddresss[0] = '\0';
	
	strcpy(groupInfo.m_userName,_userInfo.m_name);
	strcpy(groupInfo.m_groupName,_groupName);
	
	sendMsg.m_tag = _tag;
	sendMsg.m_messageValue = &groupInfo;

	ProtocolPack(&sendMsg,buffer,BUFFER_SIZE);
	
	if(SOCK_SUCCESS != ClientSend(_clntInfo->m_clntNet,buffer))
	{
    		PrintError(SEND_MESSAGE_FAILED);
    		return false;
	}
	if(SOCK_SUCCESS != ClientReceive(_clntInfo->m_clntNet,buffer,BUFFER_SIZE))
	{
		if(2 <= timesToTry)
		{
			--timesToTry;
			PrintError(CONNECTION_FAILED);
			ClientManagerUserInfoSendAndReceive(_clntInfo,LOGOUT,_userInfo);
			return false;
		}
		++timesToTry;
		ClientManagerOpenSockAndConnect(_clntInfo->m_clntNet);
    		return ClientManagerCreateGroup(_clntInfo,_userInfo);
	}
	
	RecieveMessageFromServer(_clntInfo,&groupInfo,buffer,_tag);
	
	return true;
}

static void GetGroupNameFromUser(char *_groupName)
{
	GetGroupName(_groupName);
	while(strlen(_groupName) < MIN_NAME_SIZE)
	{
		PrintError(INVALID_NAME);
		GetGroupName(_groupName);
	}
}

static void RecieveMessageFromServer(clientInfo *_clntInfo, GroupInfo *_groupInfo, char *_buffer, Tag _tag)
{
	char fileName[BUFFER_SIZE] = "./chatFiles/";
	ServerMessage message;
	
	if(SERVER_RETURN_MSG == ProtocolGetTag(_buffer))
	{
		ProtocolUnPack(_buffer,&message);
		PrintServerMessage(message);
	}
	else
	{
		ProtocolUnPack(_buffer,_groupInfo);
		strcat(fileName,_groupInfo->m_userName);
		strcat(fileName,_groupInfo->m_groupName);
		strcat(fileName,".txt");
		
		if(LEAVE_GROUP == _tag)
		{
			ClientRemoveGroup(_clntInfo->m_groups,_groupInfo->m_groupName,fileName);
			ClientManagerCloseChatWindows(fileName);
		}
		else
		{
			ClientAddGroup(_clntInfo->m_groups,_groupInfo->m_groupName,fileName);
			ClientManagerOpenChatWindows(_groupInfo->m_ipAddresss,_clntInfo->m_port,fileName,_groupInfo->m_userName,_groupInfo->m_groupName);
		}
		message = (LEAVE_GROUP == _tag) ? LEAVE_GROUP_SUCCESS : ((CREATE_GROUP == _tag) ? CREATE_GROUP_SUCCESS : JOIN_GROUP_CHOOSE_SUCCESS);
		PrintServerMessage(message);
	}
}

static void PrintServerMessage(ServerMessage _message)
{
	switch(_message)
	{
		case SIGN_IN_SUCCESS:
		
			UIPrintServerMessage(UI_SIGN_IN_SUCCESS);
			break;
			
		case SIGN_IN_FAILED:
		
			UIPrintServerMessage(UI_SIGN_IN_FAILED);
			break;
			
		case SIGN_IN_ALREADY_EXIST:
		
			UIPrintServerMessage(UI_USERNAME_ALREADY_EXIST);
			break;
			
		case LOG_IN_SUCCESS:
		
			UIPrintServerMessage(UI_LOG_IN_SUCCESS);
			break;
			
		case LOG_IN_NOT_EXIST:
		
			UIPrintServerMessage(UI_USERS_NOT_IN_DB);
			break;
			
		case LOG_IN_ALREADY_CONNECTED:
		
			UIPrintServerMessage(UI_USERS_ALREADY_CONNECTED);
			break;
			
		case LOG_IN_INCORRECT_PASSWORD:
		
			UIPrintServerMessage(UI_USERS_INCORRECT_PASSWORD);
			break;
			
		case LOG_OUT_SUCCESS:
		
			UIPrintServerMessage(UI_LOG_OUT_SUCCESS);
			break;
			
		case LOG_OUT_NOT_EXIST:
		
			UIPrintServerMessage(UI_USERS_NOT_IN_DB);
			break;
		
		case CREATE_GROUP_SUCCESS:
		
			UIPrintServerMessage(UI_CREATE_GROUP_SUCCESS);
			break;
		
		case CREATE_GROUP_ALREADY_EXIST:
		
			UIPrintServerMessage(UI_CREATE_GROUP_ALREADY_EXIST);
			break;
		
		case CREATE_GROUP_WRONG_NAME:
		
			UIPrintServerMessage(UI_CREATE_GROUP_WRONG_NAME);
			break;
			
		case CREAT_GROUP_FAILED:
		
			UIPrintServerMessage(UI_CREAT_GROUP_FAILED);
			break;
		
		case JOIN_GROUP_SUCCESS:
		
			UIPrintServerMessage(UI_JOIN_GROUP_SUCCESS);
			break;
			
		case JOIN_GROUP_NOT_EXIST:
		
			UIPrintServerMessage(UI_JOIN_GROUP_NOT_EXIST);
			break;
			
		case JOIN_GROUP_FAILED:
		
			UIPrintServerMessage(UI_JOIN_GROUP_FAILED);
			break;	

		case LEAVE_GROUP_SUCCESS:
		
			UIPrintServerMessage(UI_LEAVE_GROUP_SUCCESS);
			break;
			
		case LEAVE_GROUP_NOT_EXIST:
		
			UIPrintServerMessage(UI_LEAVE_GROUP_NOT_EXIST);
			break;
			
		case LEAVE_GROUP_FAILED:
		
			UIPrintServerMessage(UI_LEAVE_GROUP_FAILED);
			break;	

		default:
		
			UIPrintServerMessage(UI_INVALID_TAG);
			break;
	}
}

static void ClientManagerPrintGroupNamesStruct(GroupsNames *_groupNames)
{
	register int i;
	
	PrintGroupsNames();
    
	for(i = 0;i < _groupNames->m_size;++i)
	{
		PrintUserName(_groupNames->m_names[i]);
	}
}

static void ClientManagerPrintGroupNamesArr(char *_groupNames[], size_t _numOfGroups)
{
	register int i;
	
	PrintGroupsNames();
    
	for(i = 0; i < _numOfGroups; ++i)
	{
		PrintUserName(_groupNames[i]);
	}
}

static void ClientManagerOpenChatWindows(char *_ip, int _port, char *_filename, char *_userName, char *_groupName)
{
    openChatArgs charArgs;
    
    ClientManagerInitOpenChatArgs(&charArgs, _ip, _port, _filename, _userName, _groupName);
  	
    ClientManagerOpenTerminal(&charArgs, BEGINNING_BIG, POSITION_BIG, BASH_READ);
    ClientManagerOpenTerminal(&charArgs, BEGINNING_SMALL, POSITION_SMALL, BASH_WRITE);
}

static void ClientManagerCloseChatWindows(char *_filename)
{
    pid_t pnum1,pnum2;
    FILE* fp;
    
    if((fp = fopen(_filename, "r")) == NULL)
    {
        perror("unable to open file");
        return;
    }
    fscanf(fp,"%d",&pnum1);
    fscanf(fp,"%d",&pnum2);
    fclose(fp);
   
    kill(pnum1, SIGKILL);    
    kill(pnum2, SIGKILL);
    
    remove(_filename);
}

static void ClientManagerInitOpenChatArgs(openChatArgs *_charArgs, char *_ip, int _port, char *_filename, char *_userName, char *_groupName)
{
    _charArgs->m_ip = _ip;
    ConvertIntToString(_port, _charArgs->m_port);
    _charArgs->m_fileName = _filename;
    _charArgs->m_userName = _userName;
    _charArgs->m_groupName = _groupName;
}

static void ClientManagerOpenTerminal(openChatArgs *_charArgs, char *_beginning, char *_position, char *_out)
{
	char buffer[BUFFER];
	
	strcpy(buffer,_beginning);
	strcat(buffer,_position);
	strcat(buffer,_out);
	strcat(buffer,_charArgs->m_ip);
	strcat(buffer," ");
	strcat(buffer,_charArgs->m_port);
	strcat(buffer," ");
	strcat(buffer,_charArgs->m_fileName); 
	strcat(buffer," ");
	strcat(buffer,_charArgs->m_userName);
	strcat(buffer," ");
	strcat(buffer,_charArgs->m_groupName);
	
    system(buffer);	
}


static void ConvertIntToString(int _i, char *_str)
{
    int num, count=0;
    
    while(_i > 0)
    {
       num = _i % 10;
       _i = _i / 10;
       
       _str[count] = num + '0';
       count++;
    }
    _str[count] = '\0';
    MirrorStrChars(_str);
}

static void MirrorStrChars(char *_str)
{
    int i, size = strlen(_str);
    char temp;
    
    for(i = 0; i < size/2; i++)
    {
        temp = _str[i];
        _str[i]= _str[size-i-1]; 
        _str[size-i-1] = temp;
    }
    _str[size] = '\0'; 
}




