#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void PrintPong(int sig, siginfo_t *siginfo, void *context) {
    
    std::cout << "\033[0;32mPONG\033[0m" << std::endl;
    sleep(1);
    
    if(kill(siginfo->si_pid, SIGUSR1) < 0) {
        std::cout << "kill failed" << std::endl;
        exit(getpid());
    }
}

int main(int a_argv, char *a_argc[]) {

    if(a_argv < 2) { return 1; }
    
    struct sigaction act;
    memset(&act, 0, sizeof(act));
	act.sa_sigaction = &PrintPong;
	act.sa_flags = SA_SIGINFO;
 
	if (sigaction(SIGUSR1, &act, NULL) < 0) {
		std::cout << "sigaction failed" << std::endl;
		return 1;
	}

    if(kill(atoi(a_argc[1]), SIGUSR1) < 0) {
        std::cout << "kill failed" << std::endl;
        return 1;
    }

    while(1) {}

    return 0;
}