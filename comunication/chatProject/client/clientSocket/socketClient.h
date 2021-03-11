#ifndef __SOCKETCLIENT_H__
#define __SOCKETCLIENT_H__

#include <stdio.h>  /* for size_t */


typedef struct client client;

typedef enum
{
    SOCK_SUCCESS,
    SOCK_FAIL,
    SOCK_NOT_INITIALIZED,
    SOCK_WRONG_INPUT,
    SOCK_CLOSED
}sockError;


/*
    DESCRIPTION:    Creates client.
    
    INPUT:          _address - String of the adress to connect with. Should not be NULL.
                    _port - Port to use.
    
    RETURN:         Pointer to client created.
    
    ERRORS:         If failed returns NULL.
*/
client* ClientCreate(char *_address, int _port);


/*
    DESCRIPTION:    Destroys the client.
    
    INPUT:          _clnt - Pointer to client created in ClientCreate. Should not be NULL.
*/
void ClientDestroy(client *_clnt);


/*
    DESCRIPTION:    Opens the socket.
    
    INPUT:          _clnt - Pointer to client created in ClientCreate. Should not be NULL.
    
    RETURN:         Value of SOCK_SUCCESS if successfull.
    
    ERRORS:         SOCK_NOT_INITIALIZED if _clnt is not initialized.
                    SOCK_FAIL if failed.
*/
sockError ClientOpenSock(client *_clnt);


/*
    DESCRIPTION:    Creates connection request. If errored closes the socket.
    
    INPUT:          _clnt - Pointer to client created in ClientCreate. Should not be NULL.
    
    RETURN:         Value of SOCK_SUCCESS if successfull.
    
    ERRORS:         SOCK_NOT_INITIALIZED if _clnt is not initialized.
                    SOCK_FAIL if failed
*/
sockError ClientConnect(client *_clnt);


/*
    DESCRIPTION:    Sends _data. If errored closes the socket.
    
    INPUT:          _clnt - Pointer to client created in ClientCreate. Should not be NULL.
                    _data - Data to send. Should not be NULL.
    
    RETURN:         Value of SOCK_SUCCESS if successfull.
    
    ERRORS:         SOCK_NOT_INITIALIZED if _clnt is not initialized.
                    SOCK_WRONG_INPUT if data is NULL or empty;
                    SOCK_FAIL if failed
*/
sockError ClientSend(client *_clnt, char *_data);


/*
    DESCRIPTION:    Receives data. If errored closes the socket.
    
    INPUT:          _clnt - Pointer to client created in ClientCreate. Should not be NULL.
                    _buffer - Buffer to receive data. Should not be NULL.
                    _bufferSize - Size of _buffer.
    
    RETURN:         Value of SOCK_SUCCESS if successfull.
    
    ERRORS:         SOCK_NOT_INITIALIZED if _clnt is not initialized.
                    SOCK_WRONG_INPUT if _buffer is NULL or if _bufferSize is smaller than 1.
                    SOCK_CLOSED if the socket is closed.
                    SOCK_FAIL if failed
*/
sockError ClientReceive(client *_clnt, char *_buffer, size_t _bufferSize);


#endif
