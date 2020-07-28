#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

namespace experis {

const int MSG_SIZE = 20;
const int READ = 0;
const int WRITE = 1;

static void ChildCode(int *a_fd) {
    char message[MSG_SIZE];

    if(0 > read(a_fd[READ], message, MSG_SIZE)) {
        std::cout << "child read failed!" << std::endl;
    }
    close(a_fd[READ]);

    //sprintf(message, "%d", atoi(message)+1);
    if(0 > write(a_fd[WRITE], message, strlen(message) + 1)) {
        std::cout << "child write failed!" << std::endl;
    }
    close(a_fd[WRITE]);
}

static void CheckMessage(char *a_msgRecieve, char *a_msgSend) {
    if(0 == strcmp(a_msgRecieve, a_msgSend)) {
        std::cout << "\033[0;31mOK " << a_msgRecieve << "\033[0m" << std::endl;
    }
    else {
        std::cout << "\033[0;32mWRONG! " << a_msgSend << " != " << a_msgRecieve << "\033[0m" << std::endl;
    }
}

static void FatherCode(int *a_fd) {
    char msgSend[MSG_SIZE], msgRecieve[MSG_SIZE];
    srand(time(NULL));
    int msgNum = rand();

    sprintf(msgSend, "%d", msgNum);

    if(0 > write(a_fd[WRITE], msgSend, strlen(msgSend) + 1)) {
        std::cout << "father write failed!" << std::endl;
    }
    close(a_fd[WRITE]);

    wait(NULL);
    if(0 > read(a_fd[READ], msgRecieve, MSG_SIZE)) {
        std::cout << "father read failed!" << std::endl;
    }

    CheckMessage(msgRecieve, msgSend);

    close(a_fd[READ]);
}

void ForkPipe() {
    pid_t pid;
    int fd[2];

    if(-1 == pipe(fd)) {
        std::cout << "pipe failed!" << std::endl;
        return;
    }

    pid = fork();
    if(pid == 0) { // child
        ChildCode(fd);
    }
    else if(pid > 0) { // father
        FatherCode(fd);
    }
    else {
        std::cout << "failed!" << std::endl;
        return;
    }
}

} //experis

int main() {
    experis::ForkPipe();

    return 0;
}