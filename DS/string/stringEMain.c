#include <stdio.h>
#include <string.h>
#include "stringE.h"

int main()
{
	char str[LENGTH];
	int num;

	printf("please insert a string: ");
	fgets(str,sizeof(str),stdin);
	
	printf("string before reverse = %s \n",str);
	ReverseString(str);
	printf("reversed string = %s \n",str);

	printf("please insert string of number: ");
	fgets(str,sizeof(str),stdin);
	printf("the string number of = %s is %d \n",str, MyAtoI(str));
	
	printf("please insert a number: ");
	scanf("%d",&num);
	printf("the number = %d as string is = %s \n",num, MyItoA(num));


	return 0;
}
