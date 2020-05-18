#include <stdio.h>
#include <string.h>

#include "ui.h"

void GetReallPlayerName(char *_name)
{
	int choose;
	
	printf("if you want to choose a name please press 1 else press 0:");
	scanf("%d", &choose);
	getchar();
		
	if(choose)
	{
		printf("\nplease enter your name:");
		scanf("%s", _name);
		getchar();
		
	}
}

void PrintPlayerName(char *_name)
{
	printf("\nname = %s \n", _name);
}

void PrintPlayerPoints(size_t _points)
{
	printf("points = %ld \n", _points);
}

void PrintCardsArr(Card *_card, int _size)
{
	int i;
	
	printf("\n");
	
	for(i = 0;i < _size;++i)
	{
		PrintCard(_card[i]);
	}
	
	printf("\n");
}

void PrintCard(Card _card)
{
	switch(_card.m_suite)
	{
		case HEART:
			printf("\xE2\x99\xA5 ");
			break;
		
		case LEAF:
			printf("\xE2\x99\xA0 ");
			break;
			
		case DIAMOND:
			printf("\xE2\x99\xA6 ");
			break;
			
		default:
			printf("\xE2\x99\xA3 ");
			break;
	}
	
	switch(_card.m_rank)
	{
		case PRINCE:
			printf("PRINCE ");
			break;
		
		case QUEEN:
			printf("QUEEN ");
			break;
			
		case KING:
			printf("KING ");
			break;
			
		case AS:
			printf("AS ");
			break;
				
		default:
			printf("%d ",  (_card.m_rank+2));
			break;
	}
}

void PrintChoose3Cards(int _n)
{
	printf("\nplease select card number %d to pass \n", _n);
}

void GetRealPlayerCard(size_t *_suite, size_t *_rank)
{
	char ch;
	
	printf("\nplease enter your card:\n");
	
	printf("\nplease enter suite:");
	scanf("%lu", _suite);
	printf("\nplease enter rank:");
	scanf("%lu", _rank);
	
	while((ch = getchar()) != '\n' && ch != EOF );
	
	printf("\n");
}

void NotValidCard()
{
	printf("\ncard not valid, please select other card\n");

}

void PrintWinner(int _roundNum, int _isEndGame)
{

	if(_isEndGame)
	{
		printf("------ wins the game ------\n\n");
	}
	else
	{		
		printf("------ wins hand %d ------ \n\n", _roundNum + 1);
	}

}

void PrintAnotherHand(int _endGame, int *_anotherHand)
{
	printf("\nthe game is over! if you want to play another %s press 1 else press 0:", (_endGame) ? "game" : "hand");
	scanf("%d",_anotherHand);
	printf("\n");
}




