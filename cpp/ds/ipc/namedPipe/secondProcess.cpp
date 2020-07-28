#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace experis {

const int MSG_SIZE = 20;

static void SendMessage(char *a_fifo, char *a_message) {
    //sprintf(a_message, "%d", atoi(a_message)+1);

    int fd = open(a_fifo, O_WRONLY);
    if(0 > fd) {
        std::cout << "second process open fifo failed!" << std::endl;
    }
    if(0 > write(fd, a_message, strlen(a_message) + 1)) {
        std::cout << "second process write failed!" << std::endl;
    }
    close(fd);
} 

static void Communicate(char *a_fifo) {
    char message[MSG_SIZE];

    int fd = open(a_fifo, O_RDONLY);
    if(0 > fd) {
        std::cout << "second process open fifo failed!" << std::endl;
    }
    if(0 > read(fd, message, MSG_SIZE)) {
        std::cout << "second process read failed!" << std::endl;
    }
    close(fd);

    SendMessage(a_fifo, message);
}

} // experis

int main() {

    char *fifo = "fifo";
  
    experis::Communicate(fifo);

    return 0; 
}