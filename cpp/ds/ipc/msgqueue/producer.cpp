#include "handleMsg.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int msgid = experis::OpenQueuePipe("msgqueue");
    experis::message msgSend, msgRecieve;
    srand(time(NULL));
    msgSend.m_msgData = rand();

    experis::SendMessage(msgid, msgSend);
    experis::RecieveMessage(msgid, msgRecieve);
    experis::CheckMessage(msgRecieve, msgSend);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}