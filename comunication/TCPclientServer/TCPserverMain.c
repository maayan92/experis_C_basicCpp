#include <stdio.h>
#include "TCPserver.h"


int main()
{
	int sock;
	char buffer[DATA_SIZE];
	
	if(ERR_SUCCESS != SocketCreate(&sock,"192.168.0.101"))
	{
		printf("socket failed\n");
	}
	
	if(ERR_CONNECTION_FAILED == SetConnection(&sock))
	{
		printf("connection failed\n");
	}
	
	while(1)
	{
		if(ERR_SEND_FAILED == RecvDataTransfer(sock,buffer))
		{
			printf("data recv failed\n");
		}
		
		printf("%s \n", buffer);
		
		if(ERR_SEND_FAILED == SendDataTransfer(sock))
		{
			printf("data send failed\n");
		}
	}
	
	CloseSocket(sock);
	
	return 0;
}
