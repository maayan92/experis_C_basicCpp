#ifndef __TCP_CLIENT__
#define __TCP_CLIENT__

#define PORT 1234
#define DATA_SIZE 400

enum
{
	ERR_SUCCESS,
	ERR_SOCK_FAILED,
	ERR_SET_SOCK_FAILED,
	ERR_CONNECTION_FAILED,
	ERR_SEND_FAILED,
	ERR_CLOSED_SOCK
};

/*
	Description: create the socket, and initialize the socket.
	Input: _sock - pointer to the created socket.
	Return value: return error, ERR_SOCK_FAILED - if the socket creation failed, ERR_SUCCESS - on success.
*/
int SocketInitialization(int *_sock, struct sockaddr_in *_sin, char *_address);

/*
	Description: set the connection with the server.
	Input: _sock - pointer to the created socket.
	Return value: return error, ERR_CONNECTION_FAILED - if connection fails, ERR_SUCCESS - on success.
*/
int Connect(int _sock, struct sockaddr_in _sin);

/*
	Description: send a message to the server.
	Input: _sock - the socket.
	Return value: return error, ERR_SEND_FAILED - if the socket failed to send data to the server, ERR_SUCCESS - on success.
*/
int SendDataTransfer(int _sock);

/*
	Description: reviece a message from the server.
	Input: _clientSock - the client socket, _buffer - message to be recieved from the client.
	Return value: return error, ERR_SEND_FAILED - if the socket failed to recieve data from the server, 
					ERR_CLOSED_SOCK - if the client has closed from the server, ERR_SUCCESS - on success.
*/
int RecvDataTransfer(int _clientSock, char *_buffer);

/*
	Description: close the socket.
	Input: _sock - the socket to be close.
	Return value: nothing returns.
*/
void CloseSocket(int _sock);


#endif
