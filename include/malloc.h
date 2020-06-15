#ifndef __MALLOC_H__
#define __MALLOC_H__

#define SIZE_OF_INIT 12
#define INIT_PLACES 3

typedef unsigned char BYTE;

/*
	Description: initialize the allocation memory.
	Input: _memory - pointer to the allocation memory, _memorySize - memory allocation size, should be more than SIZE_OF_INIT.
	Return value: nothing returns.
*/
void MyMallocInit(void* _memory, size_t _memorySize);

/*
	Description: allocate _requiredBlockSize size memory space.
	Input: _memory - pointer to the allocation memory, _requiredBlockSize - 
	Return value: returns pointer to the allocatede space.
*/
void* MyMalloc(void* _memory, size_t _requiredBlockSize);

/*
	Description: free a memory space.
	Input: _myBlock - pointer to the memory space.
	Return value: nothing returns.
*/
void MyFree(void* _myBlock);


#endif
