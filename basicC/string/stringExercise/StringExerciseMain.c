#include <stdio.h>
#include "StringExercise.h"

#define WORD_IN_LINE 1
#define REVERSE 2
#define DECIMAL_BINARY 3
#define TRIM_SPACE 4
#define EXIT 5

int main()
{
	char str[LENGTH];
	char type;
	int num, action;

	do
	{
		printf("\nPlease select action: \n");
		printf("for printing each word of the string in a line press 1 \n");
		printf("for reverse the string press 2 \nfor decimal/binary calculation press 3 \n");
		printf("for trimming multiple consecutive in the string press 4 \nor any other button for exit \n");
		scanf("%d", &action);
		getchar();

		switch (action)
		{
			case WORD_IN_LINE:

				printf("Please enter a sentence:");
				fgets(str, sizeof(str), stdin); 

				EachWordInLine(str);

				break;

			case REVERSE:

				printf("Please enter a sentence:");
				fgets(str, sizeof(str), stdin); 

				ReverseStr(str);

				break;

			case DECIMAL_BINARY:

				printf("Please enter a number:");
				scanf("%d", &num);
				getchar();
			
				do
				{
					printf("Please select \'d\' for decimal or \'b\' for binary number:");
					scanf("%c", &type);

					BinaryOrDecimal(num,type);
		
					printf("Please enter a number:");
					scanf("%d", &num);
					getchar();


				}while(0 < num);

				break;

			case TRIM_SPACE:

				printf("Please enter a sentence:");
				fgets(str, sizeof(str), stdin); 

				TrimSpaces(str);

				puts(str);

				break;

			default:

				action = EXIT;
				break;

		}
		
	}while(EXIT != action);

	return 0;
}








