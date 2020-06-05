#include <stdio.h>
#include <stdlib.h>

static const char __func__() = "function-name";

#pragma pack(1)
struct mystruct
{
	char ch;
	char k;
	int i;
	char arr[13];
	long lj;
	double dl;
};
#pragma pack()

int main()
{

	/*printf("struct size %ld \n",sizeof(struct mystruct));*/
	
	
	printf("module: %s Line: %d, Function: %s ",__FILE__, __LINE__, __func__);

	return 0;
}







