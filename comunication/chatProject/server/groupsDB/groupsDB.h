#ifndef __GROUPSBD_H__
#define __GROUPSBD_H__

#include <stdio.h>  /* for size_t */

#define MAX_NUM_OF_GROUP 100


typedef struct groupsDB groupsDB;

typedef enum
{
    GROUPS_SUCCESS,
    GROUPS_FAIL,
    GROUPS_NOT_INITIALIZED,
    GROUPS_WRONG_INPUT,
    GROUPS_ALLOCATION_FAILED,
    GROUPS_DUPLICATE_GROUP_NAME,
    GROUPS_NOT_IN_DB,
    GROUPS_CLIENT_NOT_IN_DB,
    GROUPS_NO_MORE_IP,
    GROUPS_CLOSED
}groupsError;



/*
    DESCRIPTION:    Creates new groupsDB.
    
    RETURN:         Pointer to the new groupsDB created.
    
    ERRORS:         If faild returns NULL.
*/
groupsDB* GroupsDBCreate();


/*
    DESCRIPTION:    Frees the groupsDB.
    
    INPUT:          _grp - Pointer to the groupsDB created in GroupsDBCreate. should not be NULL.
*/
void GroupsDBDestroy(groupsDB *_grp);


/*
    DESCRIPTION:    Opens a new group and adds the first client to it.
    
    INPUT:          _grp - Pointer to the groupsDB created in GroupsDBCreate. should not be NULL.
                    _groupName - Group name. Should not be NULL or empty.
                    _firstClientInGroup - Name of the client to add to the group. Should not be NULL.
                    _ip - Pointer that will recieve the group IP. Should not be NULL.
    
    RETURN:         Value of GROUPS_SUCCESS if opend.
    
    ERRORS:         GROUPS_NOT_INITIALIZED if the groupsDB is not initialized.
                    GROUPS_WRONG_INPUT if the input is flawed.
                    GROUPS_DUPLICATE_GROUP_NAME if the group name already exists in the groupsDB.
                    GROUPS_NO_MORE_IP if there are no more available ips.
                    GROUPS_ALLOCATION_FAILED if the allocation failed.
*/
groupsError GroupsDBOpenNewGroup(groupsDB *_grp, char *_groupName, char *_firstClientInGroup, char *_ip);


/*
    DESCRIPTION:    Adds _clientUserName to an existing group.
    
    INPUT:          _grp - Pointer to the groupsDB created in GroupsDBCreate. should not be NULL.
                    _groupName - Group name. Should not be NULL or empty.
                    _clientUserName - Name of the client to add to the group. Should not be NULL.
                    _ip - Pointer that will recieve the group IP. Should not be NULL.
    
    RETURN:         Value of GROUPS_SUCCESS if added.
    
    ERRORS:         GROUPS_NOT_INITIALIZED if the groupsDB is not initialized.
                    GROUPS_WRONG_INPUT if the input is flawed.
                    GROUPS_ALLOCATION_FAILED if the allocation failed.
                    GROUPS_NOT_IN_DB if there is no group named _groupName in the groupsDB.
*/
groupsError GroupsDBAddClientToGroup(groupsDB *_grp, char *_groupName, char *_clientUserName, char *_ip);


/*
    DESCRIPTION:    Removes _clientUserName from an existing group.
    
    INPUT:          _grp - Pointer to the groupsDB created in GroupsDBCreate. should not be NULL.
                    _groupName - Group name. Should not be NULL or empty.
                    _clientUserName - Name of the client to remove from the group. Should not be NULL.
    
    RETURN:         Value of GROUPS_SUCCESS if the client was removed or GROUPS_CLOSED if the group closed.
    
    ERRORS:         GROUPS_NOT_INITIALIZED if the groupsDB is not initialized.
                    GROUPS_WRONG_INPUT if the input is flawed.
                    GROUPS_NOT_IN_DB if there is no group named _groupName in the groupsDB.
*/
groupsError GroupsDBRemoveClientFromGroup(groupsDB *_grp, char *_groupName, char *_clientUserName);


/*
    DESCRIPTION:    Fills the array with the existing group names.
    
    INPUT:          _grp - Pointer to the groupsDB created in GroupsDBCreate. should not be NULL.
                    _groupNames - Pointer to an array of str. Should be at least in size MAX_NUM_OF_GROUP and should not be NULL.
    
    RETURN:         The num of groups.
    
    ERRORS:         If the groupsDB is not initialized or if _groupNames is NULL returns 0.
*/
size_t GroupsDBGetGroupNames(groupsDB *_grp, char *_groupNames[]);

#endif



