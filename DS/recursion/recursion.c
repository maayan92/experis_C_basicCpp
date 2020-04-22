#include <stdio.h>

void RecPrintNumbers(int _numOfNums)
{
	if(0 == _numOfNums)
	{
		return;
	}

	RecPrintNumbers(--_numOfNums);

	printf("%d ",_numOfNums);
}

int RecPower(int _num,int _k)
{
	if(1 == _k)
	{
		return _num;
	}

	return _num*RecPower(_num,_k-1);
}

int RecFactorial(int _num)
{
	if(0 ==_num)
	{
		return 1;
	}

	return _num*RecFactorial(_num-1);
}

size_t Fibonacci(size_t _num)
{
	if(1 >= _num)
	{
		return _num;
	}

	return Fibonacci(_num-1) + Fibonacci(_num-2);
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

	printf("Factorial number -> \nplease insert a number: ");
	scanf("%d", &num);

	printf("the fibonacci of %d = %ld \n",num, Fibonacci(num));


	return 0;
}




