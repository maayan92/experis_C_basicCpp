#include "handleMsg.h"
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <fstream>

namespace experis {

const int MSG_SIZE = 20;

void CheckMessage(message &a_msgRecieve, message &a_msgSend) {
    if(a_msgRecieve.m_msgData == a_msgSend.m_msgData) {
        std::cout << "\033[0;31mOK " << a_msgRecieve.m_msgData << "\033[0m" << std::endl;
    }
    else {
        std::cout << "\033[0;32mWRONG! " << a_msgSend.m_msgData << " != " << a_msgRecieve.m_msgData << "\033[0m" << std::endl;
    }
}

void RecieveMessage(int a_msgid, message &a_msgRecieve) {
    a_msgRecieve.m_msgType = 0;
    if(0 > msgrcv(a_msgid, &a_msgRecieve, sizeof(a_msgRecieve), 1, 0)) {
        std::cout << "recieve message failed!" << std::endl;
    }
}

void SendMessage(int a_msgid, message &a_msgSend) {
    a_msgSend.m_msgType = 1;
    if(0 > msgsnd(a_msgid, &a_msgSend, sizeof(a_msgSend), 0)) {
        std::cout << "send message failed!" << std::endl;
    }
}

int OpenQueuePipe(const char *a_fileName) {
    std::ofstream file(a_fileName);
    if(!file) {
        std::cout << "file failed to open" << std::endl;
        return -1;
    }
    key_t key = ftok(a_fileName, 65);
    if(0 > key) {
        std::cout << "open msg queue pipe failed!" << std::endl;
        return -1;
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if(0 > msgid) {
        std::cout << "get msg queue identifier pipe failed!" << std::endl;
        return -1;
    }

    return msgid;
}

} // experis