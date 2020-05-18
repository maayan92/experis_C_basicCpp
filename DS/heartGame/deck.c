#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

#define DECK_MAGIC_NUMBER 0x0000CCCC
#define IS_NOT_EXIST(_deck) (!_deck || _deck->m_magicNumber != DECK_MAGIC_NUMBER)

struct Deck
{
	size_t m_magicNumber;
	Card *m_cards;
	size_t m_numOfCards;
};

/*swap cards*/
static void Swap(Deck *_deck, size_t _i, size_t _j);

Deck* CreateDeck(int _numOfCards)
{
	Deck *deck = (Deck*)malloc(sizeof(Deck));
	if(!deck)
	{
		return NULL;
	}

	deck->m_numOfCards = _numOfCards;
	
	deck->m_cards = (Card*)malloc(sizeof(Card)*(_numOfCards));
	if(!(deck->m_cards))
	{
		free(deck);
		return NULL;
	}
	
	deck->m_magicNumber = DECK_MAGIC_NUMBER;
	
	return deck;
}

void DestroyDeck(Deck *_deck)
{
	if(!IS_NOT_EXIST(_deck))
	{	
		_deck->m_magicNumber = 0;
		free(_deck);
	}
}

void FillDeck(Deck *_deck)
{
	int suite = 0, rank, i = 0;
	
	if(IS_NOT_EXIST(_deck))
	{
		return;
	}
	
	while(suite < NUM_OF_SUITES)
	{
		rank = 0;
		while(rank < NUM_OF_RANKS)
		{
			_deck->m_cards[i].m_suite = suite;
			_deck->m_cards[i++].m_rank = rank;
			
			rank++;
		}
		
		suite++;
	}
	
	_deck->m_numOfCards = i;
}

void mixDeck(Deck *_deck)
{
	int i, index;
	time_t t;
	
	if(IS_NOT_EXIST(_deck))
	{
		return;
	}
	
	srand((unsigned)time(&t));

	for(i = 0;i < _deck->m_numOfCards;++i)
	{
		index = rand()%(_deck->m_numOfCards);
		Swap(_deck,i,index);
	}
}

ErrCode RemoveCard(Deck *_deck, Card *_card)
{	
	if(IS_NOT_EXIST(_deck))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	*_card = _deck->m_cards[--_deck->m_numOfCards];
	
	return SUCCEEDED;
}

/* SUB FUNCTION */

static void Swap(Deck *_deck, size_t _i, size_t _j)
{
	Card temp = _deck->m_cards[_i];
	_deck->m_cards[_i] = _deck->m_cards[_j];
	_deck->m_cards[_j] = temp;
}










