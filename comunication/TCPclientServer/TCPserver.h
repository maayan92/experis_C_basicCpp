#ifndef __TCP_SERVER__
#define __TCP_SERVER__

#define PORT 1234
#define DATA_SIZE 400

enum
{
	ERR_SUCCESS,
	ERR_SOCK_FAILED,
	ERR_SET_SOCK_FAILED,
	ERR_BIND_FAILED,
	ERR_LISTEN_FAILED,
	ERR_CONNECTION_FAILED,
	ERR_SEND_FAILED
};

/*
	Description: create the socket.
	Input: _sock - pointer to the created socket, _address - address connection.
	Return value: return error, 
*/
int SocketCreate(int *_sock, char *_address);

/*
	Description: set the connection with the client
	Input: _sock - pointer to the created socket.
	Return value: return error, TODO
*/
int SetConnection(int *_sock);

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
	Description: close the socket.
	Input: _sock - the socket to be close.
	Return value: nothing returns.
*/
void CloseSocket(int _sock);


#endif
