#include <stdio.h>
#include <string.h>
#include "protocol.h"

#define BUFFER_SIZE 100

typedef enum
{
	SUCCEDD,
	FAILED
}Result;
/*
Result TestUserInfoSetBuffer_Valid()
{
	UserInfo user = {SIGNIN,"maayan","12345678"};
	
	char ans[BUFFER_SIZE];
	
	ProtocolUserInfoSetBuffer(&user,ans,BUFFER_SIZE);
	
	if(0 != strncmp(ans + 3, user.m_name,6) || 0 != strncmp(ans + 10, user.m_password,9))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestGetUserInfoByBuffer_Valid()
{
	UserInfo userRes, user = {SIGNIN,"maayan","12345678"};
	
	char ans[BUFFER_SIZE];
	
	ProtocolUserInfoSetBuffer(&user,ans,BUFFER_SIZE);
	
	ProtocolUserInfoGetByBuffer(ans,&userRes);
	
	if(SIGNIN != userRes.m_tag || 0 != strcmp(user.m_name,userRes.m_name) || strcmp(user.m_password,userRes.m_password))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}



static void PrintRes(char *_str, Result(*ptrPrint)(void))
{
	static int count = 0;
	++count;
	
	printf("\n%d. %-40s \t %s \n", count, _str, (SUCCEDD == (*ptrPrint)()) ? "succedded" : "failed");
}
*/
int main()
{
	/*Buffer by user info*/
	/*POS
	printf("\n--- Buffer by user info: ---\n");
	PrintRes("TestUserInfoSetBuffer_Valid:",TestUserInfoSetBuffer_Valid);
	NEG*/
	
	/*User info by buffer*/
	/*POS
	printf("\n--- User info by buffer: ---\n");
	PrintRes("TestGetUserInfoByBuffer_Valid:",TestGetUserInfoByBuffer_Valid);
*/
	return 0;
}


