#ifndef __CLIENT_GROUPS_H
#define __CLIENT_GROUPS_H

#include <stdio.h>  /* for size_t */

#define MAX_NUM_OF_GROUP 100


typedef enum
{
    GROUP_SUCCESS,
    GROUP_FAIL,
    GROUP_NOT_INITIALIZED,
    GROUP_WRONG_INPUT,
    GROUP_ALLOCATION_FAILED,
    GROUP_NOT_IN_DB
}clinetError;

typedef struct clientGroups clientGroups;



/*
    DESCRIPTION:    Creates clinet Groups.
    
    RETURN:         Pointer to the new client Groups.
    
    ERRORS:         If failed returns NULL.
*/
clientGroups* ClientGroupsCreate();

/*
    DESCRIPTION:    Frees the clientGroupDB.
    
    INPUT:          _groups - Pointer to the clientGroupDB created in ClientGroupsCreate. Should not be NULL.
*/
void ClientGroupDestroy(clientGroups *_groups);

/*
    DESCRIPTION:    Adding a group in the clientGroupDB.
    
    INPUT:          _groups - Pointer to the clientGroupDB created in ClientGroupsCreate. Should not be NULL.
    				_groupName - name of added group.
    				_fileName - name of added file. 
    
    RETURN:			GROUP_SUCCESS - if group was added successfully.
    	
    ERRORS:         GROUP_NOT_INITIALIZED - if group that wasn't created in clientGroupDB.
    				GROUP_WRONG_INPUT - if _groupName or _fileName are NULL.
    				GROUP_ALLOCATION_FAILED - if allocation failed.
    				GROUP_FAIL - if destroy elements failed.
*/
clinetError ClientAddGroup(clientGroups *_groups,const char *_groupName, const char *_fileName);

/*
    DESCRIPTION:    Remove group in the clientGroupDB.
    
    INPUT:          _groups - Pointer to the clientGroupDB that was created in ClientGroupsCreate. Should not be NULL.
    				_groupName - name of group.
    				_fileName - pointer that will receive the file name. should not be NULL. 
    
    RETURN:			GROUP_SUCCESS - if group was removed successfully.
    	
    ERRORS:         GROUP_NOT_INITIALIZED - if group that wasn't created in clientGroupDB.
    				GROUP_WRONG_INPUT - if _groupName or _fileName are NULL.
    				GROUP_FAIL - if remove group from DS failed.
*/
clinetError ClientRemoveGroup(clientGroups *_groups,char *_groupName,char *_fileName);


/*
    DESCRIPTION:    Find group in the clientGroupDB.
    
    INPUT:          _groups - Pointer to the clientGroupDB that was created in ClientGroupsCreate. Should not be NULL.
    				_groupName - name of group.
    
    RETURN:			if group was found - return true.
					if group wasn't found - return false.
*/
int ClientFindGroup(clientGroups *_groups, const char *_groupName);


/*
    DESCRIPTION:    Fills the array with the existing group names.
    
    INPUT:          _grp - Pointer to the clientGroupDB created in ClientGroupsCreate. should not be NULL.
                    _groupNames - Pointer to an array of str. Should be at least in size MAX_NUM_OF_GROUP and should not be NULL.
    
    RETURN:         The num of groups.
    
    ERRORS:         If the groupsDB is not initialized or if _groupNames is NULL returns 0.
*/
size_t GroupsDBGetGroupNames(clientGroups *_grp, char **_groupNames);


#endif
