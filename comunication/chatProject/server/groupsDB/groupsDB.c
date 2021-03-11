#include "groupsDB.h"
#include "ipPool.h"
#include "genDLList.h"
#include "genDLListIter.h"
#include "genDLListIterFunc.h"
#include "genHashMap.h"
#include <stdio.h>
#include <stdlib.h>  /* for allocation */
#include <string.h>  /* for strlen, strcmp and strcpy */
#include <ctype.h>  /* for tolower */
#include <stdbool.h>

#define MAGIC_NUMBER 0xfeccdede
#define CAPACITY 2
#define IP_LENGTH 16
#define HASH_FOR_EACH_SUCCESS 1

#define IS_GROUPS_DB_NOT_EXIST(grp) (!(grp) || (grp)->m_magicNumber != MAGIC_NUMBER)


struct groupsDB
{
    size_t m_magicNumber;
    genHashMap *m_groupsHash;
    ipPool *m_ipPool;
};

typedef struct groupInfo
{
    char m_ip[IP_LENGTH];
    /*size_t m_port;*/
    genList *m_clientList;
}groupInfo;

typedef struct getGroupNames
{
    char **m_names;
    int m_i;
}getGroupNames;


static size_t GroupsDBGroupNameToIndex(void *_groupName);
static int GroupsDBIsSameName(void *_nameA, void *_nameB);
static void GroupsDBDestroySimpleAlloc(void *_obj);
static void GroupsDBDestroyGroupInfo(void *_info);
static groupInfo* GroupsDBCreateGroupInfo(char *_firstClientInGroup, char *_ip);
static groupsError GroupsDBAddClientToAGroup(groupInfo *_gInfo, char *_clientUserName);
static char* GroupsDBCreateName(char *_name);
static int GroupsDBCopyGroupNameToArr(const void* _key, void* _value, void* _context);


groupsDB* GroupsDBCreate()
{
    groupsDB *newGroupsDB;
    
    if((newGroupsDB = (groupsDB*)malloc(sizeof(groupsDB))))
    {
        if((newGroupsDB->m_groupsHash = GenHashMapCreate(CAPACITY, GroupsDBGroupNameToIndex, GroupsDBIsSameName)))
        {
            if((newGroupsDB->m_ipPool = IpPoolCreate()))
            {
                newGroupsDB->m_magicNumber = MAGIC_NUMBER;
                return newGroupsDB;
            }
            GenHashMapDestroy(&newGroupsDB->m_groupsHash, NULL, NULL);
        }
        free(newGroupsDB);
    }
    return NULL;
}


void GroupsDBDestroy(groupsDB *_grp)
{
    if(!IS_GROUPS_DB_NOT_EXIST(_grp))
    {
        _grp->m_magicNumber = 0;
        IpPoolDestroy(_grp->m_ipPool);
        GenHashMapDestroy(&_grp->m_groupsHash, GroupsDBDestroySimpleAlloc, GroupsDBDestroyGroupInfo);
        free(_grp);
    }
}


groupsError GroupsDBOpenNewGroup(groupsDB *_grp, char *_groupName, char *_firstClientInGroup, char *_ip)
{
    char newIp[IP_LENGTH], *newGroupName;
    groupInfo *newGroupInfo;
    groupsError e = GROUPS_ALLOCATION_FAILED;
    mapResult eMap;
    
    if(IS_GROUPS_DB_NOT_EXIST(_grp))
    {
        return GROUPS_NOT_INITIALIZED;
    }
    if(!_groupName || strlen(_groupName) < 1 || !_firstClientInGroup || !_ip)
    {
        return GROUPS_WRONG_INPUT;
    }
    if(IpPoolRecieve(_grp->m_ipPool, newIp) == OK)
    {
        if((newGroupName = GroupsDBCreateName(_groupName)))
        {
            if((newGroupInfo = GroupsDBCreateGroupInfo(_firstClientInGroup, newIp)))
            {
                if((eMap = GenHashMapInsert(_grp->m_groupsHash, newGroupName, newGroupInfo)) == MAP_SUCCESS)
                {
                    strcpy(_ip, newIp);
                    return GROUPS_SUCCESS;
                }
                else if(eMap == MAP_KEY_DUPLICATE_ERROR)
                {
                    e = GROUPS_DUPLICATE_GROUP_NAME;
                }
                GroupsDBDestroyGroupInfo(newGroupInfo);
            }
            free(newGroupName);
        }
        IpPoolReturn(_grp->m_ipPool, newIp);
    }
    else
    {
        e = GROUPS_NO_MORE_IP;
    }
    return e;
}


groupsError GroupsDBAddClientToGroup(groupsDB *_grp, char *_groupName, char *_clientUserName, char *_ip)
{
    void *gInfo;
    
    if(IS_GROUPS_DB_NOT_EXIST(_grp))
    {
        return GROUPS_NOT_INITIALIZED;
    }
    if(!_groupName || !_clientUserName)
    {
        return GROUPS_WRONG_INPUT;
    }
    if(GenHashMapFind(_grp->m_groupsHash, _groupName, &gInfo) == MAP_SUCCESS)
    {
        strcpy(_ip, ((groupInfo*)gInfo)->m_ip);
        return GroupsDBAddClientToAGroup(gInfo, _clientUserName);
    }
    return GROUPS_NOT_IN_DB;
}


groupsError GroupsDBRemoveClientFromGroup(groupsDB *_grp, char *_groupName, char *_clientUserName)
{
    void *gInfo;
    genListIter itr, end;
    char *userName;
    
    if(IS_GROUPS_DB_NOT_EXIST(_grp))
    {
        return GROUPS_NOT_INITIALIZED;
    }
    if(!_groupName || !_clientUserName)
    {
        return GROUPS_WRONG_INPUT;
    }
    
    if(GenHashMapFind(_grp->m_groupsHash, _groupName, &gInfo) == MAP_SUCCESS)
    {
        end = GenListIterEnd(((groupInfo*)gInfo)->m_clientList);
        itr = GenListIterFindFirst(GenListIterBegin(((groupInfo*)gInfo)->m_clientList), end, GroupsDBIsSameName, _clientUserName);
        userName = GenListIterGet(itr);
        if(!GenListIterEquals(itr, end) && GroupsDBIsSameName(userName, _clientUserName))
        {
            userName = GenListIterRemove(itr);
            GroupsDBDestroySimpleAlloc(userName);
            if(GenDLListIsEmpty(((groupInfo*)gInfo)->m_clientList))
            {
                IpPoolReturn(_grp->m_ipPool, ((groupInfo*)gInfo)->m_ip);
                GenHashMapRemove(_grp->m_groupsHash, _groupName, (void**)&_groupName, NULL);
                GroupsDBDestroyGroupInfo(gInfo);
                GroupsDBDestroySimpleAlloc(_groupName);
                return GROUPS_CLOSED;
            }
            return GROUPS_SUCCESS;
        }
    }
    return GROUPS_NOT_IN_DB;
}


size_t GroupsDBGetGroupNames(groupsDB *_grp, char **_groupNames)
{
    getGroupNames names;
    
    if(IS_GROUPS_DB_NOT_EXIST(_grp) || !_groupNames)
    {
        return 0;
    }
    
    names.m_i = 0;
    names.m_names = _groupNames;
    
    GenHashMapForEach(_grp->m_groupsHash, GroupsDBCopyGroupNameToArr, &names);
    
    return names.m_i;
}



static size_t GroupsDBGroupNameToIndex(void *_groupName)
{
    register int i;
    int len = strlen((char*)_groupName);
    size_t sum = 0;
    
    for(i=0; i<len; ++i)
    {
        sum += tolower(((char*)_groupName)[i]) - 'a';
    }
    return sum;
}

static int GroupsDBIsSameName(void *_nameA, void *_nameB)
{
    return strcmp(_nameA, _nameB) == 0? true: false;
}

static void GroupsDBDestroySimpleAlloc(void *_obj)
{
    if(_obj)
    {
        free(_obj);
    }
}

static void GroupsDBDestroyGroupInfo(void *_info)
{
    if(_info)
    {
        GenDLListDestroy(((groupInfo*)_info)->m_clientList, GroupsDBDestroySimpleAlloc);
        free(_info);
    }
}

static groupInfo* GroupsDBCreateGroupInfo(char *_firstClientInGroup, char *_ip)
{
    groupInfo *newGroupInfo;
    
    if((newGroupInfo = (groupInfo*)malloc(sizeof(groupInfo))))
    {
        strcpy(newGroupInfo->m_ip, _ip);
        if((newGroupInfo->m_clientList = GenDLListCreate()))
        {
            if(GroupsDBAddClientToAGroup(newGroupInfo, _firstClientInGroup) == GROUPS_SUCCESS)
            {
                return newGroupInfo;
            }
            GenDLListDestroy(newGroupInfo->m_clientList, GroupsDBDestroySimpleAlloc);
        }
        free(newGroupInfo);
    }
    return NULL;
}

static groupsError GroupsDBAddClientToAGroup(groupInfo *_gInfo, char *_clientUserName)
{
    char *userName;
    
    if((userName = GroupsDBCreateName(_clientUserName)))
    {
        if(GenDLListPushTail(_gInfo->m_clientList, userName) == OK)
        {
            return GROUPS_SUCCESS;
        }
        free(userName);
    }
    return GROUPS_ALLOCATION_FAILED;
}

static char* GroupsDBCreateName(char *_name)
{
    char *newName;
    
    if((newName = (char*)malloc(sizeof(char) * (strlen(_name)) + 1)))
    {
        strcpy(newName, _name);
        return newName;
    }
    return NULL;
}

static int GroupsDBCopyGroupNameToArr(const void* _key, void* _value, void* _context)
{
    ((getGroupNames*)_context)->m_names[((getGroupNames*)_context)->m_i] = (char*)_key;
    ++((getGroupNames*)_context)->m_i;
    return HASH_FOR_EACH_SUCCESS;
}





