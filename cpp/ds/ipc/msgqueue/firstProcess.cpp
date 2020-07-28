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

static void CheckMessage(message &a_msgRecieve, message &a_msgSend) {
    if(0 == strcmp(a_msgRecieve.m_msgText, a_msgSend.m_msgText)) {
        std::cout << "\033[0;31mOK " << a_msgRecieve.m_msgText << "\033[0m" << std::endl;
    }
    else {
        std::cout << "\033[0;32mWRONG! " << a_msgSend.m_msgText << " != " << a_msgRecieve.m_msgText << "\033[0m" << std::endl;
    }
}

static void RecieveMessage(int a_msgid, message &a_msgSend) {
    message msgRecieve;

    msgRecieve.m_msgType = 0;
    if(0 > msgrcv(a_msgid, &msgRecieve, sizeof(msgRecieve), 1, 0)) {
        std::cout << "first process recieve message failed!" << std::endl;
    }

    CheckMessage(msgRecieve, a_msgSend);
} 

static void Communicate(int a_msgid) {
    message msgSend;

    srand(time(NULL));
    int msgNum = rand();
    sprintf(msgSend.m_msgText, "%d", msgNum);

    msgSend.m_msgType = 1;
    if(0 > msgsnd(a_msgid, &msgSend, sizeof(msgSend), 0)) {
        std::cout << "first process send message failed!" << std::endl;
    }

    sleep(2);
    RecieveMessage(a_msgid, msgSend);
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
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}