#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdio.h>  /* for size_t */
#include <sys/socket.h>  /* for stream type */


typedef struct server server;

typedef void(*messageHandlerFunc)(char*, int, void*);

typedef enum
{
    SOCK_SUCCESS,
    SOCK_FAIL,
    SOCK_NOT_INITIALIZED,
    SOCK_WRONG_INPUT,
    SOCK_CLOSED,
    SOCK_NO_BLOCKING,
    SOCK_ALLOCATION_FAILED,
    SOCK_FULL
}sockError;



/*
    DESCRIPTION:    Creates new server.
    
    INPUT:          _address - String of the adress to connect with. If NULL will be set as INADDR_ANY.
                    _port - Port to use.
    
    RETURN:         Pointer to the new server created.
    
    ERRORS:         If failed returns NULL.
*/
server* ServerCreate(char *_address, int _port);


/*
    DESCRIPTION:    Frees the server.
    
    INPUT:          _srvr - Pointer to server created in ServerCreate. Should not be NULL.
*/
void ServerDestroy(server *_srvr);


/*
    DESCRIPTION:    Updates the new activity requests to the server.
    
    INPUT:          _srvr - Pointer to server created in ServerCreate. Should not be NULL.
    
    RETURN:         SOCK_SUCCESS if updated.
    
    ERRORS:         SOCK_NOT_INITIALIZED if the server is not initialized.
                    SOCK_FAIL if failed to update.
*/
sockError ServerNewActivity(server *_srvr);


/*
    DESCRIPTION:    Accepts a new client to the server. Sould be called after ServerNewActivity.
    
    INPUT:          _srvr - Pointer to server created in ServerCreate. Should not be NULL.
    
    RETURN:         SOCK_SUCCESS if accepted.
    
    ERRORS:         SOCK_NOT_INITIALIZED if the server is not initialized.
                    SOCK_ALLOCATION_FAILED if the allocation failed.
                    SOCK_FAIL if failed to accept.
                    SOCK_FULL if the server is full and can not accept nwe clients.
*/
sockError ServerAcceptServer(server *_srvr);


/*
    DESCRIPTION:    Runs the server and recives messages. Sould be called after ServerNewActivity.
    
    INPUT:          _srvr - Pointer to server created in ServerCreate. Should not be NULL.
                    _messageFunc - Pointer to func that makes an action with the message recieved. Sould not be NULL.
                    _context - User context for messageHandlerFunc.
    
    RETURN:         Value of SOCK_SUCCESS if executed.
    
    ERRORS:         SOCK_NOT_INITIALIZED if the server is not initialized.
                    SOCK_WRONG_INPUT if the input is flawed.
*/
sockError ServerRunAndReceive(server *_srvr, messageHandlerFunc _messageFunc, void *_context);


/*
    DESCRIPTION:    Sends _deta to _clientSock.
    
    INPUT:          _srvr - Pointer to server created in ServerCreate. Should not be NULL.
                    _clientSock - Client socket number to send to.
                    _data - The data to send. Sould not be NULL or empty.
    
    RETURN:         Value of SOCK_SUCCESS if sent.
    
    ERRORS:         SOCK_NOT_INITIALIZED if the server is not initialized.
                    SOCK_WRONG_INPUT if the input is flawed.
                    SOCK_FAIL if failed to send.
*/
sockError ServerSend(server *_srvr, int _clientSock, char *_data);


#endif
