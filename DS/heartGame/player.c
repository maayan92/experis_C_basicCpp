#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

#define PLAYER_MAGIC_NUMBER 0x0000DDDD

#define IS_NOT_EXIST(_player) (!_player || _player->m_magicNumber != PLAYER_MAGIC_NUMBER)
#define SWAP(_cards,_i,_j) { Card temp = _cards[_i];  _cards[_i] = _cards[_j]; _cards[_j] = temp; }

struct Player
{
	size_t m_magicNumber;
	size_t m_id;
	char m_name[LENGTH];
	size_t m_points;
	Card *m_cards;
	size_t m_cardsInitSize;
	size_t m_numOfCards;
	size_t m_computerPlayer;
	size_t m_numOfLostCards;
};
 
/*Sort*/
/*fill the player cards*/
static void FillCards(Player *_player, Card *_arr);
/*pull value from array to the player's hand*/
static ErrCode PullFromArrToPlayer(Player *_player, int *_arr, int _minValue, int _maxValue, int(*ptrFun)(Card));
/*fill the array and sum it up*/
static void FillAndSum(Player *_player, int *_arr, int _minValue, int _maxValue, int(*ptrFun)(Card));
/*Sort*/

/*remove the card in position _index*/
static void RemoveTheCard(Player *_player, int _index);


Player* CreatePlayer(char *_name, size_t _id, size_t _computerPlayer)
{
	Player *player = (Player*)malloc(sizeof(Player));
	if(NULL == player)
	{
		return NULL;
	}
	
	strcpy(player->m_name,_name);
	player->m_id = _id;
	player->m_points = 0;
	player->m_numOfCards = 0;
	player->m_cardsInitSize = 0;
	player->m_numOfLostCards = 0;
	player->m_computerPlayer = _computerPlayer;
	
	if(!player->m_computerPlayer)
	{
		GetReallPlayerName(player->m_name);
	}

	player->m_cards = NULL;
	player->m_magicNumber = PLAYER_MAGIC_NUMBER;
	
	return player;
}

void DestroyPlayer(Player *_player)
{
	if(!IS_NOT_EXIST(_player))
	{
		if(_player->m_cards)
		{
			free(_player->m_cards);
		}
		
		_player->m_magicNumber = 0;
		free(_player);
	}
}

char* GetName(Player *_player)
{
	return _player->m_name;
}

ErrCode SetPoints(Player *_player, size_t _newPoints)
{
	if(IS_NOT_EXIST(_player))
	{
		return ERR_NOT_INITIALIZE;
	}

	_player->m_points = _newPoints;
	
	return SUCCEEDED;
}

size_t GetPoints(Player *_player)
{
	if(IS_NOT_EXIST(_player))
	{
		return 0;
	}

	return _player->m_points;
}

size_t GetNumOfCards(Player *_player)
{
	if(IS_NOT_EXIST(_player))
	{
		return 0;
	}

	return _player->m_numOfCards;
}

size_t IsComputer(Player *_player)
{
	if(IS_NOT_EXIST(_player))
	{
		return false;
	}

	return _player->m_computerPlayer;
}

ErrCode CreatePlayerCards(Player *_player, size_t _cardsInitSize)
{
	if(IS_NOT_EXIST(_player))
	{
		return ERR_NOT_INITIALIZE;
	}
	_player->m_cardsInitSize = _cardsInitSize;
	
	_player->m_cards = (Card*)malloc(sizeof(Card)*_cardsInitSize);
	if(!(_player->m_cards))
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	return SUCCEEDED;
}

ErrCode SetCard(Player *_player, Card _card)
{
	if(IS_NOT_EXIST(_player))
	{
		return ERR_NOT_INITIALIZE;
	}

	if(_player->m_numOfCards == _player->m_cardsInitSize)
	{
		return ERR_OVERFLOW;
	}

	_player->m_cards[(_player->m_numOfCards)++] = _card;

	return SUCCEEDED;
}

ErrCode RemoveCardByIndex(Player *_player, int(*prtStrategy)(Card*,size_t,Card), Card *_card)
{	
	int index;
	
	if(IS_NOT_EXIST(_player))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	index = (*prtStrategy)(_player->m_cards,_player->m_numOfCards,*_card);
	if(-1 == index)
	{
		return ERR_NOT_EXIST;
	}	
	
	*_card = _player->m_cards[index];
	
	RemoveTheCard(_player,index);

	return SUCCEEDED;
}

int IsCardExist(Player *_player, int(*prtStrategy)(Card*,size_t,Card), Card *_card)
{
	int index;
	
	if(IS_NOT_EXIST(_player))
	{
		return false;
	}
	
	index = (*prtStrategy)(_player->m_cards,_player->m_numOfCards,*_card);

	if(-1 == index)
	{
		return false;
	}
	
	*_card = _player->m_cards[index];
	
	return true;
}

/* SORT */

ErrCode CountingSortAlgo(Player *_player, int _minValue, int _maxValue, int(*ptrFun)(Card))
{
	int *arr = (int*)calloc((_maxValue - _minValue)+1,sizeof(int));

	if(IS_NOT_EXIST(_player))
	{
		return ERR_NOT_INITIALIZE;
	}

	if(NULL == arr)
	{
		return ERR_ALLOCATION_FAILED;
	}	

	FillAndSum(_player,arr,_minValue,_maxValue,ptrFun);
	
	return PullFromArrToPlayer(_player,arr,_minValue,_maxValue,ptrFun);
}

/*Print player*/

void PrintPlayer(Player *_player)
{	
	PrintPlayerName(_player->m_name);
	
	PrintPlayerPoints(_player->m_points);
}

void PrintPlayerCards(Player *_player)
{	
	PrintCardsArr(_player->m_cards,_player->m_numOfCards);
}


/* SUB FUNCTIONS */

/*sort functions*/

static void FillCards(Player *_player, Card *_arr)
{
	int i;
	
	for(i = 0;i < _player->m_numOfCards;++i)
	{
		_player->m_cards[i] = _arr[i];
	}
}

static ErrCode PullFromArrToPlayer(Player *_player, int *_arr, int _minValue, int _maxValue, int(*ptrFun)(Card))
{
	int i = (_player->m_numOfCards)-1;
	Card *tempArr;

	tempArr = (Card*)calloc((_player->m_numOfCards)+1,sizeof(Card));
	if(NULL == tempArr)
	{
		return ERR_ALLOCATION_FAILED;
	}

	while(i >= 0)
	{
		tempArr[--_arr[(*ptrFun)(_player->m_cards[i])]] = _player->m_cards[i];
		--i;
	}

	FillCards(_player,tempArr);

	free(_arr);
	free(tempArr);
	return SUCCEEDED;
}

static void FillAndSum(Player *_player, int *_arr, int _minValue, int _maxValue, int(*ptrFun)(Card))
{
	int i = 0;

	while(i < _player->m_numOfCards)
	{
		++_arr[(*ptrFun)(_player->m_cards[i++])];
	}

	for(i = 1;i <= (_maxValue - _minValue);++i)
	{
		_arr[i] = _arr[i] + _arr[i-1];
	}

}

/* remove card from the array */

static void RemoveTheCard(Player *_player, int _index)
{
	while(_index < _player->m_numOfCards-1)
	{
		SWAP(_player->m_cards,_index,_index+1);
		++_index;
	}
	
	--(_player->m_numOfCards);
}






