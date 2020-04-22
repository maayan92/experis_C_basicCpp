#include <stdio.h>
#include "stack.h"

void RecPrintNumbers(int _numOfNums)
{
	if(0 == _numOfNums)
	{
		return;
	}

	RecPrintNumbers(--_numOfNums);

	printf("%d ",_numOfNums);
}

int RecPower(int _n,int _k)
{
	if(1 == _k)
	{
		return _n;
	}

	return _n*RecPower(_n,_k-1);
}

int RecFactorial(int _n)
{
	if(0 ==_n)
	{
		return 1;
	}

	return _n*RecFactorial(_n-1);
}

int main()
{
	int num, k;

	printf("Print numbers -> \nplease insert a number: ");
	scanf("%d", &num);

	RecPrintNumbers(num);
	printf("\n");

	printf("Power calculation -> \nplease insert a number: ");
	scanf("%d", &num);
	printf("please insert a power number: ");
	scanf("%d", &k);

	printf("%d power %d = %d \n",num,k, RecPower(num,k));

	printf("Factorial number -> \nplease insert a number: ");
	scanf("%d", &num);

	printf("the factorial of %d = %d \n",num, RecFactorial(num));


	return 0;
}




