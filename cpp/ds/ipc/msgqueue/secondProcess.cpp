#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <fstream>

const int MSG_SIZE = 20;

typedef struct msg_buffer { 
    long m_msgType; 
    char m_msgText[MSG_SIZE]; 
} message; 

static void SendMessage(int a_msgid) {
    //sprintf(a_message, "%d", atoi(a_message)+1);
    message msgSend;

    msgSend.m_msgType = 1;
    if(0 > msgsnd(a_msgid, &msgSend, sizeof(msgSend), 0)) {
        std::cout << "second process send message failed!" << std::endl;
    }
} 

static void Communicate(int a_msgid) {
    message msgRecieve;

    msgRecieve.m_msgType = 0;
    if(0 > msgrcv(a_msgid, &msgRecieve, sizeof(msgRecieve), 1, 0)) {
        std::cout << "second process recieve message failed!" << std::endl;
    }

    SendMessage(a_msgid);
}

int main() {

    key_t key;
    std::ofstream file("msgqueue");
    key = ftok("msgqueue", 65);
    if(0 > key) {
        std::cout << "open msg queue pipe failed!" << std::endl;
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if(0 > msgid) {
        std::cout << "get msg queue identifier pipe failed!" << std::endl;
    }
  
    Communicate(msgid);

    return 0; 
}