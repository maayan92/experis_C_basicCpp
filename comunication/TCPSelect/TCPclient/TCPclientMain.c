#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include "TCPclient.h"

#define SIZE 1000
#define STATISTIC 100

static int InitAndConnect()
{
	int sock;
	struct sockaddr_in sin;
	
	if(ERR_SUCCESS != SocketInitialization(&sock,&sin,"192.168.0.57"))
	{
		printf("socket failed!\n");
		return -1;
	}

	if(ERR_CONNECTION_FAILED == Connect(sock,sin))
	{
		printf("connection failed!\n");
		return -1;
	}
	
	return sock;
}

static void SendAndRecv(int _sock)
{
	static int num = 1;
	char buffer[DATA_SIZE];
	
	if(ERR_SEND_FAILED == SendDataTransfer(_sock))
	{
		printf("data send failed!\n");
		return;
	}
		
	if(ERR_SEND_FAILED == RecvDataTransfer(_sock,buffer))
	{
		printf("data recv failed\n");
		return;
	}
		
	printf("%d : %s \n", num++, buffer);
}	

int main()
{
	int randNum, clients[SIZE] = {0}, i = 0;
	time_t t;
	
	srand((unsigned)time(&t));
	
	while(1)
	{
		randNum = rand()%STATISTIC;
		
		if(0 == clients[i])
		{
			if(randNum < (0.3*STATISTIC))
			{
				if(-1 == (clients[i] = InitAndConnect()))
				{
					clients[i] = 0;
				}
			}
		}
		else
		{
			if(randNum < (0.05*STATISTIC))
			{
				CloseSocket(clients[i]);
				clients[i] = 0;
			}
			
			else if(randNum < (0.3*STATISTIC))
			{
				SendAndRecv(clients[i]);
			}
		}
		
		i = (i + 1) % SIZE;
	}

	return 0;
}





