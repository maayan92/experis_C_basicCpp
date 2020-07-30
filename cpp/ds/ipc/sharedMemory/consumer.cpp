#include "sharedMemory.hpp"
#include <cmath>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

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

long ReadNumberFromSharedMemory(MemoryStructure *a_sharedMemAddr) {
    return a_sharedMemAddr->nums[a_sharedMemAddr->readidx++];
}

void WriteResultToSharedMemory(MemoryStructure *a_sharedMemAddr, long a_num, bool a_isPrime) {
    a_sharedMemAddr->result[a_sharedMemAddr->writeidx].isPrime = a_isPrime;
    a_sharedMemAddr->result[a_sharedMemAddr->writeidx].orignum = a_num;
    ++a_sharedMemAddr->writeidx;
}

void RunConsumer(MemoryStructure *a_sharedMemAddr, sem_t *a_semaphore) {
    while(a_sharedMemAddr->readidx < SHM_SIZE) {
       
        sem_wait(a_semaphore);
        long number = ReadNumberFromSharedMemory(a_sharedMemAddr);
        sem_post(a_semaphore);

        bool isPrime = experis::CheckIfPrimeNumber(number);

        sem_wait(a_semaphore);
        WriteResultToSharedMemory(a_sharedMemAddr, number, isPrime);
        sem_post(a_semaphore);
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
        sem_post(semaphore);
        RunConsumer(sharedMemAddr, semaphore);

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