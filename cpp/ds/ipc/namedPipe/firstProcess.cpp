#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

const int MSG_SIZE = 20;

static void CheckMessage(char *a_msgRecieve, char *a_msgSend) {
    if(0 == strcmp(a_msgRecieve, a_msgSend)) {
        std::cout << "\033[0;31mOK " << a_msgRecieve << "\033[0m" << std::endl;
    }
    else {
        std::cout << "\033[0;32mWRONG! " << a_msgSend << " != " << a_msgRecieve << "\033[0m" << std::endl;
    }
}

static void RecieveMessage(char *a_fifo, char *a_msgSend) {
    char msgRecieve[MSG_SIZE];

    int fd = open(a_fifo, O_RDONLY);
    if(0 > fd) {
        std::cout << "first process open fifo failed!" << std::endl;
    }
    if(0 > read(fd, msgRecieve, MSG_SIZE)) {
        std::cout << "first process read failed!" << std::endl;
    }

    CheckMessage(msgRecieve, a_msgSend);

    close(fd);
} 

static void Communicate(char *a_fifo) {
    char msgSend[MSG_SIZE];

    srand(time(NULL));
    int msgNum = rand();
    sprintf(msgSend, "%d", msgNum);

    int fd = open(a_fifo, O_WRONLY);
    if(0 > fd) {
        std::cout << "first process open fifo failed!" << std::endl;
    }
    if(0 > write(fd, msgSend, strlen(msgSend) + 1)) {
        std::cout << "first process write failed!" << std::endl;
    }
    close(fd);

    RecieveMessage(a_fifo, msgSend);
}

int main() {

    char *fifo = "fifo";
  
    if(0 > mkfifo(fifo, 0666)) {
        std::cout << "open fifo pipe failed!" << std::endl;
    }

    Communicate(fifo);
    unlink(fifo);

    return 0; 
}