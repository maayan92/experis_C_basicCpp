#ifndef __PLAYERS_H_
#define __PLAYERS_H_

#include "ui.h"

#define LENGTH 50

enum
{
	false,
	true
};

typedef struct Player Player;

/*
	Description: create a new player.
	Input: _name = player's name, _id = player's id, _computerPlayer - says if the player is computer or real.
	Return Value: return pointer to the player, or NULL if the allocation fails.
*/
Player* CreatePlayer(char *_name, size_t _id, size_t _computerPlayer);

/*
	Description: destroy the player.
	Input: _player - pointer to the player.
	Return Value: nothing returns.
*/
void DestroyPlayer(Player *_player);

/*
	Description: set a new number of points to the player.
	Input: _player - pointer to the player, _newPoints - new number of points.
	Return Value: return error code, ERR_NOT_INITIALIZE - if the _player is not exist, SUCCEEDED - on success.
*/
ErrCode SetPoint(Player *_player, size_t _newPoints);

/*
	Description: get the number of points of the _player.
	Input: _player - pointer to the player.
	Return Value: return the number of points.
*/
size_t GetPoint(Player *_player);

/*
	Description: get the number of cards in the _player's hand.
	Input: _player - pointer to the player.
	Return Value: return the number of card in the player's hand.
*/
size_t GetNumOfCards(Player *_player);

/*TODO*/
/*
	Description: set a new number of cards the _player got from loosing in the game.
	Input: _player - pointer to the player, 
	Return Value: return error code, ERR_NOT_INITIALIZE - if the _player is not exist, SUCCEEDED - on success.
*/
ErrCode SetNumOfLostCards(Player *_player, size_t _numOfCards);

/*
	Description: get the number of cards the _player got from loosing in the game.
	Input: _player - pointer to the player.
	Return Value: return the number of lost card in the player's hand.
*/
size_t GetNumOfLostCards(Player *_player);
/*TODO*/

/*
	Description: check if the player is computer or a real player.
	Input: _player - pointer to the player.
	Return Value: return true if the player is computer, false if the player is not exist or if its a real player.
*/
size_t IsComputer(Player *_player);

/*
	Description: create array for holding the cards in the player's hand. 
	Input: _player - pointer to the player, _cardsInitSize - the max number of cards the player can hold.
	Return Value: return error code, ERR_NOT_INITIALIZE - if the _player is not exist, ERR_ALLOCATION_FAILED - if the allocation fails, SUCCEEDED - on success. 
*/
ErrCode CreatePlayerCards(Player *_player, size_t _cardsInitSize);

/*
	Description: set a new card to the _player's hand.
	Input: _player - pointer to the player.
	Return Value: return error code, ERR_NOT_INITIALIZE - if the _player is not exist, ERR_OVERFLOW - if the player's hand if full, SUCCEEDED - on success.
*/
ErrCode SetCard(Player *_player, Card _card);

/*
	Description: remove a card from the player's hand.
	Input: _player - pointer to the player, (*prtStrategy) - pointer to a function that search the position of a card in a specific term, 
		_card - the card to search if needed and gets the removed card.
	Return Value: return error code, ERR_NOT_INITIALIZE - if the _player is not exist, ERR_NOT_EXIST - if there no card in the specific term, SUCCEEDED - on success.
*/
ErrCode RemoveCardByIndex(Player *_player, int(*prtStrategy)(Card*,size_t,Card), Card *_card);

/*
	Description: search if a specific card is exist in the player's hand.
	Input: _player - pointer to the player, (*prtStrategy) - pointer to a function that search the position of a card in a specific term, _card - the to search.
	Return Value: return true if the _card is exist, false if the _player is not exist or if the _card is not exist in the player's hand .
*/
int IsCardExist(Player *_player, int(*prtStrategy)(Card*,size_t,Card), Card *_card);

/*
	Description: sort the cards in the player's hand, by its rank and then by its suite 
	Input: _player - pointer to the player.
	Return Value: return error code, ERR_NOT_INITIALIZE - if the _player is not exist, ERR_ALLOCATION_FAILED - if the allocation fails, SUCCEEDED - on success. 
*/
ErrCode SortCards(Player *_player);

/*
	Description: print the player's details.
	Input: _player - pointer to the player.
	Return Value: nothing returns.
*/
void PrintPlayer(Player *_player);





#endif
