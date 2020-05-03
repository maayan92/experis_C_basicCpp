#include <stdio.h>
#include <string.h>

typedef struct Person
{
	char m_name[30];
	int m_id;
	int m_age;
	int m_education;
}Person;

void swap(Person *_pers1, Person *_pers2)
{
	Person temp = *_pers1;
	*_pers1 = *_pers2;
	*_pers2 = temp;
}

int IsPrime(int _num)
{
	int i = 2;
	
	while(i < _num)
	{
		if(_num%i == 0)
		{
			return 0;
		}
		++i;
	}

	return 1;
}

void SortByID(Person *_person, int _size)
{
	int i, j, swapped = 1;

	for(i = 0;i < _size-1 && swapped;++i)
	{
		swapped = 0;
		for(j = 0;j < _size-i-1;++j)
		{
			if(_person[j].m_id > _person[j+1].m_id)
			{
				swap(&_person[j],&_person[j+1]);
				swapped = 1;
			}
		}
	}
}

void SortByName(Person *_person, int _size)
{
	int i, j , swapped = 1;

	for(i = 0;i < _size-1 && swapped;++i)
	{
		swapped = 0;
		for(j = 0;j < _size-i-1;++j)
		{
			if(0 < strcmp(_person[j].m_name,_person[j+1].m_name))
			{
				swap(&_person[j],&_person[j+1]);
				swapped = 1;
			}
		}
	}
}

void PrintPerson(Person *_person, int _size)
{
	int i;

	for(i = 0;i < _size;++i)
	{
		printf("name: %s, id: %d, age: %d, education: %d \n",_person[i].m_name, _person[i].m_id, _person[i].m_age,_person[i].m_education);
	}
	printf("\n");
}

int main()
{
	int size = 5, num;
	Person person[5] = {{"may",123,27,80},{"yos",256,35,70},{"lia",23,5,100},{"mosh",340,45,60},{"hadar",198,30,90}};

	PrintPerson(person,size);

	SortByName(person,size);

	PrintPerson(person,size);

	SortByID(person,size);
	
	PrintPerson(person,size);

	printf("please insert a number:");
	scanf("%d", &num);

	printf("the number %d is %s \n",num, IsPrime(num) ? "prime" : "not prime");

	return 0;
}









