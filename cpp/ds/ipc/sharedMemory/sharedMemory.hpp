#ifndef __SHARED_MEMORY_H__
#define __SHARED_MEMORY_H__

#include <iostream>
#include <exception>

namespace experis {

const int SHM_SIZE = 1000;

class ExcCreateFailed : std::exception {
public:  
    const char* what() const throw() { return "shared memory create failed!"; }
};
class ExcAttachingFailed : std::exception {
public:
    const char* what() const throw() { return "shared memory attaching failed!"; }
};
class ExcDetachingFailed : std::exception {
public:
    const char* what() const throw() { return "shared memory detaching failed!"; }
};

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