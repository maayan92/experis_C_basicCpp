#ifndef __TCP_CLIENT__
#define __TCP_CLIENT__

#define PORT 1992
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
	Description: create the socket.
	Input: _sock - pointer to the created socket.
	Return value: return error, 
*/
int SocketCreate(int *_sock);

/*
	Description: create sockkadrr sin.
	Input: _address - address connection.
	Return value: return sockaddr sin. 
*/
struct sockaddr_in SinCreate(char *_address);

/*
	Description: set the connection with the server.
	Input: _sock - pointer to the created socket.
	Return value: return error, TODO
*/
int Connect(int _sock, struct sockaddr_in _sin);

/*
	Description: send a message to the server.
	Input: _sock - the socket.
	Return value: return error, 
*/
int SendDataTransfer(int _sock);

/*
	Description: reviece a message from the server.
	Input: _clientSock - the client socket, _buffer - message to be recieved from the client.
	Return value: return error, TODO
*/
int RecvDataTransfer(int _clientSock, char *_buffer);

/*
	Description: close the socket.
	Input: _sock - the socket to be close.
	Return value: nothing returns.
*/
void CloseSocket(int _sock);


#endif
