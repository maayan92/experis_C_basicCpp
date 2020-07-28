#include "handleMsg.h"

int main() {

    int msgid = experis::OpenQueuePipe("msgqueue");
    experis::message msgRecieve;

    experis::RecieveMessage(msgid, msgRecieve);

    //msgRecieve.m_msgData = msgRecieve.m_msgData + 1;
    experis::SendMessage(msgid, msgRecieve);
  
    

    return 0; 
}