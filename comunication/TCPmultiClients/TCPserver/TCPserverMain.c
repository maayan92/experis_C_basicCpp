#include <stdio.h>
#include <unistd.h>
#include "TCPserver.h"

static int RecvAndSend(void *_clientSock, void *_context)
{
<<<<<<< HEAD
=======
	static int num = 1;
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
	char buffer[DATA_SIZE];
	int err = RecvDataTransfer(*((int*)_clientSock),buffer);

	if(ERR_SEND_FAILED == err || ERR_CLOSED_SOCK == err)
	{
		return 0;
	}
	
	if(ERR_NO_BLOCKING == err)
	{
		return 1;
	}
			
<<<<<<< HEAD
	printf("%s \n", buffer);
			
	if(ERR_SEND_FAILED == SendDataTransfer(*((int*)_clientSock)))
	{
		printf("data send failed\n");
=======
	printf("%d : client num: %d %s \n", num++, *((int*)_clientSock), buffer);
			
	if(ERR_SEND_FAILED == SendDataTransfer(*((int*)_clientSock)))
	{
		printf("send data to client failed\n");
>>>>>>> c3597023196d98124e148dd66712061cc5dc72d6
	}
	
	return 1;
}

static void CommunicateWithClients(Server *_server)
{
	while(1)
	{
		if(ERR_CONNECTION_FAILED == SetConnection(_server))
		{
			return;
		}
		
		ServerListForEach(_server,RecvAndSend);
	}
}

int main()
{
	Server *server = ServerCreate();
	
	if(ERR_SUCCESS != SocketInitialization(server,"127.0.0.1"))
	{
		printf("socket failed\n");
		return 0;
	}

	CommunicateWithClients(server);

	ServerDestroy(server);
	
	return 0;
}





