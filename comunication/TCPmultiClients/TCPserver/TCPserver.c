#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "TCPserver.h"

#define SERVER_MAGIC_NUMBER 0xe1e1e1e1
#define SERVER_NO_MAGIC_NUMBER 0xe0e0e0e0

struct Server
{
	size_t m_magicNumber;
	int m_serverSock;
	List *m_clients;
};

/*create sockaddr sin*/
static struct sockaddr_in SinCreate(char *_address);
/**/
static int SetBindListen(int *_sock, char *_address);
/*set the socket as non blocking.*/
static int SetAsNonBlock(int *_sock);
/*close the socket.*/
void CloseSocket(void* _sock);


Server* ServerCreate()
{
	Server *server = (Server*)malloc(sizeof(Server));
	if(!server)
	{
		return NULL;
	}
	
	server->m_clients = DLListCreate();
	server->m_magicNumber = SERVER_MAGIC_NUMBER;
	
	return server;
}

void ServerDestroy(Server *_server)
{
	if(!_server || SERVER_MAGIC_NUMBER != _server->m_magicNumber)
	{
		return;
	}
	
	_server->m_magicNumber = SERVER_NO_MAGIC_NUMBER;
	
	DLListDestroy(_server->m_clients,CloseSocket);
	CloseSocket(&_server->m_serverSock);
	
	free(_server);
	
}

void CloseSocket(void* _sock)
{
	close(*(int*)_sock);
	free((int*)_sock);
}

int SocketInitialization(Server *_server, char *_address)
{
	int err;
	
	_server->m_serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > _server->m_serverSock)
	{
		return ERR_SOCK_FAILED;
	}
	
	if(ERR_SUCCESS != (err = SetBindListen(&_server->m_serverSock,_address)))
	{
		return err;
	}
	
	if(ERR_SUCCESS != (err = SetAsNonBlock(&_server->m_serverSock)))
	{
		return err;
	}
	
	return ERR_SUCCESS;
}

int SetConnection(Server *_server)
{
	struct sockaddr_in sin;
	socklen_t addr_len = sizeof(sin);
	int *clientSock = (int*)malloc(sizeof(int));

	*clientSock = accept(_server->m_serverSock,(struct sockaddr *)&sin, &addr_len);
	
	if (*clientSock < 0)
	{
		free(clientSock);
		
		if(EAGAIN == errno || EWOULDBLOCK == errno)
		{
			return ERR_NO_BLOCKING;
		}
		
		return ERR_CONNECTION_FAILED;
	}
	
	SetAsNonBlock(clientSock);
	DLListPushHead(_server->m_clients,clientSock);
	
	return ERR_SUCCESS;
}

int RecvDataTransfer(int _clientSock, char *_buffer)
{
	ssize_t read_bytes;
	
	read_bytes = recv(_clientSock, _buffer, DATA_SIZE, 0);
	
	if(0 == read_bytes)
	{
		return ERR_CLOSED_SOCK;
	}
	
	if (0 > read_bytes) 
	{
		if(EAGAIN == errno || EWOULDBLOCK == errno)
		{
			return ERR_NO_BLOCKING;
		}
		
		return ERR_SEND_FAILED;
	}
		
	_buffer[read_bytes] = '\0';
	
	return ERR_SUCCESS;
}

int SendDataTransfer(int _clientSock)
{
	char data[DATA_SIZE] = "message received";
	ssize_t sent_bytes;

	sent_bytes = send(_clientSock, data, strlen(data), 0);
	
	if (sent_bytes < 0) 
	{
		return ERR_SEND_FAILED;
	}
	
	return ERR_SUCCESS;
}

void ServerListForEach(Server *_server, ListActionFunction _action)
{
	ListItr itr = ListItrBegin(_server->m_clients), removeItr;
	int *clientSock;
	
	while(!ListItrEquals(itr,ListItrEnd(_server->m_clients)))
	{
		itr = ListItrForEach(itr,ListItrEnd(_server->m_clients),_action,NULL);
		
		if(!ListItrEquals(itr,ListItrEnd(_server->m_clients)))
		{
			removeItr = itr;
			itr = ListItrNext(itr);
			
			clientSock = ListItrRemove(removeItr);
			CloseSocket(clientSock);
		}
	}
}


/**/

static int SetBindListen(int *_sock, char *_address)
{
	struct sockaddr_in sin;
	int optval = 1;
	
	if (setsockopt(*_sock, SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval)) < 0) 
	{
		return ERR_SET_SOCK_FAILED;
	}
	
	sin = SinCreate(_address);
	
	if (bind(*_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) 
	{
		return ERR_BIND_FAILED;
	}
	
	if (listen(*_sock, CLIENTS_SIZE) < 0) 
	{
		return ERR_LISTEN_FAILED;
	}
	
	return ERR_SUCCESS;
}

static int SetAsNonBlock(int *_sock)
{
	int flags;

	if (-1 == (flags = fcntl(*_sock, F_GETFL)))
	{
		return ERR_F_GETFL_FAILED;
	}

	if(-1 == fcntl(*_sock, F_SETFL, flags | O_NONBLOCK))
	{
		return ERR_NON_BLOCK_FAILED;
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



