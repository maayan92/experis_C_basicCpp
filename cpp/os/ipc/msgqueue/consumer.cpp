#include "handleMsg.h"

int main() {

    int msgid = experis::OpenQueuePipe("msgqueue");
    experis::message msgRecieve;

    while(1) {
        experis::RecieveMessage(msgid, msgRecieve);

        std::cout << msgRecieve.m_msgData << std::endl;
        //msgRecieve.m_msgData = msgRecieve.m_msgData + 1;
        experis::SendMessage(msgid, msgRecieve);
    }

    return 0; 
}