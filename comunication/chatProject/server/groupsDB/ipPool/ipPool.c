#include "ipPool.h"
#include "genDLList.h"
#include <stdio.h>
#include <string.h>/*for strlen,strcpy*/
#include <stdlib.h> /*for allocation*/

#define MAGIC_NUMBER 0xceadcade
#define NO_MAGIC_NUMBER 0xbeadcade
#define IP_LENGTH 16 /*maximum chars of ip address*/
#define IP_BASE "224.0.0." /* All addresses in pool have the same IP_BASE - Multicast Communication */


struct ipPool
{
    size_t m_magicNumber;
    genList* m_iplist;  /* using list as queue */
};

static int FillIpPool(genList* _IpList);
static void DestroyIP(void* _ip);
static void ConvertIntToString(int _i,char* _str);
static void MirrorStrChars(char*_str);

ipPool* IpPoolCreate()
{
    ipPool* newIpPool;
    
    if(!(newIpPool = (ipPool*)malloc(sizeof(ipPool))))
    {
        return NULL;
    }
    if(!(newIpPool->m_iplist = GenDLListCreate()))
    {
        free(newIpPool);
        return NULL;
    }
    if(FillIpPool(newIpPool->m_iplist)!=IP_ADDRESSES)
    {
        GenDLListDestroy(newIpPool->m_iplist,DestroyIP);
        free(newIpPool);
        return NULL;
    }
    newIpPool->m_magicNumber = MAGIC_NUMBER;
    
    return newIpPool;
}

void IpPoolDestroy(ipPool* _ipPool)
{
    if(!_ipPool || (_ipPool->m_magicNumber!=MAGIC_NUMBER))
    {
        return;
    }
    _ipPool->m_magicNumber = NO_MAGIC_NUMBER;
    GenDLListDestroy(_ipPool->m_iplist,DestroyIP);
    free(_ipPool);
}

ErrorCode IpPoolRecieve(ipPool* _ipPool,char* _str)
{
    void *temp;
    if(!_ipPool || (_ipPool->m_magicNumber!=MAGIC_NUMBER))
    {
        return ERROR_NOT_INITIALIZED;
    }
    if(!_str)
    {
        return ERROR_WRONG_INPUT;
    }
    if(GenDLListPopHead(_ipPool->m_iplist, &temp) == OK)
    {
        strcpy(_str, temp);
        DestroyIP(temp);
        return OK;
    }
    return ERROR_UNDERFLOW;

}

ErrorCode IpPoolReturn(ipPool* _ipPool,char* _str)
{
    char *newStr;
    
    if(!_ipPool || (_ipPool->m_magicNumber!=MAGIC_NUMBER))
    {
        return ERROR_NOT_INITIALIZED;
    }
    if(!(newStr = (char*)malloc(sizeof(char) * (strlen(_str) + 1))))
    {
        return ERROR_ALLOCATION_FAILED;
    }
    
    strcpy(newStr, _str);
    
    if(GenDLListPushTail(_ipPool->m_iplist, newStr)!=OK)
    {
    	return ERROR_WRONG_INPUT;
    }

    return OK;
}

size_t IpPoolNumOfAddresses(ipPool* _ipPool)
{
	if(!_ipPool || (_ipPool->m_magicNumber!=MAGIC_NUMBER))
    {
        return 0;
    }
	return GenDLListCountItems(_ipPool->m_iplist);
}



/*-----------------------------static functions-----------------------------*/

static void DestroyIP(void* _ip)
{
    if(!_ip)
    {
        return;
    }
    free(_ip);
}


static int FillIpPool(genList* _ipList)
{
    char* ip;
    char singleIP[IP_LENGTH];
    register int i;
    
    for(i = 1; i <= IP_ADDRESSES; i++)
    {
        if(!(ip = (char*)malloc(sizeof(char)* IP_LENGTH)))
        {
            return i;
        }
        strcpy(ip,IP_BASE);
        ConvertIntToString(i,singleIP);
        strcat(ip,singleIP);
        if(GenDLListPushTail(_ipList, ip) != OK)
        {
            return i-1;
        }
    }
    return i-1;
}


static void ConvertIntToString(int _i, char* _str)
{
    int num, count=0;
    
    while(_i>0)
    {
       num = _i % 10;
       _i = _i/10;
       
       _str[count] =num+'0';
       count++;
    }
    _str[count] = '\0';
    MirrorStrChars(_str);
    return;

}

static void MirrorStrChars(char*_str)
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




