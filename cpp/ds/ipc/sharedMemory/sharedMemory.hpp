#ifndef __SHARED_MEMORY_H__
#define __SHARED_MEMORY_H__

#include <iostream>
#include <exception>

namespace experis {

const int SHM_SIZE = 1000;

enum {
    CREATE_SHM_FAILED = -1
};

class ExcCreateFailed : std::exception {};
class ExcAttachingFailed : std::exception {};
class ExcDetachingFailed : std::exception {};

struct MemoryStructure {
		unsigned long readidx;
		unsigned long nums[SHM_SIZE];
		unsigned long writeidx;
		struct Result {
			unsigned long orignum;
			bool isPrime;
		} result[SHM_SIZE];
};

int CreateSharedMemory(const char* a_fileName);
MemoryStructure* AttachingSharedMemory(int a_shmid);
void DetachingSharedMemory(MemoryStructure *a_sharedMemAddr);


} // experis



#endif