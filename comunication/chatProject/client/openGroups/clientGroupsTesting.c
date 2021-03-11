#include <stdio.h>
#include "clientGroups.h"
#define MAX_LEN 15

typedef enum test
{
	SUCCESS,
	FAILED
}test;

static void TestPrintResult(test (*_funcToTest)(void), char *_funcName);
test TestCreateClientGroups();
test TestDestroyClientGroups();
test TestClientAddGroup();
test TestClientFindGroup();
test TestClientRemoveGroup();

int main()
{
	TestPrintResult(TestCreateClientGroups, "TestCreateClientGroups");        
	TestPrintResult(TestDestroyClientGroups, "TestDestroyClientGroups");        
	TestPrintResult(TestClientAddGroup, "TestClientAddGroup");
	TestPrintResult(TestClientFindGroup, "TestClientFindGroup");
	TestPrintResult(TestClientRemoveGroup, "TestClientRemoveGroup");


	return 0;
}


test TestCreateClientGroups()
{
	clientGroups* newClient=NULL;
	if(!(newClient = ClientGroupsCreate()))
	{
		return FAILED;
	}
	ClientGroupDestroy(newClient);
	return SUCCESS;

}

test TestDestroyClientGroups()
{
	clientGroups* newClient=ClientGroupsCreate();
	ClientGroupDestroy(newClient);
	return SUCCESS;

}

test TestClientAddGroup()
{
	char group[MAX_LEN]="groupA",file[MAX_LEN]="fileOne";
	clientGroups* newClient=ClientGroupsCreate();
	if(ClientAddGroup(newClient, group, file)==GROUP_SUCCESS)
	{
		ClientGroupDestroy(newClient);
		return SUCCESS;
	}
	ClientGroupDestroy(newClient);
	return FAILED;
}

test TestClientFindGroup()
{
	char group[MAX_LEN]="groupA",file[MAX_LEN]="fileOne";
	clientGroups* newClient=ClientGroupsCreate();
	ClientAddGroup(newClient, group, file);
	if(ClientFindGroup(newClient, group))
	{
		ClientGroupDestroy(newClient);
		return SUCCESS;	
	}
	ClientGroupDestroy(newClient);
	return FAILED;
}


test TestClientRemoveGroup()
{
	char group[MAX_LEN]="groupA",file[MAX_LEN]="fileOne";
	
	clientGroups* newClient=ClientGroupsCreate();
	ClientAddGroup(newClient, group, file);
	ClientRemoveGroup(newClient, group, NULL);
	if(ClientFindGroup(newClient, group))
	{
		ClientGroupDestroy(newClient);
		return FAILED;	
	}
	ClientGroupDestroy(newClient);
	return SUCCESS;
}






static void TestPrintResult(test (*_funcToTest)(void), char *_funcName)
{
    test r = _funcToTest();
    printf("%s\t %s\n", _funcName, r==SUCCESS? "SUCCESS": "FAILED");
}
