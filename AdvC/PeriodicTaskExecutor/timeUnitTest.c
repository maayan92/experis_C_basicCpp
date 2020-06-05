#include <stdio.h>
#include <stdlib.h>

#include "time.h"

typedef enum
{
	SUCCEDD,
	FAILED
}Result;


int main()
{
	clock_t end;
	struct timespec *t2;

	clock_t start = clock(); 
	struct timespec *t = GetCurrentTime();
	
	sleep(5);
	
	t2 = GetCurrentTime();
	
	end = clock(); 
	
	printf("time: sec %ld ns %ld start %ld end %ld \n", t->tv_sec, t->tv_nsec, start / CLOCKS_PER_SEC, end / CLOCKS_PER_SEC);
	
	printf("time: sec %ld ns %ld start %ld end %ld \n", t2->tv_sec, t2->tv_nsec, start, end);

	free(t);
	free(t2);


	return 0;
}


