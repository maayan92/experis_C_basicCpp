#include <iostream>
#include <unistd.h>
#include <signal.h>

static void PrintPing(int sig, siginfo_t *siginfo, void *context) {
    
    std::cout << "\033[0;31mPING\033[0m" << std::endl;

    sleep(1);

    kill(siginfo->si_pid, SIGUSR1);
}

int main() {

    struct sigaction act;
 
	act.sa_sigaction = &PrintPing;
	act.sa_flags = SA_SIGINFO;
 
	if (sigaction(SIGUSR1, &act, NULL) < 0) {
		std::cout << "sigaction" << std::endl;
		return 1;
	}

    while(1) {}

    return 0;
}