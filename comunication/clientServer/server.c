#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
	ssize_t read_bytes, sent_bytes;
	struct sockaddr_in sin;
	char buffer[4096], data[] = "recived message!";
	socklen_t sin_len = sizeof(sin);
	
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

	if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {

		perror("bind failed");
		abort();
	}
	
	read_bytes = recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&sin,&sin_len);
	
	if(0 > read_bytes)
	{
		perror("read failed!!");
		abort();
	}
	
	printf("%s \n",buffer);
	
	sent_bytes = sendto(sock,&data,sizeof(data),0,(struct sockaddr *)&sin,sizeof(sin));
	
	if(0 > sent_bytes)
	{
		perror("sento failed!!");
		abort();
	}
	
	close(sock);
	
	return 0;
}



