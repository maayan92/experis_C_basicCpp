#include <stdio.h>
#include "createFile.h"

enum
{
	FIRST_N = 1,
	LAST_N = 2,
	COMPARE = 3,
	WORD_OCCUR = 4,
	EXIT = 5
};

int main()
{
	size_t numOfLines;
	int action, numOfOccur;
	char ch[LENGTH];
	ErrCode err;

	do
	{
		printf("Please select action: \n");
		printf("1 - for printing the first n lines\n2 - for printing the last n lines\n");
		printf("3 - for comparing two files \n4 - for the number of occurrences of a specific word \n");
		printf("or any other button for exit\n");
		scanf("%d", &action);

		switch(action)
		{

			case FIRST_N:

				printf("Please select how many first lines you want to print:");
				scanf("%lu", &numOfLines);
				err = PrintFirstN(numOfLines,"clients.txt");
		
				if(ERR_FILE_NOT_OPEN == err)
				{
					printf("File failed to open!");
					break;
				}

				else if(ILLEGAL_INPUT == err)
				{
					printf("Illegal input in numOfLines or in file name");
					break;
				}

				printf("\n");

				break;

			case LAST_N:

				printf("Please select how many last lines you want to print:");
				scanf("%lu", &numOfLines);
				getchar();
				err = PrintLastN(numOfLines,"clients.txt");

				if(ERR_FILE_NOT_OPEN == err)
				{
					printf("File failed to open!");
					break;
				}

				else if(ILLEGAL_INPUT == err)
				{
					printf("Illegal input in numOfLines or in file name");
					break;
				}

				printf("\n");

				break;

			case COMPARE:

				err = CompareFiles("clients.txt","clients2.txt");
				
				if(ERR_FILE_NOT_OPEN == err)
				{
					printf("File failed to open!");
					break;
				}
				
				printf("\n");

				break;

			case WORD_OCCUR:

				printf("Please insert a word:");
				scanf("%s",ch);

				numOfOccur = NumOfOccurrences(ch,"clients.txt");

				if(ERR_FILE_NOT_OPEN == numOfOccur)
				{
					printf("File failed to open!");
					break;
				}

				printf("The number of occurrences of the word %s is %d \n", ch,numOfOccur);

				break;

			default:

				action = EXIT;

				break;

		}

	
	}while(EXIT != action);

	return 0;
}



