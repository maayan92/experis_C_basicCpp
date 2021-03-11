#include "socketServerSelect.h"
#include "genDLList.h"
#include "genDLListIter.h"
#include "genDLListIterFunc.h"
#include <stdio.h>
#include <arpa/inet.h>  /* for inet_addr */
#include <unistd.h>  /* for close */
#include <stdlib.h>  /* for allocation */
#include <errno.h>  /* for errno */
#include <sys/select.h>  /* for fd_set */
#include <string.h>  /* for strlen */
#include <stdbool.h>


#define MAGIC_NUMBER 0xafccebdd
#define QUEUE_SIZE 500
#define BUFFER_SIZE 100
#define MAX_NUM_OF_SOCK 1024

#define IS_SERVER_NOT_EXIST(sr) (!(sr) || (sr)->m_magicNumber != MAGIC_NUMBER)


struct server
{
    size_t m_magicNumber;
    int m_socketNum;
    genList *m_clientList;
    struct sockaddr_in m_sin;
    fd_set m_master;
    fd_set m_tempMaster;
    int m_currentlyActive;
    int m_numOfOpenSock;
};


static sockError SockBind(server *_srvr);
static sockError SockListen(server *_srvr, size_t _queueSize);
static void CloseSocket(void *_sock);
static sockError ServerReceive(server *_srvr, int _clientSock, char *_buffer, size_t _bufferSize);
static int ServerIsSocketEqual(void *_socketA, void *_socketB);


server* ServerCreate(char *_address, int _port)
{
    server *srvr;
    int optval = 1;
    
    if(!(srvr = (server*)calloc(1, sizeof(server))))
    {
        return NULL;
    }
    if(!(srvr->m_clientList = GenDLListCreate()))
    {
        free(srvr);
        return NULL;
    }
    
    srvr->m_socketNum = socket(AF_INET, SOCK_STREAM, 0);
    if(srvr->m_socketNum < 0)
    {
        GenDLListDestroy(srvr->m_clientList, NULL);
        free(srvr);
        perror("socket failed");
        return NULL;
    }
    if(setsockopt(srvr->m_socketNum, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse failed");
        close(srvr->m_socketNum);
        GenDLListDestroy(srvr->m_clientList, NULL);
        free(srvr);
        return NULL;
    }
    
    srvr->m_sin.sin_family = AF_INET;
    srvr->m_sin.sin_addr.s_addr = _address? inet_addr(_address): INADDR_ANY;
    srvr->m_sin.sin_port = htons(_port);
    FD_ZERO(&srvr->m_master);
    FD_SET(srvr->m_socketNum, &srvr->m_master);
    
    if(SockBind(srvr) != SOCK_SUCCESS || SockListen(srvr, QUEUE_SIZE) != SOCK_SUCCESS)
    {
        close(srvr->m_socketNum);
        GenDLListDestroy(srvr->m_clientList, NULL);
        free(srvr);
        return NULL;
    }
    
    srvr->m_magicNumber = MAGIC_NUMBER;
    
    return srvr;
}

void ServerDestroy(server *_srvr)
{
    if(!IS_SERVER_NOT_EXIST(_srvr))
    {
        GenDLListDestroy(_srvr->m_clientList, CloseSocket);
        close(_srvr->m_socketNum);
        free(_srvr);
    }
}

sockError ServerNewActivity(server *_srvr)
{
    if(IS_SERVER_NOT_EXIST(_srvr))
    {
        return SOCK_NOT_INITIALIZED;
    }
    
    _srvr->m_tempMaster = _srvr->m_master;
    
    if((_srvr->m_currentlyActive = select(MAX_NUM_OF_SOCK, &_srvr->m_tempMaster, NULL, NULL, NULL)) < 0)
    {
        perror("select failed");
        _srvr->m_currentlyActive = 0;
        return SOCK_FAIL;
    }
    return SOCK_SUCCESS;
}

sockError ServerAcceptServer(server *_srvr)
{
    socklen_t addr_len = sizeof(struct sockaddr_in);
    int *newClientSock;
    
    if(IS_SERVER_NOT_EXIST(_srvr))
    {
        return SOCK_NOT_INITIALIZED;
    }
    if(FD_ISSET(_srvr->m_socketNum, &_srvr->m_tempMaster))
    {
        if(!(newClientSock = (int*)malloc(sizeof(int))))
        {
            return SOCK_ALLOCATION_FAILED;
        }
        
        if((*newClientSock = accept(_srvr->m_socketNum, (struct sockaddr*)&_srvr->m_sin, &addr_len)) < 0)
        {
            free(newClientSock);
            perror("accept failed");
            return SOCK_FAIL;
        }
        --_srvr->m_currentlyActive;
        if(_srvr->m_numOfOpenSock > 1000)
        {
            CloseSocket(newClientSock);
            return SOCK_FULL;
        }
        
        FD_SET(*newClientSock, &_srvr->m_master);
        GenDLListPushTail(_srvr->m_clientList, newClientSock);
        ++_srvr->m_numOfOpenSock;
    }
    return SOCK_SUCCESS;
}

sockError ServerRunAndReceive(server *_srvr, messageHandlerFunc _messageFunc, void *_context)
{
    genListIter itr, temp, end;
    sockError e;
    int *clientSock;
    char buffer[BUFFER_SIZE];
    
    if(IS_SERVER_NOT_EXIST(_srvr))
    {
        return SOCK_NOT_INITIALIZED;
    }
    if(!_messageFunc)
    {
        return SOCK_WRONG_INPUT;
    }
    
    itr = GenListIterBegin(_srvr->m_clientList);
    end = GenListIterEnd(_srvr->m_clientList);
    
    while(_srvr->m_currentlyActive > 0 && !GenListIterEquals(itr, end))
    {
        clientSock = GenListIterGet(itr);
        
        if(FD_ISSET(*clientSock, &_srvr->m_tempMaster))
        {
            if((e = ServerReceive(_srvr, *clientSock, buffer, BUFFER_SIZE)) == SOCK_SUCCESS)
            {
                _messageFunc(buffer, *clientSock, _context);
                itr = GenListIterNext(itr);
            }
            else
            {
                if(e == SOCK_CLOSED || e == SOCK_FAIL)
                {
                    temp = itr;
                    itr = GenListIterNext(itr);
                    GenListIterRemove(temp);
                    FD_CLR(*clientSock, &_srvr->m_master);
                    CloseSocket(clientSock);
                    --_srvr->m_numOfOpenSock;
                }
                else
                {
                    itr = GenListIterNext(itr);
                }
            }
            --_srvr->m_currentlyActive;
        }
        else
        {
            itr = GenListIterNext(itr);
        }
    }
    return SOCK_SUCCESS;
}

sockError ServerSend(server *_srvr, int _clientSock, char *_data)
{
    size_t len;
    genListIter itr, end;
    
    if(IS_SERVER_NOT_EXIST(_srvr))
    {
        return SOCK_NOT_INITIALIZED;
    }
    if(!_data || (len = strlen(_data)) < 1)
    {
        return SOCK_WRONG_INPUT;
    }
    
    if(send(_clientSock, _data, len, 0) < 0)
    {
        end = GenListIterEnd(_srvr->m_clientList);
        itr = GenListIterFindFirst(GenListIterBegin(_srvr->m_clientList), end, ServerIsSocketEqual, &_clientSock);
        if(!GenListIterEquals(itr, end) && *(int*)GenListIterGet(itr) == _clientSock)
        {
            GenListIterRemove(itr);
            CloseSocket(&_clientSock);
        }
        return SOCK_FAIL;
    }
    return SOCK_SUCCESS;
}

static sockError SockBind(server *_srvr)
{
    if(bind(_srvr->m_socketNum, (struct sockaddr*)&_srvr->m_sin, sizeof(struct sockaddr_in)) < 0)
    {
        perror("bind failed");
        return SOCK_FAIL;
    }
    return SOCK_SUCCESS;
}

static sockError SockListen(server *_srvr, size_t _queueSize)
{
    if(listen(_srvr->m_socketNum, _queueSize) < 0)
    {
        perror("listen failed");
        return SOCK_FAIL;
    }
    return SOCK_SUCCESS;
}

static void CloseSocket(void *_sock)
{
    if(*(int*)_sock > 0)
    {
        close(*(int*)_sock);
    }
    free(_sock);
}

static sockError ServerReceive(server *_srvr, int _clientSock, char *_buffer, size_t _bufferSize)
{
    int readBites;
    
    readBites = recv(_clientSock, _buffer, _bufferSize, 0);
    
    if(readBites == 0)
    {
        return SOCK_CLOSED;
    }
    else if(readBites < 0)
    {
        perror("receive failed");
        return SOCK_FAIL;
    }
    _buffer[readBites] = '\0';
    
    return SOCK_SUCCESS;
}

static int ServerIsSocketEqual(void *_socketA, void *_socketB)
{
    return *(int*)_socketA == *(int*)_socketB;
}




