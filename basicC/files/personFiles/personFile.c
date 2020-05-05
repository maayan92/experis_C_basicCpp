#include <stdio.h>
#include <stdlib.h>
#include "personFile.h"

struct person
{
	char firstName[LENGTH];
	char lastName[LENGTH];
	float age;
};

static void InsertPersons(FILE *_file, int _numOfPerson)
{
	int i;

	person *newPerson;

	newPerson = (person*)malloc(sizeof(person));
	
	for(i = 1;i <= _numOfPerson;++i)
	{
		printf("Please enter person %d details \n",i);

		printf("first name: ");
		scanf("%s",newPerson->firstName);

		printf("last name: ");
		scanf("%s",newPerson->lastName);

		printf("age: ");
		scanf("%f", &(newPerson->age));

		fprintf(_file, "%s %s %f\n" , newPerson->firstName, newPerson->lastName, newPerson->age);
	}

	free(newPerson);
	newPerson = NULL;
}

ErrCode CreatePersons(char *_fileName, int _numOfPerson)
{
	
	FILE *_file;

	_file = fopen(_fileName,"w");

	if(NULL == _file)
	{
		return ERR_FILE_NOT_OPEN;
	}

	InsertPersons(_file,_numOfPerson);

	fclose(_file);

	return SUCCEEDED;
}

static void Print(FILE *_file, person *_newPerson)
{
	printf("%-10s %-10s %-10s\n", "First Name", "Last Name", "Age");
	fscanf(_file, "%s%s%f",_newPerson->firstName, _newPerson->lastName, &_newPerson->age);
	
	while(!feof(_file))
	{
		printf("%-10s %-10s %-10f\n",_newPerson->firstName, _newPerson->lastName, _newPerson->age);
		fscanf(_file, "%s%s%f",_newPerson->firstName, _newPerson->lastName, &_newPerson->age);
	}
}

ErrCode PrintPersons(char *_fileName)
{
	
	FILE *_file;
	person *newPerson;

	_file = fopen(_fileName,"r");

	newPerson = (person*)malloc(sizeof(person));

	if(NULL == _file)
	{
		return ERR_FILE_NOT_OPEN;
	}

	Print(_file,newPerson);

	free(newPerson);
	newPerson = NULL;

	fclose(_file);

	return SUCCEEDED;
}




