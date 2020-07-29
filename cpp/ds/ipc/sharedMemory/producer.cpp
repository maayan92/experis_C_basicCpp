
#include "sharedMemory.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

namespace experis {

void FillNumbersToSharedMemory(MemoryStructure *a_sharedMemAddr) {
    for(int i = 0; i < SHM_SIZE ; ++i) {
        a_sharedMemAddr->nums[i] = (rand() + 1) % 1000;
    }
}

void PrintResultFromSharedMemory(MemoryStructure *a_sharedMemAddr) {
    for(int i = 0 ; i < SHM_SIZE ; ++i) {
        std::cout << "number -> " << a_sharedMemAddr->result[i].orignum << "\t"
                    << (a_sharedMemAddr->result[i].isPrime ? "\033[0;31m is prime" : "\033[0;32m is not prime") 
                            << "\033[0m" << std::endl;
    }
}

void WaitForConsumerToSetResult(MemoryStructure *a_sharedMemAddr, sem_t *a_semaphore) {
    long prevWriteIdx = 0;
    long curWriteIdx;
    do {
        sem_wait(a_semaphore);
        curWriteIdx = a_sharedMemAddr->writeidx;
        sem_post(a_semaphore);
    } while (curWriteIdx == prevWriteIdx);
}

void RunProducer(MemoryStructure *a_sharedMemAddr, sem_t *a_semaphore) {
    sem_post(a_semaphore);
    sem_wait(a_semaphore);
    experis::FillNumbersToSharedMemory(a_sharedMemAddr);
    sem_post(a_semaphore);

    experis::WaitForConsumerToSetResult(a_sharedMemAddr, a_semaphore);
    PrintResultFromSharedMemory(a_sharedMemAddr);
}

} // experis

int main() {
    try {
        int shmid = experis::CreateSharedMemory("sharedMemory");

        experis::MemoryStructure *sharedMemAddr = experis::AttachingSharedMemory(shmid);
        sharedMemAddr->readidx = 0;
        sharedMemAddr->writeidx = 0;

        sem_t *semaphore = sem_open("/readWriteSem", O_CREAT, 0644, 1);
        if (semaphore == SEM_FAILED) {
            std::cout << "failed to open semphore" << std::endl;
            return 1;
        }

        RunProducer(sharedMemAddr, semaphore);
        
        sem_close(semaphore);
        sem_unlink("/readWriteSem");
        experis::DetachingSharedMemory(sharedMemAddr);
        
    }catch(const experis::ExcCreateFailed& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcAttachingFailed& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcDetachingFailed& exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}