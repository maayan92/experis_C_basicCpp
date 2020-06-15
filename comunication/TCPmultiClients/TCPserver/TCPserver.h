#ifndef __TCP_SERVER__
#define __TCP_SERVER__

#include "listFunctions.h"

#define PORT 1234
#define DATA_SIZE 400
#define CLIENTS_SIZE 5

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
	ERR_NON_BLOCK_FAILED,
	ERR_F_GETFL_FAILED,
	ERR_NO_BLOCKING,
	ERR_CLOSED_SOCK
};

Server* ServerCreate();

void ServerDestroy(Server *_server);

/*
	Description: create the socket, and initialize the socket.
	Input: _sock - pointer to the created socket, _address - address connection.
	Return value: return error, 
*/
int SocketInitialization(Server *_server, char *_address);

/*
	Description: set the connection with the client
	Input: _sock - pointer to the created socket.
	Return value: return error, TODO
*/
int SetConnection(Server *_server);

/*
	Description: recieve a message from the client.
	Input: _clientSock - the client socket, _buffer - message to be recieved from the client.
	Return value: return error, TODO
*/
int RecvDataTransfer(int _clientSock, char *_buffer);

/*
	Description: send a message back to the client.
	Input: _clientSock - the client socket.
	Return value: return error, 
*/
int SendDataTransfer(int _client_sock);

/*
	Description: do the _action function on all the server's clients.
	Input: _server - pointer to the server, _action - the action function.
	Return value: nothing returns.
*/
void ServerListForEach(Server *_server, ListActionFunction _action);


#endif
