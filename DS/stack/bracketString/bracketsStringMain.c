#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bracketsString.h"


int main()
{
	char str[LENGTH];
	int isValid;

	printf("Please insert string of brackets: ");
	scanf("%s",str);

	isValid = ValidBrackets(str);

	if(true == isValid)
	{
		printf("\nThe string is brackets valid!\n");
	}
	else
	{
		printf("\nThe string is not brackets valid!\n");
	}


	return 0;
}
