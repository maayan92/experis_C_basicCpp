#include "sharedMemory.hpp"
#include <cmath>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <assert.h>

namespace experis {

bool CheckIfPrimeNumber(long a_number) {
    if(a_number != 2 && (a_number % 2) == 0) {
        return false;
    }
    for(int i = 3 ; i < sqrt(a_number) ; i += 2) {
        if((a_number % i) == 0) {
            return false;
        }
    }
    return true;
}

unsigned long ReadNumberFromSharedMemory(MemoryStructure *a_sharedMemAddr, sem_t *a_semaphore) {
    sem_wait(a_semaphore);
    if(a_sharedMemAddr->readidx >= SHM_SIZE) {
        return 0;
    }
    long num =  a_sharedMemAddr->nums[a_sharedMemAddr->readidx++];
    sem_post(a_semaphore);

    return num;
}

void WriteResultToSharedMemory(MemoryStructure *a_sharedMemAddr, long a_num, bool a_isPrime, sem_t *a_semaphore) {
    sem_wait(a_semaphore);
    a_sharedMemAddr->result[a_sharedMemAddr->writeidx].isPrime = a_isPrime;
    a_sharedMemAddr->result[a_sharedMemAddr->writeidx].orignum = a_num;
    ++a_sharedMemAddr->writeidx;
    sem_post(a_semaphore);
}

void RunConsumer(MemoryStructure *a_sharedMemAddr, sem_t *a_semaphore) {
    while(a_sharedMemAddr->readidx < SHM_SIZE) {
        unsigned long number = ReadNumberFromSharedMemory(a_sharedMemAddr, a_semaphore);
        if(!number) { break; }

        bool isPrime = experis::CheckIfPrimeNumber(number);
        WriteResultToSharedMemory(a_sharedMemAddr, number, isPrime, a_semaphore);
    }
}

} // experis

int main() {
    try {
        int shmid = experis::CreateSharedMemory("sharedMemory");

        experis::MemoryStructure *sharedMemAddr = experis::AttachingSharedMemory(shmid);

        sem_t *semaphore = sem_open("/readWriteSem", O_CREAT);
        if (semaphore == SEM_FAILED) {
            std::cout << "Failed to open semphore" << std::endl;
           return 1;
        }
        int status = sem_post(semaphore);
        assert(0 == status);
        RunConsumer(sharedMemAddr, semaphore);

        sem_close(semaphore);
        sem_unlink("/readWriteSem");
        experis::DetachingSharedMemory(sharedMemAddr);
        
    }catch(const experis::ExcGetShmKeyFailed& exc) {
        std::cout << exc.what() << std::endl;
    }
    catch(const experis::ExcCreateFailed& exc) {
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