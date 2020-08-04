#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void PrintPing(int sig, siginfo_t *siginfo, void *context) {
    
    std::cout << "\033[0;31mPING\033[0m" << std::endl;
    sleep(1);
    
    if(kill(siginfo->si_pid, SIGUSR1) < 0) {
        std::cout << "sigaction" << std::endl;
        exit(getpid());  
    }
}

int main() {

    struct sigaction act;
    memset(&act, 0, sizeof(act));
	act.sa_sigaction = &PrintPing;
	act.sa_flags = SA_SIGINFO;
 
	if (sigaction(SIGUSR1, &act, NULL) < 0) {
		std::cout << "sigaction" << std::endl;
		return 1;
	}

    while(1) {}

    return 0;
}