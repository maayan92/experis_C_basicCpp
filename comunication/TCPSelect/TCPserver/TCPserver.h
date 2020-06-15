#ifndef __TCP_SERVER__
#define __TCP_SERVER__

#include "listFunctions.h"

#define PORT 1234
#define DATA_SIZE 400
#define CLIENTS_SIZE 100
#define MAX_CLIENTS 1000
#define NUM_OF_SOCKETS 1024

typedef struct Server Server;

enum
{
	ERR_SUCCESS,
	ERR_SOCK_FAILED,
	ERR_SET_SOCK_FAILED,
	ERR_BIND_FAILED,
	ERR_LISTEN_FAILED,
	ERR_CONNECTION_FAILED,
	ERR_SEND_FAILED,
	ERR_CLOSED_SOCK,
	ERR_NO_CONNECTION
};

/*
	Description: create new server.
	Input: 
	Return value: return pointer to the server.
*/
Server* ServerCreate();

/*
	Description: destroy the server.
	Input: _server - server to destroy.
	Return value: nothing returns.
*/
void ServerDestroy(Server *_server);

/*
	Description: create the socket, and initialize the socket.
	Input: _sock - pointer to the created socket, _address - address connection.
	Return value: return error, ERR_SOCK_FAILED - if socket failed to create, ERR_SET_SOCK_FAILED - if set socket opt failed,
								ERR_BIND_FAILED - if socket bind failed, ERR_LISTEN_FAILED - if socket listen failed,
								ERR_SUCCESS - on success.
*/
int SocketInitialization(Server *_server, char *_address);

/*
	Description: set the socket's bit and wait for activity.
	Input: _server - pointer to the server.
	Return value: return the number of activity sockets, or -1 if _server isn't exist.
*/
int SetAndWait(Server *_server);

/*
	Description: set the connection with the client
	Input: _sock - pointer to the created socket.
	Return value: return error, ERR_CLOSED_SOCK - if there is no place for another client, the socket close,
								ERR_CONNECTION_FAILED - if the socket failed to connect, ERR_SUCCESS - on success.
*/
int SetConnection(Server *_server);

/*
	Description: recieve a message from the client.
	Input: _clientSock - the client socket, _buffer - message to be recieved from the client.
	Return value: return error, ERR_CLOSED_SOCK - if the socket hes closed from the client's side,
								ERR_SEND_FAILED - if the server failed to recieve data from the client, ERR_SUCCESS - on success.
*/
int RecvDataTransfer(int _clientSock, char *_buffer);

/*
	Description: send a message back to the client.
	Input: _clientSock - the client socket.
	Return value: return error, ERR_SEND_FAILED - if send data back to the client failed, ERR_SUCCESS - on success.
*/
int SendDataTransfer(int _client_sock);

/*
	Description: do the _action function on all the server's clients.
	Input: _server - pointer to the server, _action - the action function.
	Return value: nothing returns.
*/
void ServerListForEach(Server *_server, ListActionFunction _action, int _activity);


#endif
