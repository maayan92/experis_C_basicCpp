#include "usersDataBase.h"
#include "genHashMap.h"
#include <stdio.h>
#include <stdlib.h>  /* for allocation */
#include <string.h>  /* for strlen, strcmp and strcpy */
#include <ctype.h>  /* for tolower */
#include <stdbool.h>

#define MAGIC_NUMBER 0xfeadcade
#define CAPACITY 500

#define IS_USERS_DB_NOT_EXIST(usr) (!(usr) || (usr)->m_magicNumber != MAGIC_NUMBER)


struct usersDB
{
    size_t m_magicNumber;
    genHashMap *m_usersHash;
};

typedef struct userInfo
{
    char m_password[MAX_PASSWORD_LEN];
    int m_isActive;
}userInfo;


static size_t UsersDBUsernameToIndex(void *_username);
static int UsersDBIsSameUsername(void *_userA, void *_userB);
static void UsersDBDestroyInfo(void *_info);
static userInfo* UserInfoCreate(const char *_password);



usersDB* UsersDBCreate()
{
    usersDB *newUsers;
    
    if(!(newUsers = (usersDB*)malloc(sizeof(usersDB))) || !(newUsers->m_usersHash = GenHashMapCreate(CAPACITY, UsersDBUsernameToIndex, UsersDBIsSameUsername)))
    {
        return NULL;
    }
    newUsers->m_magicNumber = MAGIC_NUMBER;
    return newUsers;
}

void UsersDBDestroy(usersDB *_users)
{
    if(!IS_USERS_DB_NOT_EXIST(_users))
    {
        _users->m_magicNumber = 0;
        GenHashMapDestroy(&_users->m_usersHash, UsersDBDestroyInfo, UsersDBDestroyInfo);
        free(_users);
    }
}

userError UsersDBAddUser(usersDB *_users, const char *_userName, const char *_password)
{
    char *userNameAlloc;
    userInfo *userInfoAlloc;
    mapResult e;
    
    if(IS_USERS_DB_NOT_EXIST(_users))
    {
        return USERS_NOT_INITIALIZED;
    }
    if(!_userName || !_password)
    {
        return USERS_WRONG_INPUT;
    }
    if(!(userNameAlloc = (char*)malloc((strlen(_userName) + 1) * sizeof(char))))
    {
        return USERS_ALLOCATION_FAILED;
    }
    strcpy(userNameAlloc, _userName);
    if(!(userInfoAlloc = UserInfoCreate(_password)))
    {
        free(userNameAlloc);
        return USERS_ALLOCATION_FAILED;
    }
    
    if((e = GenHashMapInsert(_users->m_usersHash, userNameAlloc, userInfoAlloc)) == MAP_SUCCESS)
    {
        return USERS_SUCCESS;
    }
    
    UsersDBDestroyInfo(userNameAlloc);
    UsersDBDestroyInfo(userInfoAlloc);
    
    if(e == MAP_KEY_DUPLICATE_ERROR)
    {
        return USERS_DUPLICATE_USERNAME;
    }
    
    return USERS_FAIL;
}

userError UsersDBLogin(usersDB *_users, const char *_userName, const char *_password)
{
    void *userInfoInHash;
    
    if(IS_USERS_DB_NOT_EXIST(_users))
    {
        return USERS_NOT_INITIALIZED;
    }
    if(!_userName || !_password)
    {
        return USERS_WRONG_INPUT;
    }
    
    if(GenHashMapFind(_users->m_usersHash, _userName, &userInfoInHash) == MAP_SUCCESS)
    {
        if(((userInfo*)userInfoInHash)->m_isActive)
        {
            return USERS_ALREADY_CONNECTED;
        }
        if(strcmp((char*)((userInfo*)userInfoInHash)->m_password, _password) == 0)
        {
            ((userInfo*)userInfoInHash)->m_isActive = true;
            return USERS_SUCCESS;
        }
        return USERS_INCORRECT_PASSWORD;
    }
    return USERS_NOT_IN_DB;
}

userError UsersDBLogout(usersDB *_users, const char *_userName)
{
    void *userInfoInHash;
    
    if(IS_USERS_DB_NOT_EXIST(_users))
    {
        return USERS_NOT_INITIALIZED;
    }
    if(!_userName)
    {
        return USERS_WRONG_INPUT;
    }
    
    if(GenHashMapFind(_users->m_usersHash, _userName, &userInfoInHash) == MAP_SUCCESS)
    {
        ((userInfo*)userInfoInHash)->m_isActive = false;
        return USERS_SUCCESS;
    }
    return USERS_NOT_IN_DB;
}


static size_t UsersDBUsernameToIndex(void *_username)
{
    register int i;
    int len = strlen((char*)_username);
    size_t sum = 0;
    
    for(i=0; i<len; ++i)
    {
        sum += tolower(((char*)_username)[i]) - 'a';
    }
    return sum;
}

static int UsersDBIsSameUsername(void *_userA, void *_userB)
{
    return strcmp(_userA, _userB) == 0? true: false;
}

static void UsersDBDestroyInfo(void *_info)
{
    free(_info);
}

static userInfo* UserInfoCreate(const char *_password)
{
    userInfo *userInfoAlloc;
    if(!(userInfoAlloc = (userInfo*)malloc(sizeof(userInfo))))
    {
        return NULL;
    }
    
    strcpy(userInfoAlloc->m_password, _password);
    userInfoAlloc->m_isActive = false;
    
    return userInfoAlloc;
}





