#ifndef __UI_H_
#define __UI_H_

#include "card.h"
#include "ADTErrors.h"

/*
	Description: get a name input from the real player.
	Input:
	Return Value: nothing returns.
*/
void GetReallPlayerName(char *_name);

/*
	Description: print the player's name;
	Input:
	Return Value: nothing returns.
*/
void PrintPlayerName(char *_name);

/*
	Description: print the player's points.
	Input:
	Return Value: nothing returns.
*/
void PrintPlayerPoints(size_t _points);

/*
	Description: print a card array.
	Input: _card - card arra, _size - size of array.
	Return Value: nothing returns.
*/
void PrintCardsArr(Card *_card, int _size);

/*
	Description: print the card.
	Input:
	Return Value: nothing returns.
*/
void PrintCard(Card _card);

/*
	Description: print a message to choose the _n card to transfer.
	Input:
	Return Value: nothing returns.
*/
void PrintChoose3Cards(int _n);

/*
	Description: get a card input from a real player. 
	Input:
	Return Value: nothing returns.
*/
void GetRealPlayerCard(size_t *_suite, size_t *_rank);

/*
	Description: print a message that the card is not valid.
	Input:
	Return Value: nothing returns.
*/
void NotValidCard();

/*
	Description: print the winner of the round/game.
	Input: _roundNum - number of the round,_isEndGame - is the game ended or not.
	Return Value: nothing returns.
*/
void PrintWinner(int _roundNum, int _isEndGame);

/*
	Description: print message that the round/game is over.
	Input: _endGame - is the game ended or not, _anotherHand - pointer to the choice if to play another hand/game.
	Return Value: nothing returns.
*/
void PrintAnotherHand(int _endGame, int *_anotherHand);



#endif
