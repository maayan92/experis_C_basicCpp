#include "ipPool.h"
#include <stdio.h>
#include <string.h> /*for strcmp*/
#define MAX_LEN 16 /*maximum chars of ip address*/

typedef enum test
{
	SUCCESS,
	FAILED
}test;

static void TestPrintResult(test (*_funcToTest)(void), char *_funcName);
test TestCreateIpPool();
test TestDestroyIpPool();
test TestRecieveThreeIpAddresses();
test TestRecieveIpAddress_PoolNotInit();
test TestReturnTwoIpAddresses();


int main()
{
	TestPrintResult(TestCreateIpPool, "TestCreateIpPool");        
	TestPrintResult(TestDestroyIpPool,"TestDestroyIpPool");
	TestPrintResult(TestRecieveThreeIpAddresses,"TestRecieveThreeIpAddresses");
	TestPrintResult(TestRecieveIpAddress_PoolNotInit,"TestRecieveIpAddress_PoolNotInit");
	TestPrintResult(TestReturnTwoIpAddresses,"TestReturnTwoIpAddresses");
	
	return 0;
}



test TestCreateIpPool()
{
	ipPool* newIpPool= NULL;
	newIpPool = IpPoolCreate();
	
	if(!newIpPool)
	{
		return FAILED;
	}
	IpPoolDestroy(newIpPool);
	return SUCCESS;
}

test TestDestroyIpPool()
{
	ipPool* newIpPool= NULL;
	newIpPool = IpPoolCreate();
	IpPoolDestroy(newIpPool);
	
	return SUCCESS;
}

test TestRecieveThreeIpAddresses()
{
	char str1[MAX_LEN],str2[MAX_LEN],str3[MAX_LEN];
	ipPool* newIpPool= NULL;
	newIpPool = IpPoolCreate();
	IpPoolRecieve(newIpPool,str1);
	IpPoolRecieve(newIpPool,str2);
	IpPoolRecieve(newIpPool,str3);
	
	if(strcmp(str3 ,"224.0.0.98")==0)
	{
		IpPoolDestroy(newIpPool);
		return SUCCESS;
	}
	IpPoolDestroy(newIpPool);
	return FAILED;
}

test TestRecieveIpAddress_PoolNotInit()
{
	char str1[MAX_LEN];
	ipPool* newIpPool= NULL;
	if(IpPoolRecieve(newIpPool,str1)==OK)
	{
		return FAILED;
	}
	return SUCCESS;
}

test TestReturnTwoIpAddresses()
{
	char str1[MAX_LEN],str2[MAX_LEN],str3[MAX_LEN];
	ipPool* newIpPool= NULL;
	newIpPool = IpPoolCreate();
	IpPoolRecieve(newIpPool,str1);
	IpPoolRecieve(newIpPool,str2);
	IpPoolRecieve(newIpPool,str3);
	IpPoolReturn(newIpPool,str1);
	IpPoolReturn(newIpPool,str3);
	if(IpPoolNumOfAddresses(newIpPool)!=99)
	{
		IpPoolDestroy(newIpPool);
		return FAILED;
	}
	IpPoolDestroy(newIpPool);
	return SUCCESS;
}

static void TestPrintResult(test (*_funcToTest)(void), char *_funcName)
{
    test r = _funcToTest();
    printf("%s\t %s\n", _funcName, r==SUCCESS? "SUCCESS": "FAILED");
}
