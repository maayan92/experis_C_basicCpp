#include <stdio.h>
#include <stdlib.h>    /*for create new terminal (system call)*/
#include <string.h>
#define BUFFER 400
#define IP_LEN 20


void OpenTerminal(char* file,char* position,char* beginning,char* out, char* ip, char* port,char* fileName,char* userName,char* groupName);
/*			1		 2		3 	 4		5		 6		*/
/*argc: GroupName,position,Ip, Port, UserName,FileName, */

int main(int argc,char* argv[])
{
    char file[BUFFER];
    char fileName[] = "file.txt";
    char userName[] = "ron";
    char groupName[] = "h64";
    char beginningBig[] = "gnome-terminal command  --geometry=40x20";
    char beginningSmall[] = "gnome-terminal command  --geometry=40x10";
    char positionBig[] ="+40+100 ";
	char positionSmall[] ="+40+500 ";
	char read[] = " -- bash -c \"./chatRead.out ";
    char write[] = " -- bash -c \"./chatWrite.out ";
    char ip[IP_LEN];
    char port[5];
    if(argc!= 3)
    {
    	return 0;
    }
  	strcpy(ip,argv[1]);
  	strcpy(port,argv[2]);
  	
    OpenTerminal(file,positionBig,beginningBig,read,ip,port,fileName,userName,groupName);
    
    OpenTerminal(file,positionSmall,beginningSmall,write,ip,port,fileName,userName,groupName);
  	
	return 0;
}

void OpenTerminal(char* file,char* position,char* beginning,char* out, char* ip, char* port,char* fileName,char* userName,char* groupName)
{
	strcpy(file,beginning);
	strcat(file,position);
	strcat(file,out);
	strcat(file,ip);
	strcat(file," ");
	strcat(file,port);
	strcat(file," ");
	strcat(file,fileName); 
	strcat(file," ");
	strcat(file,userName);
	strcat(file," ");
	strcat(file,groupName);
	strcat(file,"\"");
	printf("%s\n\n",file);
	
    system(file);	
}


