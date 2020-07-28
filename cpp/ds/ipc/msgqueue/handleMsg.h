#ifndef __HANDLE_MSG_H__
#define __HANDLE_MSG_H__

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

namespace experis {

typedef struct msgBuffer { 
    long m_msgType;
    int m_msgData;
} message;

void CheckMessage(message &a_msgRecieve, message &a_msgSend);
void RecieveMessage(int a_msgid, message &a_msgRecieve);
void SendMessage(int a_msgid, message &a_msgSend);
int OpenQueuePipe(const char *a_fileName);

} // experis

#endif