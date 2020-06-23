#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "TCPserver.h"

static int RecvAndSend(void *_clientSock, void *_context)
{
	static int num = 1;
	char buffer[DATA_SIZE];
	int err = RecvDataTransfer(*((int*)_clientSock),buffer);
	
	--*((int*)_context);

	if(ERR_SEND_FAILED == err || ERR_CLOSED_SOCK == err)
	{
		return 0;
	}
			
	printf("%d : client num: %d %s \n", num++, *((int*)_clientSock), buffer);
			
	if(ERR_SEND_FAILED == SendDataTransfer(*((int*)_clientSock)))
	{
		perror("send data to client failed");
	}
	
	return 1;
}

static void CommunicateWithClients(Server *_server)
{
	int activity, err;
	
	while(1)
	{
		activity = SetAndWait(_server);
		
		if(0 < activity)
		{
			err = SetConnection(_server);
			
			if(ERR_SUCCESS == err || ERR_CLOSED_SOCK == err)
			{
				--activity;
			}
		}
		
		if(0 < activity)
		{
			ServerListForEach(_server,RecvAndSend,activity);
		}
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





