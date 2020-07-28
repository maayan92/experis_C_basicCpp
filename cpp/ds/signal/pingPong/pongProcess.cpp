#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void PrintPong(int sig, siginfo_t *siginfo, void *context) {
    
    std::cout << "\033[0;32mPONG\033[0m" << std::endl;

    sleep(1);

    kill(siginfo->si_pid, SIGUSR1);
}

int main(int a_argv, char *a_argc[]) {

    struct sigaction act;
    int pid = atoi(a_argc[1]);

    kill(pid, SIGUSR1);
 
	act.sa_sigaction = &PrintPong;
	act.sa_flags = SA_SIGINFO;
 
	if (sigaction(SIGUSR1, &act, NULL) < 0) {
		std::cout << "sigaction" << std::endl;
		return 1;
	}

    while(1) {}

    return 0;
}