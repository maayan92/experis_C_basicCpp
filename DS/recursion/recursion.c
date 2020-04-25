#include <stdio.h>
#include "dynamicVector.h"

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

size_t Fibonacci(size_t _num, Vector *_vector)
{
	int sum, data;

	if(1 >= _num)
	{
		if(SUCCEEDED != VectorGet(_vector,_num,&data))
		{
			VectorAddTail(_vector,_num);
		}
		return _num;
	}

	sum = Fibonacci(_num-2,_vector) + Fibonacci(_num-1,_vector);
	
	if(SUCCEEDED != VectorGet(_vector,_num,&data))
	{
		VectorAddTail(_vector,sum);
	}
	
	return sum;
}

int main()
{
	int num, k;
	Vector *vector;

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

	vector = VectorCreate(num,0);
	
	if(NULL == vector)
	{
		printf("error \n");
		return 0;
	}


	Fibonacci(num,vector);
	PrintArray(vector);
	printf("\n");

	return 0;
}




