#include "handleMsg.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {

    int msgid = experis::OpenQueuePipe("msgqueue");
    experis::message msgSend, msgRecieve;

    while(1) {
        srand(time(NULL));
        msgSend.m_msgData = rand();

        std::cout << msgSend.m_msgData << std::endl;
        sleep(1);
        experis::SendMessage(msgid, msgSend);
        experis::RecieveMessage(msgid, msgRecieve);
        experis::CheckMessage(msgRecieve, msgSend);
    }

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}