#include <stdio.h>
#include <string.h>
#include <stdlib.h>  /* for system */
#include "ui.h"

#define LENGTH 200

Action UIPrintMenuGetAction(Menu _menu)
{
	Action action;
	int result;
	printf("Choose Action:\n");
	
	if(START_MENU == _menu)
	{
		do
		{
			printf("\nStart Menu \n");
			printf("%d - Sign in \n",UI_SIGN_IN);
			printf("%d - Log in \n",UI_LOG_IN);
			printf("%d - Exit\n",UI_EXIT);
				
			result = scanf("%u",&action);
			getchar();
			
		}while(1 != result || (UI_EXIT < action || UI_SIGN_IN > action));
			
		return action;
	}
	
	do
	{
		printf("\nMain Menu \n");
		printf("%d - Create group \n",UI_CREATE_GROUP);
		printf("%d - Leave group \n",UI_LEAVE_GROUP);
		printf("%d - Join group \n",UI_JOIN_GROUP);
		printf("%d - Log out \n",UI_LOG_OUT);
		
		result = scanf("%u",&action);
		getchar();

	}while(1 != result || (UI_NUM_OF_ACTIONS <= action || UI_CREATE_GROUP > action));
	
	return action;
}

void UIPrintServerMessage(SvrMessage _msg)
{
	switch(_msg)
	{
		case UI_SIGN_IN_SUCCESS:
		
			printf("\nUser added successfully!\n");
			break;
		
		case UI_SIGN_IN_FAILED:
		
			printf("\nFailed to add user!\n");
			break;
		
		case UI_USERNAME_ALREADY_EXIST:
		
			printf("\nUser name is already exists!\n");
			break;
		
		case UI_LOG_IN_SUCCESS:
		
			printf("\nUser logged in successfully!\n");
			break;
		
		case UI_USERS_ALREADY_CONNECTED:
		
			printf("\nUser is already connected!\n");
			break;
		
		case UI_USERS_INCORRECT_PASSWORD:
		
			printf("\nWrong password!\n");
			break;
	
		case UI_USERS_NOT_IN_DB:
		
			printf("\nUser does not exist!\n");
			break;
			
		case UI_LOG_OUT_SUCCESS:
		
			printf("\nLogged out successfully!\n");
			break;
		
		case UI_CREATE_GROUP_SUCCESS:
		
			printf("\nCreated group successfully!\n");
			break;
		
		case UI_CREATE_GROUP_ALREADY_EXIST:
		
			printf("\nGroup name alredy exists!\n");
			break;
		
		case UI_CREATE_GROUP_WRONG_NAME:
		
			printf("\nInvalid group name!\n");
			break;
			
		case UI_CREAT_GROUP_FAILED:
		
			printf("\nGroup failed to open!\n");
			break;
		
		case UI_JOIN_GROUP_SUCCESS:
		
			printf("\nJoined Group successfully!\n");
			break;
			
		case UI_JOIN_GROUP_NOT_EXIST:
		
			printf("\nGroup does not exist!\n");
			break;
			
		case UI_JOIN_GROUP_FAILED:
		
			printf("\nJoin group failed!\n");
			break;
		
		case UI_LEAVE_GROUP_SUCCESS:
		
			printf("\nLeft group successfully!\n");
			break;
		
		case UI_LEAVE_GROUP_NOT_EXIST:
		
			printf("\nGroup does not exist!\n");
			break;
			
		case UI_LEAVE_GROUP_FAILED:
		
			printf("\nLeft group failed!\n");
			break;
			
		case UI_INVALID_TAG:
		
			printf("\nInvalid request!\n");
			break;
	}
}

void PrintError(Error _err)
{
	switch(_err)
	{
		case CONNECTION_FAILED:
		
			printf("\nConnection failed! please try to connect again!\n");
			break;
			
		case SEND_MESSAGE_FAILED:
		
			printf("\nFailed to send message!\n");
			break;
			
		case INVALID_NAME:
		
			printf("\nUser name too short, please choose a name with at least 2 characters!\n");
			break;
			
		case INVALID_PASSWORD:
		
			printf("\nPassword too short, please choose a password with at least 6 characters!\n");
			break;
			
		case INVALID_GROUP_NAME:
		
			printf("\nGroup Name too short, please choose a name with at least 2 characters!\n");
			break;
		
		case ALREADY_IN_GROUP:
		
			printf("\nUser is already in the group!\n");
			break;
			
		case NOT_IN_GROUP:
		
			printf("\nUser is not in the group!\n");
			break;
			
		case NEW_GROUP_NAME:
		
			printf("\nPlease enter a group name with no spaces!\n");
			break;
	}
}

void PrintUserName(char *_name)
{
	printf("%s\n",_name);
}

void GetUsersDetails(char *_name, char *_password)
{
	printf("\nPlease enter user name and password:\n");
	
	printf("name: ");
	scanf("%s", _name);
	getchar();
	
	printf("password: ");
	scanf("%s", _password);
	getchar();
}

void GetGroupName(char *_groupName)
{
	printf("\ngroup name: ");
	scanf("%s", _groupName);
	getchar();
}

void PrintGroupsNames()
{
	printf("\nAll group names:\n");
	
}

void UIPrintBanner()
{
    system("clear");
    printf("\n");
    printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗██╗\n");
    printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝██║\n");
    printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  ██║\n");
    printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  ╚═╝\n");
    printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗██╗\n");
    printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝╚═╝\n\n");
}



