#include <stdio.h>
#include <stdlib.h>
#include "appointmentDiary.h"

#define CREATE_AD 1
#define CREAT_NEW_MEET 2
#define INSERT_NEW_MEET 3
#define REMOVE_MEET 4
#define SEARCH_MEET 5
#define DESTROY_DIARY 6
#define PRINT_DIARY 7
#define EXIT 8


void GetMeetValues(float *_beginH, float *_endH, size_t *_room)
{
	printf("Please enter begin hour:");
	scanf("%f",_beginH);
	printf("Please enter end hour:");
	scanf("%f",_endH);
	printf("Please enter room:");
	scanf("%lu",_room);
	getchar();
}

void GetAdValues(size_t *_initialSize, size_t *_incremetBlockSize)
{
	printf("Please enter the initial size:");
	scanf("%lu",_initialSize);
	printf("Please enter the incremet block size:");
	scanf("%lu",_incremetBlockSize);	
	getchar();
}

void ChangeMeet(int *_changeNewMeet, meet **newMeet)
{
	printf("There is a new meeting created and not added to the diary, if you want to change her press 1 else press 0:");
	scanf("%d", _changeNewMeet);

	if(*_changeNewMeet)
	{
		*newMeet = NULL;
	}
}

int main()
{
	int action, searchMeet, printAd, changeNewMeet, overideAD;
	size_t initialSize, incremetBlockSize, room;
	float beginH, endH, searchMeetBeginH, removeMeetBeginH;
	ErrCode err;

	AD_t * appointmentDiary = NULL;
	meet *newMeet = NULL;
	printf("Welcome to your Appointment Diary!");

	do 
	{
		printf("\nPlease select action: \nfor creating appointment diary press 1\n");
		if(NULL != appointmentDiary)
		{
			printf("for creating a new meeting press 2 \nfor inserting the new meeting to the diary press 3");
			printf("\nfor removing a meeting from the diary press 4 \nfor searching a meeting in the diary press 5");
			printf("\nfor destroying the appointment diary press 6 \nfor printing the appointment diary press 7\n");
		}
		printf("for exit press 8\n");
		scanf("%d",&action);
		
		switch(action)
		{
			case CREATE_AD:

				if(NULL != appointmentDiary)
				{
					printf("There is an appointment diary exist, if you want to destroy it and create a new one press 1: ");
					scanf("%d",&overideAD);

					if(1 != overideAD)
					{
						break;
					}

					DestroyAD(appointmentDiary);
					appointmentDiary = NULL;
				}

				GetAdValues(&initialSize,&incremetBlockSize);

				appointmentDiary = CreateAD(initialSize,incremetBlockSize);

				if(NULL == appointmentDiary)
				{
					printf("\nMemory overflow or Illegal input in initial size or in incremet block size\n");
					break;
				}
	
				printf("\nAppointment Diary created!\n");
				break;

			case CREAT_NEW_MEET:

				if(NULL != newMeet)
				{
					ChangeMeet(&changeNewMeet,&newMeet);

					if(!changeNewMeet)
					{
						break;
					}
				}

				GetMeetValues(&beginH,&endH,&room);
				err = CreateMeeting(&newMeet,beginH,endH,room);

				switch (err)
				{
					case ERR_ILLEGAL_INPUT:

						printf("\nIllegal input in begin/end hour or in room number!\n");
						break;

					case ERR_OVERFLOW:

						printf("\nMemory overflow!\n");
						break;

					default:

						printf("\nMeeting created!\n");
						break;
				}

				break;

			case INSERT_NEW_MEET:
				
				err = InsertMeet(appointmentDiary,&newMeet);
				newMeet = NULL;

				switch (err)
				{
					case ERR_ILLEGAL_INPUT:

						printf("\nNo meeting to insert!\n");
						break;

					case ERR_NOT_EXIST:

						printf("\nAppointment Diary does not exist!\n");
						break;

					case ERR_OVERLAP:

						printf("\nThere is an overlap with the new meeting please create a new one.\n");
						break;

					case ERR_OVERFLOW:

						printf("\nMemory overflow!\n");
						break;

					default:

						printf("\nNew meeting added to the diary!\n");
						break;
				}

				break;

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

			case EXIT:

				DestroyAD(appointmentDiary);
				appointmentDiary = NULL;

				printf("\nBye Byeeeee :) \n");
				break;

			default:

				printf("\nYou pressed a wrong button!!\n");
				break;
			
		}

	}while(EXIT != action);


	return 0;
}

