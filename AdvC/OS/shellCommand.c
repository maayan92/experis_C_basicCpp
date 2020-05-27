#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*get line command*/
static void read_command(char *command, char **paramaters)
{
	char *token;
	int i = 0;

	printf("insert command:");
	fgets(command,50,stdin);
	
	token = strtok(command," ");

	while(token)
	{
		paramaters[i++] = token;
		
		token = strtok(NULL," ");
	}
	
	paramaters[--i] = NULL;
	
	command = paramaters[0];
}


int main()
{
	char str[50], command[50], *paramaters[10];
	int status;

	while(1)
	{
		printf("rony prompt: ");
		fgets(str,50,stdin);
		
		read_command(command,paramaters);

		if(fork() != 0)
		{
			/*Parent code*/
			
			waitpid(-1,&status,0);
		}
		
		else
		{
			/*Child code*/	
			
			execvp(command,paramaters);
			
			printf("failed\n");
			exit(0);
		}
	}

	return 0;
}


