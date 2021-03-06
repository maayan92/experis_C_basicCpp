#ifndef __TCP_SERVER__
#define __TCP_SERVER__

#include "listFunctions.h"

#define PORT 1234
#define DATA_SIZE 400
<<<<<<< HEAD
#define CLIENTS_SIZE 5
=======
#define CLIENTS_SIZE 500
#define MAX_CLIENTS 1000
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6

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

<<<<<<< HEAD
Server* ServerCreate();

=======
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
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
void ServerDestroy(Server *_server);

/*
	Description: create the socket, and initialize the socket.
	Input: _sock - pointer to the created socket, _address - address connection.
<<<<<<< HEAD
	Return value: return error, 
=======
	Return value: return error, ERR_SOCK_FAILED - if socket failed to create, ERR_SET_SOCK_FAILED - if set socket opt failed,
								ERR_BIND_FAILED - if socket bind failed, ERR_LISTEN_FAILED - if socket listen failed,
								ERR_F_GETFL_FAILED - if set socket as non block get failed,
								ERR_NON_BLOCK_FAILED - if set socket as non block failed, ERR_SUCCESS - on success.
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
*/
int SocketInitialization(Server *_server, char *_address);

/*
	Description: set the connection with the client
	Input: _sock - pointer to the created socket.
<<<<<<< HEAD
	Return value: return error, TODO
=======
	Return value: return error, ERR_CLOSED_SOCK - if there is no place for another client, the socket close,
								ERR_NO_BLOCKING - if the socket failed to connect and the server is non-blocked,
								ERR_CONNECTION_FAILED - if the socket failed to connect, ERR_SUCCESS - on success.
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
*/
int SetConnection(Server *_server);

/*
	Description: recieve a message from the client.
	Input: _clientSock - the client socket, _buffer - message to be recieved from the client.
<<<<<<< HEAD
	Return value: return error, TODO
=======
	Return value: return error, ERR_CLOSED_SOCK - if the socket hes closed from the client's side,
								ERR_NO_BLOCKING - if the server failed to recieve data from the client and the client is non-blocked,
								ERR_SEND_FAILED - if the server failed to recieve data from the client, ERR_SUCCESS - on success.
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
*/
int RecvDataTransfer(int _clientSock, char *_buffer);

/*
	Description: send a message back to the client.
	Input: _clientSock - the client socket.
<<<<<<< HEAD
	Return value: return error, 
=======
	Return value: return error, ERR_SEND_FAILED - if send data back to the client failed, ERR_SUCCESS - on success.
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
*/
int SendDataTransfer(int _client_sock);

/*
	Description: do the _action function on all the server's clients.
	Input: _server - pointer to the server, _action - the action function.
	Return value: nothing returns.
*/
void ServerListForEach(Server *_server, ListActionFunction _action);


#endif
