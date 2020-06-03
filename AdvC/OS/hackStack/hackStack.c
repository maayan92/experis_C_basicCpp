#include <stdio.h>
#include <stdlib.h>

static void foo2()
{
	printf("I'm in foo2!!\n\n");
}

static int foo1(int _i, int _j)
{
	int i, f = 10;
	
	printf("\nfoo\n");
	printf("i:\t decimal -> %d \taddress -> %p \thex -> %x \n", _i, (void*)&_i, _i);
	printf("j:\t decimal -> %d \taddress -> %p \thex -> %x \n", _j, (void*)&_j, _j);
	
	printf("\n");
	
	*((&f) + 5) = foo2;
	
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

	return 0;
}
