#include <stdio.h>
#include <stdlib.h>    /*for create new terminal (system call)*/
#include <sys/types.h> /*for kill (system call)*/
#include <signal.h>    /*for kill (system call)*/
#include <unistd.h>    /*for sleep (system call)*/


int main()
{
        pid_t pnum1,pnum2;
        FILE* fp;
        char *filename = "file.txt";
        
        if((fp = fopen(filename, "r")) == NULL)
        {
                printf("unable to open file\n");
                return 0;
        }
        fscanf(fp,"%d",&pnum1);
        fscanf(fp,"%d",&pnum2);
        fclose(fp);       
        
       
        kill(pnum1, SIGKILL);       
        kill(pnum2, SIGKILL);
        return 0;
}
