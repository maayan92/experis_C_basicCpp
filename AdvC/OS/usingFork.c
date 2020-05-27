#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int g_var = 0;

int main()
{
	int l_var = 0;
	int i;
	pid_t n;
	
	
	sleep(10);
	
	n = fork(); 
	
	sleep(10);

	if(n < 0)
	{
		printf("error code handling");
	}
	
	else if(n > 0)
	{
		/*Parent code*/
		
		for(i = 1;i <= 30;++i)
		{
			++g_var;
			++l_var;
			
			printf("g_var -> %d l_var -> %d \n", g_var, l_var);
			
			sleep(20);
		}
	}
	
	else
	{
		/*Child code*/	
		
		for(i = 1;i <= 30;++i)
		{
			--g_var;
			--l_var;
			
			printf("g_var -> %d l_var -> %d \n", g_var, l_var);
			
			sleep(1);
		}
	}


	return 0;
}


