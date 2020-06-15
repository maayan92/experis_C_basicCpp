#include <stdio.h>
#include <arpa/inet.h>
#include "TCPclient.h"


int main()
{
	int sock;
	struct sockaddr_in sin;
	char buffer[DATA_SIZE];
	
	if(ERR_SUCCESS != SocketCreate(&sock))
	{
		printf("socket failed!\n");
	}

	sin = SinCreate("192.168.0.99");
	
	if(ERR_CONNECTION_FAILED == Connect(sock,sin))
	{
		printf("connection failed!\n");
	}
	
	while(1)
	{
		if(ERR_SEND_FAILED == SendDataTransfer(sock))
		{
			printf("data send failed!\n");
		}
		
		if(ERR_SEND_FAILED == RecvDataTransfer(sock,buffer))
		{
			printf("data recv failed\n");
		}
		
		printf("%s \n", buffer);
	}
	
	CloseSocket(sock);
	
	return 0;
}
