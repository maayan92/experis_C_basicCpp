#ifndef __USERSDATABASE_H__
#define __USERSDATABASE_H__

#define MAX_PASSWORD_LEN 40  /* password can not be over this amount of chars */


typedef struct usersDB usersDB;

typedef enum
{
    USERS_SUCCESS,
    USERS_FAIL,
    USERS_NOT_INITIALIZED,
    USERS_WRONG_INPUT,
    USERS_ALLOCATION_FAILED,
    USERS_DUPLICATE_USERNAME,
    USERS_ALREADY_CONNECTED,
    USERS_INCORRECT_PASSWORD,
    USERS_NOT_IN_DB
}userError;


/*
    DESCRIPTION:    Creates new usersDB.
    
    RETURN:         Pointer to the new usersDB created.
    
    ERRORS:         If failed returns NULL.
*/
usersDB* UsersDBCreate();


/*
    DESCRIPTION:    Frees the usersDB.
    
    INPUT:          _users - Pointer to the usersDB created in UsersDBCreate. Should not be NULL.
*/
void UsersDBDestroy(usersDB *_users);


/*
    DESCRIPTION:    Adds  a new user to the usersDB. If _userName already exists in usersDB the user will not be added.
    
    INPUT:          _users - Pointer to the usersDB created in UsersDBCreate. Should not be NULL.
                    _userName - User username. Should be unique. Should not be NULL.
                    _password - User password. Should not be NULL.
    
    RETURN:         Value of USERS_SUCCESS if added to usersDB successfully.
    
    ERRORS:         USERS_NOT_INITIALIZED if _users is not initialized.
                    USERS_WRONG_INPUT if _userName or _password are NULL.
                    USERS_ALLOCATION_FAILED if the allocation failed.
                    USERS_DUPLICATE_USERNAME if _userName already exists in usersDB.
                    USERS_FAIL if failed to add to usersDB.
*/
userError UsersDBAddUser(usersDB *_users, const char *_userName, const char *_password);


/*
    DESCRIPTION:    Loggs in the _userName.
    
    INPUT:          _users - Pointer to the usersDB created in UsersDBCreate. Should not be NULL.
                    _userName - User username. Should be unique. Should not be NULL.
                    _password - User password. Should not be NULL.
    
    RETURN:         Value of USERS_SUCCESS if logged in successfully.
    
    ERRORS:         USERS_NOT_INITIALIZED if _users is not initialized.
                    USERS_WRONG_INPUT if _userName or _password are NULL.
                    USERS_ALREADY_CONNECTED if the _userName is already connected.
                    USERS_INCORRECT_PASSWORD if _password does not match the password connected to _userName in the usersDB.
                    USERS_NOT_IN_DB if _userName is not in usersDB.
*/
userError UsersDBLogin(usersDB *_users, const char *_userName, const char *_password);


/*
    DESCRIPTION:    Loggs out the _userName.
    
    INPUT:          _users - Pointer to the usersDB created in UsersDBCreate. Should not be NULL.
                    _userName - User username. Should be unique. Should not be NULL.
    
    RETURN:         Value of USERS_SUCCESS if logged out successfully.
    
    ERRORS:         USERS_NOT_INITIALIZED if _users is not initialized.
                    USERS_WRONG_INPUT if _userName or _password are NULL.
                    USERS_NOT_IN_DB if _userName is not in usersDB.
*/
userError UsersDBLogout(usersDB *_users, const char *_userName);




#endif
