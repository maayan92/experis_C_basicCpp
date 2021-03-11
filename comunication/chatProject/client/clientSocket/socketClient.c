#include "socketClient.h"
#include <stdio.h>
#include <sys/socket.h>  /* for stream type */
#include <arpa/inet.h>  /* for inet_addr */
#include <unistd.h>  /* for close */
#include <stdlib.h>  /* for allocation */
#include <string.h>  /* for strlen */
#include <stdbool.h>


#define MAGIC_NUMBER 0xafccebdd
#define PERCENT_TO_OPEN 30
#define PERCENT_TO_CLOSE 5
#define PERCENT_TO_SEND 50
#define PERCENT_WHOLE 100
#define BUFFER_SIZE 100

#define IS_CLIENT_NOT_EXIST(cl) (!(cl) || (cl)->m_magicNumber != MAGIC_NUMBER)


struct client
{
    size_t m_magicNumber;
    int m_socketNum;
    struct sockaddr_in m_sin;
};


static sockError CloseSock(client *_clnt);


client* ClientCreate(char *_address, int _port)
{
    client *clnt;
    
    if(!_address || !(clnt = (client*)calloc(1, sizeof(client))))
    {
        return NULL;
    }
    
    clnt->m_sin.sin_family = AF_INET;
    clnt->m_sin.sin_addr.s_addr = inet_addr(_address);
    clnt->m_sin.sin_port = htons(_port);
    clnt->m_magicNumber = MAGIC_NUMBER;
    
    return clnt;
}

void ClientDestroy(client *_clnt)
{
    if(!IS_CLIENT_NOT_EXIST(_clnt))
    {
        CloseSock(_clnt);
        free(_clnt);
    }
}

sockError ClientOpenSock(client *_clnt)
{
    if(IS_CLIENT_NOT_EXIST(_clnt))
    {
        return SOCK_NOT_INITIALIZED;
    }
    
    _clnt->m_socketNum = socket(AF_INET, SOCK_STREAM, 0);
    if(_clnt->m_socketNum < 0)
    {
        perror("socket failed");
        _clnt->m_socketNum = 0;
        return SOCK_FAIL;
    }
    return SOCK_SUCCESS;
}

sockError ClientConnect(client *_clnt)
{
    if(IS_CLIENT_NOT_EXIST(_clnt))
    {
        return SOCK_NOT_INITIALIZED;
    }
    
    if(connect(_clnt->m_socketNum, (struct sockaddr*)&_clnt->m_sin, sizeof(struct sockaddr_in)) < 0)
    {
        perror("connection failed");
        CloseSock(_clnt);
        return SOCK_FAIL;
    }
    return SOCK_SUCCESS;
}

sockError ClientSend(client *_clnt, char *_data)
{
    size_t dataSize;
    
    if(IS_CLIENT_NOT_EXIST(_clnt))
    {
        return SOCK_NOT_INITIALIZED;
    }
    if(!_data || (dataSize = strlen(_data)) < 1)
    {
        return SOCK_WRONG_INPUT;
    }
    
    if(send(_clnt->m_socketNum, _data, dataSize, 0) < 0)
    {
        perror("send failed");
        CloseSock(_clnt);
        return SOCK_FAIL;
    }
    return SOCK_SUCCESS;
}

sockError ClientReceive(client *_clnt, char *_buffer, size_t _bufferSize)
{
    int readBites;
    
    if(IS_CLIENT_NOT_EXIST(_clnt))
    {
        return SOCK_NOT_INITIALIZED;
    }
    if(!_buffer || _bufferSize < 1)
    {
        return SOCK_WRONG_INPUT;
    }
    
    readBites = recv(_clnt->m_socketNum, _buffer, _bufferSize, 0);
    
    if(readBites == 0)
    {
        return SOCK_CLOSED;
    }
    else if(readBites < 0)
    {
        perror("receive failed");
        CloseSock(_clnt);
        return SOCK_FAIL;
    }
    _buffer[readBites] = '\0';
    
    return SOCK_SUCCESS;
}

static sockError CloseSock(client *_clnt)
{
    if(!_clnt->m_socketNum)
    {
        return SOCK_CLOSED;
    }
    close(_clnt->m_socketNum);
    _clnt->m_socketNum = 0;
    return SOCK_SUCCESS;
}



