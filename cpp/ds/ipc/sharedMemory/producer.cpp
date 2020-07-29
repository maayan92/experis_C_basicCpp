
#include "sharedMemory.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

namespace experis {

void FillNumbers(MemoryStructure *a_sharedMemAddr) {
    for(int i = 0; i < SHM_SIZE ; ++i) {
        a_sharedMemAddr->nums[i] = (rand() + 1) % 1000;
    }
}

} // experis

int main() {

    try {
        int shmid = experis::CreateSharedMemory("sharedMemory");

        experis::MemoryStructure *sharedMemAddr = experis::AttachingSharedMemory(shmid);

        //lock
        experis::FillNumbers(sharedMemAddr);
        //unlock

        experis::DetachingSharedMemory(sharedMemAddr);
        
    }catch(const experis::ExcCreateFailed& exc) {
        exc.what();
    }
    catch(const experis::ExcAttachingFailed& exc) {
        exc.what();
    }
    catch(const experis::ExcDetachingFailed& exc) {
        exc.what();
    }

    
    
    

    return 0;
}