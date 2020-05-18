#include <stdio.h>
#include <stdlib.h>
#include "round.h"
#include "deck.h"

enum
{
	ROUND_MAGIC_NUMBER = 0x0000BBBB,
	DECKS_NUM = 1,
	TRANFER_CARDS = 3,
	PLAYERS_NUM = 4,
	TABLE_CARDS_NUM = 4,
	NUM_OF_CARDS = 52,
	PLAYER_NUM_OF_CARDS = 13
};

#define IS_NOT_EXIST(_round) (!_round || _round->m_magicNumber != ROUND_MAGIC_NUMBER)

struct Round
{
	size_t m_magicNumber;
	Card *m_tableCards;
	size_t m_numOfTCards;
	Deck *m_decks;
	Player **m_players;
	size_t m_numOfRound;
	int m_maxPoints;
	int m_loser;
	int m_heartUsed;
};

/* BUILD THE ROUND */
/*create the players cards array*/
static void CreatePlayers(Round *_round);
/*set cards to start a new round*/
static void PlayNewHand(Round *_round);
/*Hand new cards to the players*/
static void HandCards(Round *_round);
/*get 3 cards from the players and divide them*/
static void TransferCards(Round *_round);
/*divide the 3 cards by the round number*/
static void SetCardsByRound(Round *_round, Card _tranfer[][TRANFER_CARDS]);
/*divide the 3 cards to the players*/
static void DivideCardsToPlayers(Round *_round, Card _tranfer[][TRANFER_CARDS], int _trasferTo);

/*find the max rank card of the suitable suite*/
static int FindTableMax(Card *_cardsArr, int _size, Card *_card);
/*find who start the current round*/
static int FindWhoStart(Round *_round);
/*get card to the table when there is already cards on the table*/
static int GetCardNotFirst(Round *_round, Player *_player);
/*get the first card to the table*/
static int GetCardFirst(Round *_round, Player *_player);
/*set the card to the table next position*/
static int SetCardToTable(Round *_round, Card _card);
/*get a card from the next player to the table*/
static void GetCardToTable(Round *_round, Player *_player);

/*get card from the real player*/
static void GetCardFromRealP(Round *_round, Player *_player);
/*check validation of the real player's card*/
static int RealPlayerCardValid(Round *_round, Player *_player, Card _card);
/*get card index position from the playre*/
static int GetCardFromRealPlayer(Card *_cardsArr, size_t _size, Card _card);
/*check if there is a card with the same suite of _card in the _cardsArr*/
static int checkIfsuiteExist(Card *_cardsArr, size_t _size, Card _card);
/*check if the player have a card that is not with HEART suite*/
static int IfHasCardNotHeart(Card *_cardsArr, size_t _size, Card _card);

/*strategy*/
/*get the max card*/
static int GetMaxCard(Card *_cardsArr, size_t _size, Card _maxCard);
/*find the smallest card from position _i*/
static int FindSmallestCard(Card *_cardsArr, size_t _size, Card _minCard, int _i);
/*get the smallest card*/
static int GetSmallestCard(Card *_cards, size_t _size, Card _card);
/*get the smallest card, not HEART if HEART wasn't put on the table yet*/
static int GetSmallestNotHeart(Card *_cardsArr, size_t _size, Card _minCard);
/*get the same card as _card*/
static int GetSpecificCard(Card *_cardsArr, size_t _size, Card _card);
/*get the card with QUEEN suite and the biggest rank*/
static int GetBigHeartCard(Card *_cardsArr, size_t _size, Card _card);
/*get card position that it's rank is smaller than the _card rank*/
static int FindOneLess(Card *_cardsArr, size_t _size, Card _card, int _index);
/*get a suitable card position of the _card suite*/
static int GetCardBySuite(Card *_cardsArr, size_t _size, Card _card);
/*strategy*/

/*set the table cards with points to the loser player*/
static void SetLostCardsPoints(Round *_round, Card _lostCards[][NUM_OF_RANKS+1], int _loserPlayer);
/*set the players num of lost cards to zero*/
static void RemovePlayersLostCards(Round *_round);

/*print the palyers*/
static void PrintAllPlayers(Round *_round);
/*print the game, the table cards, the players details and the real player's hand*/
static void PrintGame(Round *_round);

/* create a new round */

Round* CreateRound(Player **_players, size_t _numOfPlayers, size_t _numOfDecks, int _maxPoints)
{
	Round *round = (Round*)malloc(sizeof(Round));
	if(!round)
	{
		return NULL;
	}

	round->m_maxPoints = _maxPoints;
	round->m_loser = -1;
	round->m_heartUsed = 0;
	round->m_numOfRound = 0;
	round->m_numOfTCards = 0;
	round->m_tableCards = (Card*)malloc(TABLE_CARDS_NUM*sizeof(Card));
	round->m_players = _players;
	round->m_magicNumber = ROUND_MAGIC_NUMBER;
	
	CreatePlayers(round);

	round->m_decks = CreateDeck(NUM_OF_CARDS);
	if(!(round->m_decks))
	{
		return NULL;
	}
	
	return round;
}

void DestroyRound(Round *_round)
{
	if(!IS_NOT_EXIST(_round))
	{
		DestroyDeck(_round->m_decks);
		
		_round->m_magicNumber = 0;
		free(_round);
	}
}

/*Start a new round*/

void StartRound(Round *_round)
{
	int i, startPlayer, playAnotherHand;
	Card card;
	Card lostCards[PLAYERS_NUM][NUM_OF_RANKS+1];
	
	if(IS_NOT_EXIST(_round))
	{
		return;
	}

	PlayNewHand(_round);
	
	do
	{
		startPlayer = (-1 != _round->m_loser) ? _round->m_loser : FindWhoStart(_round);
		
		for(i = 0;i < PLAYERS_NUM;++i)
		{
			GetCardToTable(_round,_round->m_players[startPlayer%PLAYERS_NUM]);
			++startPlayer;
		}
		PrintGame(_round);
		
		_round->m_loser = (FindTableMax(_round->m_tableCards,_round->m_numOfTCards,&card) + startPlayer) % PLAYERS_NUM;
		
		SetLostCardsPoints(_round,lostCards,_round->m_loser);
		
		_round->m_numOfTCards = 0;
		
	}while(GetNumOfCards(_round->m_players[startPlayer%PLAYERS_NUM]));
	
	++_round->m_numOfRound;
	_round->m_loser = -1;
	_round->m_heartUsed = 0;
	RemovePlayersLostCards(_round);
	
	PlayAnotherHand(&playAnotherHand);
	if(playAnotherHand)
	{
		StartRound(_round);
	}
}

/* SUB FUNCTIOS */

/* Play a new hand */

static void CreatePlayers(Round *_round)
{
	int i;
	
	for(i = 0;i < PLAYERS_NUM;++i)
	{
		CreatePlayerCards(_round->m_players[i],PLAYER_NUM_OF_CARDS);
	}
}

static void PlayNewHand(Round *_round)
{	
	FillDeck(_round->m_decks);
	mixDeck(_round->m_decks);

	HandCards(_round);
	PrintAllPlayers(_round);
	
	TransferCards(_round);
	PrintAllPlayers(_round);	
}

static int FindWhoStart(Round *_round)
{
	int isExist = 0, i = 0;
	Card card = {CLOVER,TWO};
	
	do
	{
		isExist = IsCardExist(_round->m_players[i],GetSpecificCard,&card);
		++i;
		
	}while(!isExist);
	
	return (i-1);
}

static void HandCards(Round *_round)
{
	int i, j;
	Card card;

	for(i = 0;i < PLAYERS_NUM;++i)
	{
		for(j = 0;j < PLAYER_NUM_OF_CARDS;++j)
		{
			if(RemoveCard(_round->m_decks,&card))
			{
				SetCard(_round->m_players[i],card);
			}	
		}
		SortCards(_round->m_players[i]);
	}
}

/* Tranfer 3 cards */

static void DivideCardsToPlayers(Round *_round, Card _tranfer[][TRANFER_CARDS], int _trasferTo)
{
	int i, j;
	
	for(i = 0;i < PLAYERS_NUM;++i)
	{
		for(j = 0;j < TRANFER_CARDS;++j)
		{
			SetCard(_round->m_players[(i+_trasferTo)%PLAYERS_NUM],_tranfer[i][j]);
		}
		SortCards(_round->m_players[(i+_trasferTo)%PLAYERS_NUM]);
	}
}

static void SetCardsByRound(Round *_round, Card _tranfer[][TRANFER_CARDS])
{
	switch(_round->m_numOfRound % PLAYERS_NUM)
	{
		case 0:
			DivideCardsToPlayers(_round,_tranfer,1);
			break;
			
		case 1:
		
			DivideCardsToPlayers(_round,_tranfer,3);
			break;
			
		default:
		
			DivideCardsToPlayers(_round,_tranfer,2);
			break;
	}
}

static void TransferCards(Round *_round)
{
	Card tranfer[PLAYERS_NUM][TRANFER_CARDS], card = {0,0};
	int i, j;

	if(3 == (_round->m_numOfRound % PLAYERS_NUM))
	{
		return;
	}
	
	for(i = 0;i < PLAYERS_NUM;++i)
	{
		for(j = 0;j < TRANFER_CARDS;++j)
		{
			(!IsComputer(_round->m_players[i])) ? RemoveCardByIndex(_round->m_players[i],GetCardFromRealPlayer,&card) : RemoveCardByIndex(_round->m_players[i],GetMaxCard,&card);
			
			tranfer[i][j] = card;
		}
	}

	SetCardsByRound(_round,tranfer);
}

/* Get new card from the player */

static int SetCardToTable(Round *_round, Card _card)
{
	_round->m_tableCards[(_round->m_numOfTCards)++] = _card;
	
	if(_card.m_suite == HEART)
	{
		_round->m_heartUsed = 1;
	}
	
	return 1;
}

static int GetCardNotFirst(Round *_round, Player *_player)
{
	Card card;
	
	/*smaler same suite*/
	FindTableMax(_round->m_tableCards,_round->m_numOfTCards,&card);
	
	if(SUCCEEDED == RemoveCardByIndex(_player,GetCardBySuite,&card))
	{
		return SetCardToTable(_round,card);
	}
	
	/*leaf queen*/
	card.m_suite = LEAF;
	card. m_rank = QUEEN;
	
	if(SUCCEEDED == RemoveCardByIndex(_player,GetSpecificCard,&card))
	{
		return SetCardToTable(_round,card);
	}
	
	/*big heart*/
	card.m_suite = HEART;
	card. m_rank = NUM_OF_RANKS;

	if(SUCCEEDED == RemoveCardByIndex(_player,GetBigHeartCard,&card))
	{
		return SetCardToTable(_round,card);
	}
	
	return 0;
}

static int GetCardFirst(Round *_round, Player *_player)
{
	Card card = {CLOVER,TWO};
	
	if((-1 == _round->m_loser) && (SUCCEEDED == RemoveCardByIndex(_player,GetSpecificCard,&card)))
	{
		return SetCardToTable(_round,card);
	}
	
	if(!_round->m_heartUsed && (SUCCEEDED == RemoveCardByIndex(_player,GetSmallestNotHeart,&card)))
	{
		return SetCardToTable(_round,card);
	}
	
	return 0;
}

static void GetCardToTable(Round *_round, Player *_player)
{
	Card card;
	int(*ptrStrategy)(Card*,size_t,Card);
	
	if(!IsComputer(_player))
	{
		GetCardFromRealP(_round,_player);
		return;
	}
	
	if(0 == _round->m_numOfTCards)
	{
		if(GetCardFirst(_round,_player))
		{
			return;
		}
	}

	else
	{
		if(GetCardNotFirst(_round,_player))
		{
			return;
		}
	}
	
	/*max/min card*/

	ptrStrategy = (0 == _round->m_numOfTCards) ? &GetSmallestCard : &GetMaxCard;
	RemoveCardByIndex(_player,ptrStrategy,&card);
	_round->m_tableCards[(_round->m_numOfTCards)++] = card;
			
}

/* real player's card */

static void GetCardFromRealP(Round *_round, Player *_player)
{
	Card card;

	while(!IsCardExist(_player,GetCardFromRealPlayer,&card) || !RealPlayerCardValid(_round,_player,card))
	{
		NotValidCard();
	}
		
	RemoveCardByIndex(_player,GetSpecificCard,&card);
	
	SetCardToTable(_round,card);
}

static int RealPlayerCardValid(Round *_round, Player *_player, Card _card)
{
	Card tablCard = _round->m_tableCards[0];
	Card cloverTCard = {CLOVER,TWO};
	
	if((-1 == _round->m_loser) && IsCardExist(_player,GetSpecificCard,&cloverTCard))
	{
		if(CLOVER == _card.m_suite && TWO == _card.m_rank)
		{
			return 1;
		}
		
		return 0;
	}
	
	if(0 != _round->m_numOfTCards)
	{
		if(_card.m_suite != _round->m_tableCards[0].m_suite)
		{
			if(IsCardExist(_player,checkIfsuiteExist,&tablCard))
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
			
	if(_card.m_suite == HEART && !_round->m_heartUsed && IsCardExist(_player,IfHasCardNotHeart,&_card))
	{
		return 0;
	}
	
	return 1;
}

static int GetCardFromRealPlayer(Card *_cardsArr, size_t _size, Card _card)
{
	int index = -1;
	
	GetRealPlayerCard(&index);

	return (index >= 0 && index < _size) ? index : -1;
}

static int checkIfsuiteExist(Card *_cardsArr, size_t _size, Card _card)
{
	int i;
	
	for(i = 0;i < _size;++i)
	{
		if(_card.m_suite == _cardsArr[i].m_suite)
		{
			return 1;
		}
	}
	
	return -1;
}

static int IfHasCardNotHeart(Card *_cardsArr, size_t _size, Card _card)
{
	int i = GetBigHeartCard(_cardsArr,_size,_card);
	
	return ((++i) == _size) ? -1 : i;
}

/* */

/* strategy */

static int FindTableMax(Card *_cardsArr, int _size, Card *_card)
{
	int i, index = 0;
	(*_card) = _cardsArr[0];
	
	for(i = 1;i < _size;++i)
	{
		if((*_card).m_suite == _cardsArr[i].m_suite && (*_card).m_rank < _cardsArr[i].m_rank)
		{
			(*_card) = _cardsArr[i];
			index = i;
		}
	}
	
	return index;
}

static int GetMaxCard(Card *_cardsArr, size_t _size, Card _maxCard)
{
	int i = 0, index = -1;
	_maxCard = _cardsArr[0];

	while(i < _size)
	{
		if(_maxCard.m_rank <= _cardsArr[i].m_rank)
		{
			_maxCard = _cardsArr[i];
			index = i;
		}
		
		++i;
	}
	
	return index;
}

static int FindSmallestCard(Card *_cardsArr, size_t _size, Card _minCard, int _i)
{
	int index = _i;
	_minCard = _cardsArr[index];

	while(_i < _size)
	{
		if(_minCard.m_rank > _cardsArr[_i].m_rank)
		{
			_minCard = _cardsArr[_i];
			index = _i;
		}
		
		++_i;
	}
	
	return index;
}

static int GetSmallestCard(Card *_cardsArr, size_t _size, Card _minCard)
{
	int i = 1, index;

	index = FindSmallestCard(_cardsArr,_size,_cardsArr[0],i);

	return (-1 == index) ? 0 : index;
}

static int GetSmallestNotHeart(Card *_cardsArr, size_t _size, Card _card)
{
	int i = 0;
	
	while(i < _size && (HEART == _cardsArr[i].m_suite))
	{
		++i;
	}
	
	return (i == _size) ? -1 : FindSmallestCard(_cardsArr,_size,_card,i);
}

static int GetSpecificCard(Card *_cardsArr, size_t _size, Card _card)
{
	int i;
	
	for(i = 0;i < _size;++i)
	{
		if(_card.m_suite == _cardsArr[i].m_suite && _card.m_rank == _cardsArr[i].m_rank)
		{
			return i;
		}
	}
	
	return -1;
}

static int GetBigHeartCard(Card *_cardsArr, size_t _size, Card _card)
{
	int i = 0;
	
	while(i < _size && HEART == _cardsArr[i].m_suite)
	{
		++i;
	}
	
	return i-1;
}

static int FindOneLess(Card *_cardsArr, size_t _size, Card _card, int _index)
{

	while(_index < _size && _card.m_suite == _cardsArr[_index].m_suite && _card.m_rank > _cardsArr[_index].m_rank)
	{
		++_index;
	}
	
	return (_index-1);
}

static int GetCardBySuite(Card *_cardsArr, size_t _size, Card _card)
{
	int i = 0;
	
	while(i < _size && _card.m_suite != _cardsArr[i].m_suite)
	{
		++i;
	}
	
	if(i == _size)
	{
		return -1;
	}

	if(_cardsArr[i].m_rank < _card.m_rank)
	{
		return FindOneLess(_cardsArr,_size,_card,i);
	}
	
	return i;
}

/* set table cards to loser */

static void RemovePlayersLostCards(Round *_round)
{
	int i;
	
	for(i = 0;i < PLAYERS_NUM;++i)
	{
		SetNumOfLostCards(_round->m_players[i],0);
	}
}

static void SetLostCardsPoints(Round *_round, Card _lostCards[][NUM_OF_RANKS+1], int _loserPlayer)
{
	int i, size = GetNumOfLostCards(_round->m_players[_loserPlayer]);
	
	for(i = 0;i < TABLE_CARDS_NUM;++i)
	{
		if(HEART == _round->m_tableCards[i].m_suite || (LEAF == _round->m_tableCards[i].m_suite && QUEEN == _round->m_tableCards[i].m_rank))
		{
			SetPoint(_round->m_players[_loserPlayer], (HEART == _round->m_tableCards[i].m_suite) ? 1 : 13);
			_lostCards[_loserPlayer][size++] = _round->m_tableCards[i];
		}
	}
	
	SetNumOfLostCards(_round->m_players[_loserPlayer],size);
}

/* Print players */

static void PrintAllPlayers(Round *_round)
{
	int i;
	
	for(i = 0;i < PLAYERS_NUM;++i)
	{
		PrintPlayer(_round->m_players[i]);
	}
}

static void PrintGame(Round *_round)
{
	PrintAllPlayers(_round);
	
	PrintCardsArr(_round->m_tableCards,_round->m_numOfTCards);

}











