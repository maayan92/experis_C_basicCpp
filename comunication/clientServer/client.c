#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
	ssize_t sent_bytes, read_bytes;
	struct sockaddr_in sin;
	char buffer[4096], data[400] = "hello moran";
	socklen_t sin_len;
	
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(0 > sock)
	{
		perror("socket failed!!");
		abort();
	}
	
	memset(&sin,0,sizeof(sin));
	
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(1234);
	
	
	while(1)
	{
		sent_bytes = sendto(sock,&data,sizeof(data),0,(struct sockaddr *)&sin,sizeof(sin));

		if(0 > sent_bytes)
		{
			perror("sendto failed!!");
			abort();
		}
		
		read_bytes = recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&sin,&sin_len);
		
		if(0 > read_bytes)
		{
			perror("read failed!!");
			abort();
		}
		
		buffer[read_bytes] = '\0';
		printf("%s \n",buffer);
		
		printf("enter message: ");
		fgets(data,200,stdin);
	}
	
	close(sock);
	
	return 0;
}
