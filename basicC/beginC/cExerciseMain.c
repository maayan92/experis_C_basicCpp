#include <stdio.h>
#include "cExercise.h"

int main()
{

	int n, ascending, prime;

	printf("Please enter a factorial number: ");
	scanf("%d", &n);

	printf("The factorial of %d is %d \n", n, Factorial(n));

	
	printf("Please enter an ascending/not number: ");
	scanf("%d", &n);

	ascending = AscendingOrder(n);

	if(0 == ascending)
	{
		printf("The number %d is not in ascending order \n", n);
	}
	else
	{
		printf("The number %d is in ascending order \n", n);
	}
	

	printf("Please enter an prime/not number: ");
	scanf("%d", &n);

	prime = PrimeNumber(n);

	if(0 == prime)
	{
		printf("The number %d is not a prime number \n", n);
	}
	else
	{
		printf("The number %d is a prime number \n", n);
	}

	printf("Please enter a number to reverse: ");
	scanf("%d", &n);

	printf("The reverse number of %d is %d \n", n, Reverse(n));

	ArmstrongNumber();

	return 0;
}















