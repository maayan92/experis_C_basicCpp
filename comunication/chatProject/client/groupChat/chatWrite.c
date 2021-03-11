#include <stdio.h>
#include <stdlib.h> /* for strtol(), exit() */
#include <string.h> /*for memset() */
#include <stdbool.h> /*for return value of openning file*/
#include <arpa/inet.h> /*for in_addr structure*/
#include <unistd.h> /*for pid*/
#define MAX_LEN 100 /*maximum chars in a message.*/



static bool OpenNewFile(char *_fileName);

int main(int argc,char* argv[])
{
    int sent_bytes,sock;
    struct sockaddr_in sin;
    char str[MAX_LEN];
    char buffer[MAX_LEN];
    
	if (argc != 6) 
	{
         perror( "Error: must get ip and port number");
         return -1;
    }
    if((sock = socket (AF_INET,SOCK_DGRAM,0))<0)
    {
		perror("socket failed");
    }
	if(!OpenNewFile(argv[3]))  /*insert pid of 'chatWrite' into file*/
	{
		return -1;
	}
	
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(argv[1]);
    sin.sin_port = htons((unsigned short int)strtol(argv[2], NULL, 0));
    strcpy(buffer,argv[4]);
    strcat(buffer," has joined the group!\n");
     
    sent_bytes = sendto(sock,(const char*)buffer,strlen(buffer),0,(struct sockaddr *)&sin,sizeof(sin));
    while(1)
    {
    	printf("Write your message for %s here:\n",argv[5]);
        fgets(str, MAX_LEN,stdin);
        system("clear");
        strcpy(buffer,argv[4]);
        strcat(buffer,":\n");
        strcat(buffer,str);
        sent_bytes = sendto(sock,(const char*)buffer,strlen(buffer),0,(struct sockaddr *)&sin,sizeof(sin));
        if(sent_bytes<0)
        {
			perror("sentdo failed");
        }
    }
    return 0;
}

/*------------------------------ static functions ------------------------------ */ 

static bool OpenNewFile(char *_fileName)
{
	 FILE* fp;
	if((fp = fopen(_fileName, "a")) == NULL)
    {
        perror("unable to open file");
        return false;
    }
    fprintf(fp,"%d\n",getpid());

    fclose(fp);
    return true;
}
