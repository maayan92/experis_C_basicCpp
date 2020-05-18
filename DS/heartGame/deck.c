#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

struct Deck
{
	Card *m_cards;
	size_t m_numOfCards;
};

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
		return NULL;
	}
	
	return deck;
}

void DestroyDeck(Deck *_deck)
{
	if(_deck)
	{	
		free(_deck);
	}
}

void FillDeck(Deck *_deck)
{
	int suite = 0, rank, i = 0;
	
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

static void Swap(Deck *_deck, size_t _i, size_t _j)
{
	Card temp = _deck->m_cards[_i];
	_deck->m_cards[_i] = _deck->m_cards[_j];
	_deck->m_cards[_j] = temp;
}

void mixDeck(Deck *_deck)
{
	int i, index;
	time_t t;
	
	srand((unsigned)time(&t));

	for(i = 0;i < _deck->m_numOfCards;++i)
	{
		index = rand()%(_deck->m_numOfCards);
		Swap(_deck,i,index);
	}
}

int/*TODO*/ RemoveCard(Deck *_deck, Card *_card)
{	
	if(!_deck)
	{
		return 0;
	}
	
	*_card = _deck->m_cards[--_deck->m_numOfCards];
	return 1;
}

/*
size_t GetCardId(Deck *_card) / (_card->m_suite) * (_card->m_number) /
{
}

ErrCode InsertByIndex(Deck *_card, size_t _index)
{
}

size_t GetNumOfElements(Deck *_deck)
{
}

*/












