#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

enum
{
	CREATE_PERSON = 1,
	INSERT_PERSON,
	REMOVE_PERSON,
	PRINT,
	DESTROY,
	EXIT
};

void GetUserParams(size_t *_id, char *_name, size_t *_age)
{
	printf("\nplease insert new person details: \n");
	printf("please insert name: ");
	scanf("%s",_name);
	printf("please insert age: ");
	scanf("%lu",_age);
	printf("please insert id: ");
	scanf("%lu",_id);
}

int main()
{
	int action, insertHead;
	size_t id, age, removeKey;
	char name[LENGTH];
	Person *listHead = NULL, *newPerson, *removePerson;

	printf("before we begin, please select how to insert and remove person:\n0 - for inserting and removing person by key");
	printf("\n1 - for inserting and removing person by key in recursion \n2 - for insert and remove from the head \n");
	scanf("%d",&insertHead);

	do
	{
		printf("\nPlease insert the action you want to do:\n");
		printf("1 - for creating new person \n2 - for insert the new person \n");
		printf("3 - for removing a meeting \n4 - for printing the list persons \n");
		printf("5 - for destroying the list \n6 - for exit! \n");
		scanf("%d", &action);
		getchar();

		switch (action)
		{
			case CREATE_PERSON:

				GetUserParams(&id,name,&age);
				newPerson = CreatePerson(id,name,age);

				if(NULL == newPerson)
				{
					printf("\nmemory overflow!\n");
					break;
				}

				printf("\nnew person created!\n");

				break;

			case INSERT_PERSON:

				switch (insertHead)
				{
					case 0:

						listHead = ListInsertByKey(listHead,id,newPerson);
						break;

					case 1:

						listHead = ListInsertByKeyRec(listHead,id,newPerson);
						break;

					default:

						listHead = ListInsertHead(listHead,newPerson);
						break;
				}

				if(NULL == listHead)
				{
					printf("\nno person to insert!\n");
					break;
				}

				printf("\nperson insert!\n");

				break;

			case REMOVE_PERSON:

				switch (insertHead)
				{
					case 0:

						printf("\nplease insert a key:");
						scanf("%lu",&removeKey);

						listHead = ListRemoveByKey(listHead,id,&removePerson);
						break;

					case 1:

						printf("\nplease insert a key:");
						scanf("%lu",&removeKey);

						listHead = ListRemoveByKeyRec(listHead,id,&removePerson);
						break;

					default:

						listHead = RemoveHead(listHead,&removePerson);
						break;
				}

				if(NULL == listHead || NULL == removePerson)
				{
					printf("\nno person to remove\n");
					break;
				}

				printf("\nperson removed! \n");

				break;

			case PRINT:

				PrintListR(listHead);

				break;

			case DESTROY:

				DestroyListR(listHead);
				listHead = NULL;

				break;

			case EXIT:
			
				printf("\nBye Byeee :) \n");
				break;

			default:

				printf("\nyou pressed a wrong button!\n");
				break;
		}


	}while(EXIT != action);

	return 0;
}





