#ifndef _GNU_SOURCE  
#define _GNU_SOURCE /*for ip_mreq structure - for multicast mode*/
#endif
#include <stdio.h>
#include <stdlib.h> /* strtol(), exit() */
#include <string.h>  /* for memset() */
#include <stdbool.h> /*for return value of openning file*/     
#include <sys/socket.h> /* =for socklen_t type*/
#include <arpa/inet.h> /*for in_addr structure and inet_ntoa*/
#include <unistd.h> /*for pid*/
#define MAX_LEN 100 /*maximum chars in a message.*/


static bool OpenNewFile(char *_fileName);
static void PrepareMulticastCommunication(struct ip_mreq* _mreq,struct sockaddr_in* _sin,int* _read_bytes);
static void StartCommunication(int _read_bytes, char *_userName, char *_groupName); 

int main(int argc,char* argv[])
{
    int read_bytes, intval = 1;
    struct ip_mreq mreq;
    struct sockaddr_in sin;
    if (argc != 6) 
    {
         perror("Error: must get ip and port number");
         return -1;
    }
    if(!OpenNewFile(argv[3])) /*insert pid into file*/
    {
    	return -1;
    }
    memset(&sin, 0, sizeof(sin)); /*InitSocket*/
    sin.sin_family = AF_INET;
    sin.sin_port = htons((unsigned short int)strtol(argv[2], NULL, 0));
    sin.sin_addr.s_addr = inet_addr(argv[1]);
  
    if((read_bytes = socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
		perror ("socket failed");
		abort();
    }
    if (setsockopt(read_bytes,SOL_SOCKET,SO_REUSEADDR,&intval,sizeof(intval))<0)
    {
        perror("reuseaddr setsockopt");
        exit(1);
    }
    if (bind(read_bytes, (struct sockaddr *) &sin, sizeof(sin)) < 0) 
    {
        perror("bind failed");
        abort();
    }
    PrepareMulticastCommunication(&mreq,&sin,&read_bytes); /* Preparatios for using Multicast */
	StartCommunication(read_bytes, argv[4], argv[5]);
    return 0;
}

/*------------------------------ static functions ------------------------------ */ 

static void StartCommunication(int _read_bytes, char *_userName, char *_groupName)
{
	struct sockaddr_in client_sock;
	int recieveMessage,len;
	char message [MAX_LEN+1];
	
	printf("Welcome to %s\n",_groupName);
	while(1)
	{
		len=sizeof(client_sock);
        recieveMessage=recvfrom(_read_bytes, message, MAX_LEN, 0,(struct sockaddr*)&client_sock, (socklen_t *)&len);
        if(recieveMessage < 0)
        {
            perror ("recv");
            exit(1);
        }
        message[recieveMessage] = '\0'; /* null-terminate string */
        printf("%s \n", message);
	}
}


static void PrepareMulticastCommunication(struct ip_mreq* _mreq,struct sockaddr_in* _sin,int* _read_bytes)
{
	_mreq->imr_multiaddr = _sin->sin_addr;
	_mreq->imr_interface.s_addr = htonl(INADDR_ANY);
	
	 /*Tell the kernel we want to join that multicast group. */
	if (setsockopt(*_read_bytes, IPPROTO_IP, IP_ADD_MEMBERSHIP, _mreq, sizeof(*_mreq)) < 0)  
	{
		perror ("add_membership setsockopt");
		exit(1);
	}
}

static bool OpenNewFile(char *_fileName)
{
	FILE* fp;
	if((fp = fopen(_fileName, "w")) == NULL)
	{
		perror("unable to open file");
		return false;
	}
	fprintf(fp,"%d\n",getpid());

	fclose(fp);
	return true;
}


