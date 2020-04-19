#include <stdio.h>
#include <stdlib.h>
#include "diaryFile.h"

enum
{
	REMOVE_MEET = 1,
	SEARCH_MEET = 2,
	DESTROY_DIARY = 3,
	PRINT_DIARY = 4,
	EXIT = 5
};

void GetAdValues(size_t *_initialSize, size_t *_incremetBlockSize)
{
	printf("Please enter the initial size:");
	scanf("%lu",_initialSize);
	printf("Please enter the incremet block size:");
	scanf("%lu",_incremetBlockSize);	
	getchar();
}

int main()
{
	AD_t * appointmentDiary;
	ErrCode err;
	size_t initialSize, incremetBlockSize;
	int action, searchMeet, printAd;
	float searchMeetBeginH, removeMeetBeginH;

	err = StoreMeet("meetingFile.txt");

	if(ERR_FILE_NOT_OPEN == err)
	{
		printf("File failed to open!\n");
	}
	
	else if(FILE_NOT_EMPTY == err)
	{
		GetAdValues(&initialSize,&incremetBlockSize);

		err = LoadMeet("meetingFile.txt",&appointmentDiary,initialSize,incremetBlockSize);

		switch (err)
		{
			case ERR_FILE_NOT_OPEN:

				printf("File failed to open!\n");
				break;

			case OVERFLOW_OR_ILLEGAL_INPUT:

				printf("\nMemory overflow or Illegal input in initial size or in incremet block size\n");
				break;

			case ERR_OVERFLOW:

				printf("\nMemory overflow!\n");
				break;

			default:

				printf("\nAppointment diary created and all meetings with no overflow was inserted to the diary!\n");
				break;
		}

		do
		{
			printf("\nPlease select action: \n");
			printf("\nfor removing a meeting from the diary press 1 \nfor searching a meeting in the diary press 2");
			printf("\nfor destroying the appointment diary press 3 \nfor printing the appointment diary press 4\n");
			printf("for exit press any other button\n");
			scanf("%d",&action);

			switch(action)
			{
				case REMOVE_MEET:

					printf("Please insert begin hour:");
					scanf("%f",&removeMeetBeginH);
				
					err = RemoveMeet(appointmentDiary,removeMeetBeginH);
	
					switch (err)
					{
						case ERR_ILLEGAL_INPUT:

							printf("\nIllegal input in begin hour!\n");
							break;

						case ERR_NOT_EXIST:

							printf("\nAppointment Diary does not exist!\n");
							break;

						case ERR_FAILED:

							printf("\nMeeting not exist!\n");
							break;

						default:

							printf("\nMeeting removed!\n");
							break;
					}

					break;

				case SEARCH_MEET:

					printf("Please insert begin hour:");
					scanf("%f",&searchMeetBeginH);

					searchMeet = FindMeet(appointmentDiary,searchMeetBeginH);

					switch (searchMeet)
					{
						case ERR_NOT_EXIST:

							printf("\nAppointment Diary does not exist!\n");
							break;

						case ERR_FAILED:

							printf("\nMeeting not exist!\n");
							break;

						default:

							printf("\nMeeting number %d \n",searchMeet);
							break;
					}
					
					break;

				case DESTROY_DIARY:

					DestroyAD(appointmentDiary);
					appointmentDiary = NULL;

					printf("\nAppointment diary destroyed! \n");
					
					break;
				
				case PRINT_DIARY:

					printAd = PrintAD(appointmentDiary);
		
					if(ERR_NOT_EXIST == printAd)
					{
						printf("\nAppointment Diary does not exist!\n");
						break;
					}

					else if(ERR_FAILED == printAd)
					{
						printf("\nSome of the meetings failed on printing!\n");
					}
					
					break;

				default:

					action = EXIT;

					DestroyAD(appointmentDiary);
					appointmentDiary = NULL;

					printf("\nBye Byeeeee :) \n");
					break;
				
			}


		}while(EXIT != action);
		
	}


	return 0;
}
