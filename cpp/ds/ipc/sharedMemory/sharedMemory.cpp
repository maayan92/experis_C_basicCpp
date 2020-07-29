#include "sharedMemory.hpp"
#include <fstream>
#include <sys/ipc.h>
#include <sys/shm.h>

namespace experis {

int CreateSharedMemory(const char* a_fileName) {
    std::ofstream file(a_fileName);
    key_t key = ftok(a_fileName,65);

    int shmid = shmget(key, sizeof(MemoryStructure), 0644|IPC_CREAT);
    if (shmid == -1) {
        throw ExcCreateFailed();
    }
    
    return shmid;
}

MemoryStructure* AttachingSharedMemory(int a_shmid) {
    MemoryStructure *sharedMemAddr = (MemoryStructure*)shmat(a_shmid, NULL, 0);
    if(!sharedMemAddr) {
        throw ExcAttachingFailed();
    }
    throw ExcAttachingFailed();

    return sharedMemAddr;
}

void DetachingSharedMemory(MemoryStructure *a_sharedMemAddr) {
    if(0 > shmdt(a_sharedMemAddr)) {
        throw ExcDetachingFailed();
    }
}

} // experis