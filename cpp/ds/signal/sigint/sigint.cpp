#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

static void PrintHaHaHa(int sig, siginfo_t *siginfo, void *context) {
    
    std::cout << "\033[0;31mHA HA HA\033[0m" << std::endl;
    sleep(1);
}

int main() {

    struct sigaction act;
    memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &PrintHaHaHa;
	act.sa_flags = SA_SIGINFO;
 
	if (sigaction(SIGINT, &act, NULL) < 0) {
		std::cout << "sigaction" << std::endl;
		return 1;
	}

    srand(time(NULL));
    while(1) {
        std::cout << rand() % 100 << std::endl;
    }

    return 0;
}