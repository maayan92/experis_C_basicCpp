#ifndef __TCP_CLIENT__
#define __TCP_CLIENT__

<<<<<<< HEAD
#define PORT 1234
=======
#define PORT 5678
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
#define DATA_SIZE 400

enum
{
	ERR_SUCCESS,
	ERR_SOCK_FAILED,
	ERR_SET_SOCK_FAILED,
	ERR_CONNECTION_FAILED,
	ERR_SEND_FAILED
};

/*
	Description: create the socket, and initialize the socket.
	Input: _sock - pointer to the created socket.
<<<<<<< HEAD
	Return value: return error, TODO
=======
	Return value: return error, ERR_SOCK_FAILED - if the socket creation failed, ERR_SUCCESS - on success.
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
*/
int SocketInitialization(int *_sock, struct sockaddr_in *_sin, char *_address);

/*
	Description: set the connection with the server.
	Input: _sock - pointer to the created socket.
<<<<<<< HEAD
	Return value: return error, TODO
=======
	Return value: return error, ERR_CONNECTION_FAILED - if connection fails, ERR_SUCCESS - on success.
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
*/
int Connect(int _sock, struct sockaddr_in _sin);

/*
	Description: send a message to the server.
	Input: _sock - the socket.
<<<<<<< HEAD
	Return value: return error, 
=======
	Return value: return error, ERR_SEND_FAILED - if the socket failed to send data to the server, ERR_SUCCESS - on success.
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
*/
int SendDataTransfer(int _sock);

/*
	Description: reviece a message from the server.
	Input: _clientSock - the client socket, _buffer - message to be recieved from the client.
<<<<<<< HEAD
	Return value: return error, TODO
=======
	Return value: return error, ERR_SEND_FAILED - if the socket failed to recieve data from the server, ERR_SUCCESS - on success.
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
*/
int RecvDataTransfer(int _clientSock, char *_buffer);

/*
	Description: close the socket.
	Input: _sock - the socket to be close.
	Return value: nothing returns.
*/
void CloseSocket(int _sock);


#endif
