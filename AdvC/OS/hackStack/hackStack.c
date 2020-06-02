#include <stdio.h>
#include <stdlib.h>

static void foo2()
{
	printf("I'm in foo2!!\n");
}

static int foo1(int _i, int _j)
{
	int i, f = 10;
	void **p;
	
	printf("\nfoo\n");
	printf("i:\t decimal -> %d \taddress -> %p \thex -> %x \n", _i, (void*)&_i, _i);
	printf("j:\t decimal -> %d \taddress -> %p \thex -> %x \n", _j, (void*)&_j, _j);

	printf("\n");
	for(i = 0;i < 20;i+=4)
	{
		printf(" value -> %-15d  hex -> %-15x  address -> %p \n", *((&f) + i), *((&f) + i), (&f) + i);
	}
	
	printf("\n hex -> %-15x  address -> %p \n", p, p);
	
	*((&f) + 8) = foo2;
	
	return 2000;	
}


int main()
{
	int i = 200;
	int j = 300;
	int k;
	
	k = foo1(i,j);
	
	printf("\ni:\t decimal -> %d \taddress -> %p \thex -> %x \n", i, (void*)&i, i);
	printf("j:\t decimal -> %d \taddress -> %p \thex -> %x \n", j, (void*)&j, j);
	
	printf("\nfoo1:\t address -> %p \n", foo1);
	printf("\nfoo2:\t address -> %p \thex -> %x \n", foo2, foo2);
	printf("\nmain:\t address -> %p \thex -> %x \n", main, main);



	return 0;
}
