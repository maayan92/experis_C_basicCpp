#ifndef __UI_H__
#define __UI_H__

typedef enum
{
	START_MENU,
	MAIN_MENU
}Menu;

typedef enum
{
	UI_SIGN_IN_SUCCESS,
	UI_SIGN_IN_FAILED,
	UI_USERNAME_ALREADY_EXIST,
	
	UI_LOG_IN_SUCCESS,
	UI_USERS_ALREADY_CONNECTED,
	UI_USERS_INCORRECT_PASSWORD,
	UI_USERS_NOT_IN_DB,
	
	UI_LOG_OUT_SUCCESS,
	
	UI_CREATE_GROUP_SUCCESS,
	UI_CREATE_GROUP_ALREADY_EXIST,
	UI_CREATE_GROUP_WRONG_NAME,
	UI_CREAT_GROUP_FAILED,
	
	UI_JOIN_GROUP_SUCCESS,
	UI_JOIN_GROUP_FAILED,
	UI_JOIN_GROUP_NOT_EXIST,
	
	UI_LEAVE_GROUP_SUCCESS,
	UI_LEAVE_GROUP_NOT_EXIST,
	UI_LEAVE_GROUP_FAILED,
	
	UI_INVALID_TAG
	
}SvrMessage;

typedef enum
{
	UI_SIGN_IN = 1,
	UI_LOG_IN,
	UI_EXIT,
	UI_CREATE_GROUP,
	UI_LEAVE_GROUP,
	UI_JOIN_GROUP,
	UI_LOG_OUT,
	UI_NUM_OF_ACTIONS
}Action;

typedef enum
{
	CONNECTION_FAILED,
	SEND_MESSAGE_FAILED,
	INVALID_NAME,
	INVALID_PASSWORD,
	INVALID_GROUP_NAME,
	ALREADY_IN_GROUP,
	NOT_IN_GROUP,
	NEW_GROUP_NAME
}Error;


/*
	Description: print the start manu/main menu.
	Input: _menu - value from menu enum.
	Return: return the action the user choose.
*/
Action UIPrintMenuGetAction(Menu _menu);

/*
	Description: print the message the client got from the server.
	Input: _msg - value from message enum.
	Return:
*/
void UIPrintServerMessage(SvrMessage _msg);

/*
	Description: print the error the client got.
	Input: _err - value from error enum.
	Return:
*/
void PrintError(Error _err);

/*
	Description: print the user name.
	Input: _name - user's name.
	Return:
*/
void PrintUserName(char *_name);

/*
	Description: get the name and password from the user.
	Input: _name - user's name, _password - user's password.
	Return:
*/
void GetUsersDetails(char *_name, char *_password);

/*
	Description: get the group name from the user.
	Input: _groupName - group's name.
	Return:
*/
void GetGroupName(char *_groupName);

/*
	Description: ptints a title presenting the group names.
	Input:
	Return:
*/
void PrintGroupsNames();

/*
	Description: prints welcome banner.
	Input:
	Return:
*/
void UIPrintBanner();




#endif
