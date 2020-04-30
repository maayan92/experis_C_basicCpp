#include <stdio.h>
#include "stack.h"
#include "linkedList.h"

typedef struct Details
{
	size_t m_id;
	size_t m_age;
	char m_name[50];

}Details;

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

size_t Fibonacci(size_t _num, Stack *_stack)
{
	int sum;

	if(1 >= _num)
	{
		if(StackNumOfelements(_stack) == _num)
		{
			StackPush(_stack,_num);
		}
		return _num;
	}

	sum = Fibonacci(_num-2,_stack) + Fibonacci(_num-1,_stack);
	
	if(StackNumOfelements(_stack) <= _num)
	{
		StackPush(_stack,sum);
	}
	
	return sum;
}

Person* CreatePersonsList()
{
	Person *listHead = NULL, *newPerson;
	int size = 4, i;

	Details detailsArr[4] = {{1,25,"may"},{3,5,"lia"},{0,25,"yos"},{2,25,"mosh"}};

	for(i = 0;i < size;++i)
	{
		newPerson = CreatePerson(detailsArr[i].m_id,detailsArr[i].m_name,detailsArr[i].m_age);
		if(NULL == newPerson)
		{
			return NULL;
		}

		listHead = ListInsertHead(listHead,newPerson);
		if(NULL == listHead)
		{
			DestroyListR(newPerson);
			return NULL;
		}
	}

	return listHead;
}

int main()
{
	int num, k;
	Stack *stack;

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

	stack = StackCreate(num,0);
	
	if(NULL == stack)
	{
		printf("error \n");
		return 0;
	}

	Fibonacci(num,stack);
	PrintStack(stack);
	printf("\n");

	return 0;
}




