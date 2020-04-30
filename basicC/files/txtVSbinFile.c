#include <stdio.h>
#include <stdlib.h>

typedef struct Person
{
	char m_name[30];
	int m_id;
	int m_age;
	int m_education;
}Person;

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

Result WriteToTxt(Person *_person, int _size, char *_filename)
{
	FILE *file;
	int i = 0;

	file = fopen(_filename, "w");

	if(NULL == file)
	{
		return FAILED;
	}

	while(i < _size)
	{
		fprintf(file, "%s %d %d %d\n" , _person[i].m_name, _person[i].m_id, _person[i].m_age, _person[i].m_education);
		++i;
	}

	fclose(file);
	return SUCCEDD;
}

Person* ReadFromTxt(int _size, char *_filename)
{
	FILE *file;
	int i = 0;
	Person *person;

	file = fopen(_filename, "r");
	if(NULL == file)
	{
		return NULL;
	}
	
	person = (Person *)malloc(_size*sizeof(Person));
	if(NULL == person)
	{
		return NULL;
	}

	while(!feof(file))
	{
		fscanf(file, "%s%d%d%d\n" , person[i].m_name, &person[i].m_id, &person[i].m_age, &person[i].m_education);
		++i;
	}

	fclose(file);

	return person;
}

Result WriteToBin(Person *_person, int _size, char *_filename)
{
	FILE *file;
	size_t res;

	file = fopen(_filename, "w");
	if(NULL == file)
	{
		return FAILED;
	}

	res = fwrite(_person,sizeof(Person),_size,file);

	if(res < _size)
	{
		return FAILED;
	}

	fclose(file);

	return SUCCEDD;
}

Person* ReadFromBin(int _size, char *_filename)
{
	FILE *file;
	size_t res;
	Person *person;

	file = fopen(_filename, "r");
	if(NULL == file)
	{
		return NULL;
	}

	person = (Person *)malloc(_size*sizeof(Person));
	if(NULL == person)
	{
		return NULL;
	}

	res = fread(person,sizeof(Person),_size,file);

	if(res < _size)
	{
		return NULL;
	}

	fclose(file);

	return person;
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
	int size = 5;
	Result res;
	char fileTxtName[] = "persons.txt", fileBinName[] = "persons.bin";
	Person *personOutTxt, *personOutBin, personIn[5] = {{"may",123,27,80},{"yos",256,35,70},{"lia",23,5,100},{"mosh",340,45,60},{"hadar",198,30,90}};

	PrintPerson(personIn,size);

	printf("Text file: \n");

	res = WriteToTxt(personIn, size, fileTxtName);
	if(FAILED == res)
	{
		printf("failed to write to file %s \n", fileTxtName);
	}

	personOutTxt = ReadFromTxt(size,fileTxtName);
	PrintPerson(personOutTxt,size);

	printf("Binary file: \n");

	res = WriteToBin(personIn,size,fileBinName);
	if(FAILED == res)
	{
		printf("failed to write to file %s \n", fileBinName);
	}

	personOutBin = ReadFromBin(size,fileBinName);

	PrintPerson(personOutBin,size);
	

	return 0;
}












