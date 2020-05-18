#include <stdio.h>
#include <string.h>

#include "ui.h"

void PrintCardsArr(Card *_card, int _size)
{
	int i;
	
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
	printf("%d \t",  (_card.m_rank+2));
}

void PrintPlayerDetails(size_t _id, char *_name, size_t _points)
{
	printf("\nid = %ld, name = %s, points = %ld \n", _id, _name, _points);
}

void PlayAnotherHand(int *_anotherHand)
{
	printf("\nthe game is over! if you want to play another hand press 1 else press 0:");
	scanf("%d",_anotherHand);
	printf("\n");
}

void GetReallPlayerName(char *_name)
{
	printf("\nplease enter your name:");
	fgets(_name,sizeof(char),stdin);
	
	strtok(_name, "\n");
	printf("\n");
}

void GetRealPlayerCard(int *_index)
{
	printf("\nplease enter your card's index position:");
	scanf("%d", _index);
	
	printf("\n");
}

void NotValidCard()
{
	printf("\ncard not valid, please select other card\n");

}











