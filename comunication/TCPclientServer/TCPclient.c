#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include "TCPclient.h"


int SocketCreate(int *_sock)
{
	*_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > (*_sock))
	{
		return ERR_SOCK_FAILED;
	}
	
	return ERR_SUCCESS;
}

struct sockaddr_in SinCreate(char *_address)
{
	struct sockaddr_in sin;
	
	memset(&sin,0,sizeof(sin));
	
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(_address);
	sin.sin_port = htons(PORT);
	
	return sin;
}

int Connect(int _sock, struct sockaddr_in _sin)
{

	if (connect(_sock, (struct sockaddr *) &_sin, sizeof(_sin)) < 0) {

		return ERR_CONNECTION_FAILED;
	}
	
	return ERR_SUCCESS;
}

int SendDataTransfer(int _sock)
{
	char data[DATA_SIZE];
	ssize_t sent_bytes;
	
	printf("enter message: ");
	fgets(data,200,stdin);
	
	sent_bytes = send(_sock, data, strlen(data), 0);
	
	if (sent_bytes < 0)
	{
		return ERR_SEND_FAILED;
	}
	
	return ERR_SUCCESS;
}

int RecvDataTransfer(int _clientSock, char *_buffer)
{
	ssize_t read_bytes;
	
	read_bytes = recv(_clientSock, _buffer, DATA_SIZE, 0);
	
	if (read_bytes < 0) {

		return ERR_SEND_FAILED;
	}
		
	_buffer[read_bytes] = '\0';
	
	return ERR_SUCCESS;
}

void CloseSocket(int _sock)
{
	close(_sock);
}










