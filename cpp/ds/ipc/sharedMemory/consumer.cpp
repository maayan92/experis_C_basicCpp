#include "sharedMemory.hpp"

namespace experis {




} // experis

int main() {
    int shmid = experis::CreateSharedMemory("sharedMemory");

    experis::MemoryStructure *sharedMemAddr = experis::AttachingSharedMemory(shmid);

    experis::DetachingSharedMemory(sharedMemAddr);

    return 0;
}