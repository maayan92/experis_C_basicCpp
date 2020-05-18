#ifndef __DECK_H_
#define __DECK_H_

#include "ui.h"

typedef struct Deck Deck;


/*
	Description:
	Input:
	Return Value:
*/
Deck* CreateDeck();

/*
	Description:
	Input:
	Return Value:
*/
void DestroyDeck(Deck *_deck);

/*
	Description:
	Input:
	Return Value:
*/
void FillDeck(Deck *_deck);

/*
	Description:
	Input:
	Return Value:
*/
void mixDeck(Deck *_deck);


int/*TODO*/ RemoveCard(Deck *_deck, Card *_card);


#endif
