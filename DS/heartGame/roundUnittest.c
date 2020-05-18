#include <stdio.h>
#include "round.h"



int main()
{
	char *names[4] = {"Mike","Bill","Lisa","you"};
	Round *round = CreateRound(NULL,4,1,100);
	if(!round)
	{
		printf("failed!");
	}
	
	PrintRoundCards(round);
	
	printf("\n");
	PrintRoundCards(round);
	

	return 0;
}
