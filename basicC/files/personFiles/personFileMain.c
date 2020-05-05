#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "personFile.h"

enum
{
	CREATE = 1,
	PRINT = 2
};

int main()
{
	ErrCode err;
	int action, numOfPerson;

	printf("Please select your action:\n");
	printf("1 - for create file and insert persons\n2 - for printing the list of persons\n");
	scanf("%d",&action);

	switch (action)
	{
		case CREATE:

			if(0 == access("person.txt", F_OK))
			{
				printf("The file is already exist, if you want to overide the file and insert new persons press y: ");
				getchar();

				if('y' != getchar())
				{
					break;
				}
			}

			printf("Please select how many persons you want to enter:");
			scanf("%d", &numOfPerson);

			err = CreatePersons("person.txt",numOfPerson);

			if(ERR_FILE_NOT_OPEN == err)
			{
				printf("File failed to open!\n");
			}

			break;

		case PRINT:

			err = PrintPersons("person.txt");
			
			if(ERR_FILE_NOT_OPEN == err)
			{
				printf("File failed to open!\n");
			}

			break;

		default:

			printf("wrong button!");
			break;
	}

	return 0;
}




