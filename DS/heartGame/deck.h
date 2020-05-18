#ifndef __DECK_H_
#define __DECK_H_

#include "ui.h"

typedef struct Deck Deck;


/*
	Description: create a new deck.
	Input: 
	Return Value: return a pointer to the deck, or NULL if the allocation fails;
*/
Deck* CreateDeck();

/*
	Description: destroy the deck.
	Input: _deck - pointer to the deck.
	Return Value: nothing returns.
*/
void DestroyDeck(Deck *_deck);

/*
	Description: fill the deck.
	Input: _deck - pointer to the deck.
	Return Value: nothing returns.
*/
void FillDeck(Deck *_deck);

/*
	Description: mix the deck.
	Input: _deck - pointer to the deck.
	Return Value: nothing returns.
*/
void mixDeck(Deck *_deck);

/*
	Description: remove a card from the end of the deck.
	Input: _deck - pointer to the deck, _card - pointer to the removed card.
	Return Value: return error code, ERR_NOT_INITIALIZE - if the deck is not exist, SUCCEEDED - on success.
*/
ErrCode RemoveCard(Deck *_deck, Card *_card);


#endif
