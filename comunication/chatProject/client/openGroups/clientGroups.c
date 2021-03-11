#include "clientGroups.h"
#include "genHashMap.h"
#include <stdio.h>
#include <stdlib.h> /*for malloc*/
#include <string.h> /*for strlen, strcmp,strcpy*/
#include <stdbool.h>/*for true/false value*/
#include <ctype.h>  /* for tolower */

#define GROUP_CAPACITY 20
#define HASH_FOR_EACH_SUCCESS 1

#define MAGIC_NUMBER 0xbefacefd
#define IS_CLIENT_GROUPS_NOT_EXIST(group) (!(group) || (group)->m_magicNumber != MAGIC_NUMBER)


struct clientGroups
{
	size_t m_magicNumber;
	genHashMap* m_groupsHash;
};

typedef struct getGroupNames
{
    char **m_names;
    int m_i;
}getGroupNames;


static size_t ClientDBGroupNameToIndex(void *_groupName);
static int ClientDBIsSameGroupName(void *_groupA, void *_groupB);
static void ClientDBDestroyGroup(void *_info);
static int ClientDBCopyGroupNameToArr(const void* _key, void* _value, void* _context);


clientGroups* ClientGroupsCreate()
{
	clientGroups* newClientGroups;
	if(!(newClientGroups = (clientGroups*)malloc(sizeof(clientGroups))))
	{
		return NULL;
	} 
	if(!(newClientGroups->m_groupsHash = GenHashMapCreate(GROUP_CAPACITY, ClientDBGroupNameToIndex, ClientDBIsSameGroupName)))
	{
		free(newClientGroups);
		return NULL;
	}
	newClientGroups->m_magicNumber = MAGIC_NUMBER;
	return newClientGroups;
}

void ClientGroupDestroy(clientGroups *_groups)
{
	if(!IS_CLIENT_GROUPS_NOT_EXIST(_groups))
    {
        _groups->m_magicNumber = 0;
        GenHashMapDestroy(&_groups->m_groupsHash, ClientDBDestroyGroup, ClientDBDestroyGroup);
        free(_groups);
    }
}


clinetError ClientAddGroup(clientGroups *_groups, const char *_groupName, const char *_fileName)
{
	char *groupNameAlloc, *fileNameAlloc;
	if(IS_CLIENT_GROUPS_NOT_EXIST(_groups))
	{
		return GROUP_NOT_INITIALIZED;
	}
	if(!_groupName || !_fileName)
    {
        return GROUP_WRONG_INPUT;
    }
    if(!(groupNameAlloc = (char*)malloc((strlen(_groupName) + 1) * sizeof(char))))
    {
        return GROUP_ALLOCATION_FAILED;
    }
    if(!(fileNameAlloc = (char*)malloc((strlen(_fileName) + 1) * sizeof(char))))
    {
    	free(groupNameAlloc);
        return GROUP_ALLOCATION_FAILED;
    }
    strcpy(fileNameAlloc,_fileName);    
    strcpy(groupNameAlloc, _groupName);
    if(GenHashMapInsert(_groups->m_groupsHash, groupNameAlloc, fileNameAlloc) != MAP_SUCCESS)
    {
    	free(fileNameAlloc);
    	free(groupNameAlloc);
    	return GROUP_FAIL;
    }
    return GROUP_SUCCESS;
}

clinetError ClientRemoveGroup(clientGroups *_groups, char *_groupName,char *_fileName)
{
	char* tempGroupName, *tempFileName;
	if(IS_CLIENT_GROUPS_NOT_EXIST(_groups))
	{
		return GROUP_NOT_INITIALIZED;
	}
	if(!_groupName)
    {
        return GROUP_WRONG_INPUT;
    }
    if(GenHashMapRemove(_groups->m_groupsHash, _groupName, (void**)&tempGroupName, (void**)&tempFileName)!=MAP_SUCCESS)
    {
    	return GROUP_FAIL;
    }
    strcpy(_fileName,tempFileName);
    ClientDBDestroyGroup(tempGroupName);
    ClientDBDestroyGroup(tempFileName);

    return GROUP_SUCCESS;
}

int ClientFindGroup(clientGroups *_groups, const char *_groupName)
{
	char *_fileName;
	if(IS_CLIENT_GROUPS_NOT_EXIST(_groups))
	{
		return false;
	}
	if(!_groupName)
    {
        return false;
    }
    if(GenHashMapFind(_groups->m_groupsHash, _groupName, (void*)&_fileName)!=MAP_SUCCESS)
    {
    	return false;
    }
    return true;
}

size_t GroupsDBGetGroupNames(clientGroups *_grp, char **_groupNames)
{
    getGroupNames names;
    
    if(IS_CLIENT_GROUPS_NOT_EXIST(_grp) || !_groupNames)
    {
        return 0;
    }
    
    names.m_i = 0;
    names.m_names = _groupNames;
    
    GenHashMapForEach(_grp->m_groupsHash, ClientDBCopyGroupNameToArr, &names);
    
    return names.m_i;
}



static size_t ClientDBGroupNameToIndex(void *_groupName)
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

static int ClientDBIsSameGroupName(void *_groupA, void *_groupB)
{
    return strcmp(_groupA, _groupB) == 0? true: false;
}

static void ClientDBDestroyGroup(void *_info)
{
    free(_info);
}

static int ClientDBCopyGroupNameToArr(const void* _key, void* _value, void* _context)
{
    ((getGroupNames*)_context)->m_names[((getGroupNames*)_context)->m_i] = (char*)_key;
    ++((getGroupNames*)_context)->m_i;
    return HASH_FOR_EACH_SUCCESS;
}

