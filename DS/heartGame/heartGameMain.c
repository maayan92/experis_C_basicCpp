#include <stdio.h>
#include "heartGame.h"


int main()
{
	char *names[4] = {"Mike","Bill","Lisa","you"};
	int numOfComputerPlayers = 4, numOfRealPlayers = 0;
	
	Game *game = CreateGame(names,numOfComputerPlayers,numOfRealPlayers,1,100);
	if(!game)
	{
		printf("failed!");
	}
	
	StartGame(game);
	
	printf("\n");
	

	return 0;
}
