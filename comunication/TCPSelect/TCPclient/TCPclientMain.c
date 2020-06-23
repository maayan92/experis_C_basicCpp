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
	
	if(ERR_SUCCESS != SocketInitialization(&sock,&sin,"127.0.0.1"))
	{
		perror("socket failed!");
		return -1;
	}

	if(ERR_CONNECTION_FAILED == Connect(sock,sin))
	{
		perror("connection failed!");
		return -1;
	}
	
	return sock;
}

static int SendAndRecv(int *_sock)
{
	static int num = 1, dataSR;
	char buffer[DATA_SIZE];
	
	dataSR = SendDataTransfer(*_sock);
	
	if(ERR_SEND_FAILED == dataSR)
	{
		perror("data send failed!");
		return 0;
	}
	
	if(ERR_CLOSED_SOCK == dataSR)
	{
		return -1;
	}
		
	dataSR = RecvDataTransfer(*_sock,buffer);
	
	if(ERR_CLOSED_SOCK == dataSR)
	{
		return -1;
	}
	
	if(ERR_SEND_FAILED == dataSR)
	{
		perror("data recv failed");
		return 0;
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
				if(-1 == SendAndRecv(&clients[i]))
				{
					CloseSocket(clients[i]);
					clients[i] = 0;
				}
			}
		}
		
		i = (i + 1) % SIZE;
	}

	return 0;
}





