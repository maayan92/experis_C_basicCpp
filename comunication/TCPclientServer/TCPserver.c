#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include "TCPserver.h"

/*create sockaddr sin*/
static struct sockaddr_in SinCreate(char *_address);


int SocketCreate(int *_sock, char *_address)
{
	struct sockaddr_in sin;
	int back_log = 2, optval = 1;
	
	*_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > (*_sock))
	{
		return ERR_SOCK_FAILED;
	}
	
	if (setsockopt(*_sock, SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval)) < 0) {

		return ERR_SET_SOCK_FAILED;
	}
	
	sin = SinCreate(_address);
	
	if (bind(*_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {

		return ERR_BIND_FAILED;
	}
	
	if (listen(*_sock, back_log) < 0) {

		return ERR_LISTEN_FAILED;
	}
	
	return ERR_SUCCESS;
}

static struct sockaddr_in SinCreate(char *_address)
{
	struct sockaddr_in sin;

	memset(&sin,0,sizeof(sin));
	
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(_address);
	sin.sin_port = htons(PORT);
	
	return sin;
}

int SetConnection(int *_sock)
{
	struct sockaddr_in sin;
	socklen_t addr_len = sizeof(sin);

	*_sock = accept(*_sock,(struct sockaddr *)&sin, &addr_len);
	
	if ((*_sock) < 0) {

		return ERR_CONNECTION_FAILED;
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

int SendDataTransfer(int _clientSock)
{
	char data[DATA_SIZE];
	ssize_t sent_bytes;
	
	printf("enter message: ");
	fgets(data,200,stdin);

	sent_bytes = send(_clientSock, data, strlen(data), 0);
	
	if (sent_bytes < 0) {
		
		return ERR_SEND_FAILED;
	}
	
	return ERR_SUCCESS;
}

void CloseSocket(int _sock)
{
	close(_sock);
}





