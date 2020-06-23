#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

#include "TCPserver.h"

#define SERVER_MAGIC_NUMBER 0xe1e1e1e1
#define SERVER_NO_MAGIC_NUMBER 0xe0e0e0e0

struct Server
{
	size_t m_magicNumber;
	int m_serverSock;
	List *m_clients;
	size_t m_numOfClients;
	fd_set m_temp;
	fd_set m_master;
};

/*set on the bit of the client's sockets*/
static int SetBitOn(void *_socket, void *_context);
/*create sockaddr sin*/
static struct sockaddr_in SinCreate(char *_address);
/*set the socket, bind and listen*/
static int SetBindListen(int *_sock, char *_address);
/*remove a socket from the list*/
static ListItr RemoveSocket(Server *_server, ListItr _itr);
/*close the socket*/
static void CloseSocket(void* _sock);


Server* ServerCreate()
{
	Server *server = (Server*)malloc(sizeof(Server));
	if(!server)
	{
		return NULL;
	}
	
	server->m_clients = DLListCreate();
	server->m_numOfClients = 0;

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

int SocketInitialization(Server *_server, char *_address)
{
	int err;
	
	if(!_server || !_address)
	{
		return ERR_NOT_INITIALIZE;
	}
	
	_server->m_serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > _server->m_serverSock)
	{
		return ERR_SOCK_FAILED;
	}
	
	if(ERR_SUCCESS != (err = SetBindListen(&_server->m_serverSock,_address)))
	{
		return err;
	}
	
	FD_SET(_server->m_serverSock,&_server->m_master);
	
	FD_ZERO(&_server->m_master);
	
	ListItrForEach(ListItrBegin(_server->m_clients),ListItrEnd(_server->m_clients),SetBitOn,&_server->m_master);
	
	return ERR_SUCCESS;
}

int SetAndWait(Server *_server)
{
	if(!_server)
	{
		return -1;
	}
	
	FD_SET(_server->m_serverSock,&_server->m_master);

	_server->m_temp = _server->m_master;
	
	return select(NUM_OF_SOCKETS,&_server->m_temp,NULL,NULL,NULL);
}

int SetConnection(Server *_server)
{
	struct sockaddr_in sin;
	socklen_t addr_len = sizeof(sin);
	int *clientSock;
	
	if(!_server)
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(!FD_ISSET(_server->m_serverSock,&_server->m_temp))
	{
		return ERR_NO_CONNECTION;
	}
	
	clientSock = (int*)malloc(sizeof(int));
	if(!clientSock)
	{
		return ERR_ALLOCATION_FAILED;
	}

	*clientSock = accept(_server->m_serverSock,(struct sockaddr *)&sin, &addr_len);
	
	if(MAX_CLIENTS <= _server->m_numOfClients)
	{
		CloseSocket(clientSock);
		return ERR_CLOSED_SOCK;
	}
	
	if (*clientSock < 0)
	{
		free(clientSock);
		return ERR_CONNECTION_FAILED;
	}
	
	DLListPushHead(_server->m_clients,clientSock);
	++_server->m_numOfClients;
	
	FD_SET(*clientSock,&_server->m_master);

	return ERR_SUCCESS;
}

int RecvDataTransfer(int _clientSock, char *_buffer)
{
	ssize_t read_bytes;
	
	if(!_buffer)
	{
		return ERR_NOT_INITIALIZE;
	}
	
	read_bytes = recv(_clientSock, _buffer, DATA_SIZE, 0);
	
	if(0 == read_bytes)
	{
		return ERR_CLOSED_SOCK;
	}
	
	if (0 > read_bytes) 
	{
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

void ServerListForEach(Server *_server, ListActionFunction _action, int _activity)
{
	ListItr begin, end;
	
	if(!_server)
	{
		return;
	}
	
	begin = ListItrBegin(_server->m_clients);
	end = ListItrEnd(_server->m_clients);
	
	while(!ListItrEquals(begin,end) && _activity)
	{
		if(FD_ISSET(*(int*)ListItrGet(begin),&_server->m_temp) && !_action(ListItrGet(begin),&_activity))
		{
			begin = RemoveSocket(_server,begin);
		}
		else
		{
			begin = ListItrNext(begin);
		}
	}
}

/* SUB FUNCTIONS */

static int SetBitOn(void *_socket, void *_context)
{
	FD_SET(*((int*)_socket),(fd_set*)_context);
	
	return 1;
}

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

static struct sockaddr_in SinCreate(char *_address)
{
	struct sockaddr_in sin;

	memset(&sin,0,sizeof(sin));
	
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(_address);
	sin.sin_port = htons(PORT);
	
	return sin;
}

static ListItr RemoveSocket(Server *_server, ListItr _itr)
{
	ListItr next = ListItrNext(_itr);
	int *clientSock = ListItrRemove(_itr);
	
	FD_CLR(*clientSock,&_server->m_master);
	CloseSocket(clientSock);
	
	--_server->m_numOfClients;
	
	return next;
}

static void CloseSocket(void* _sock)
{
	close(*(int*)_sock);
	free((int*)_sock);
}



