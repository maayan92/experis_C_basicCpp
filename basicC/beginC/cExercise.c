#include <stdio.h>

int Factorial(int _n)
{
	int sum = 1;
	
	while(0 < _n)
	{
		sum *= _n;
		_n--;
	} 
	
	return sum;

}

int AscendingOrder(int _num)
{
	int temp;

	do
	{
		temp = _num%10;
		_num /= 10;

		if(temp <= _num%10)
		{
			return 0;
		}
	
	}while(0 != _num/100);

	return 1;
}

int PrimeNumber(int _primeNum)
{
	int i = _primeNum-2;

	if(1 == _primeNum || 2 == _primeNum || 0 == _primeNum%2)
	{
		return 0;
	}

	while(i > 1)
	{
		if(0 == _primeNum%i)
		{
			return 0;
		}

		i -= 2;
	}

	return 1;	
}

int Reverse(int _num)
{
	int newNum = 0;

	while(0 < _num)
	{	
		newNum = newNum*10 + _num%10;
		_num /= 10;
	}

	return newNum;
}

int Power(int _num, int _power)
{
	int sum = 1;

	while(0 < _power)
	{
		sum *= _num;
		_power--;
	}

	return sum;
}

int getArmstrongSum(int _number, int _cubes)
{
	int sum = 0;

	while(0 < _number)
	{
		sum += Power(_number%10,_cubes);
		_number /= 10;
	}

	return sum;
}

void ArmstrongNumber()
{
	int i, sum;

	for(i = 0;i <= 999;++i)
	{
		if(i < 10)
		{
			sum = getArmstrongSum(i,1);
		}
		else if(i < 100)
		{
			sum = getArmstrongSum(i,2);
		}
		else
		{
			sum = getArmstrongSum(i,3);
		}

		if(sum == i)
		{
			printf("The number %d is armstrong\n",i);
		}
	}

}



