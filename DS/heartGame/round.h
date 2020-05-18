#ifndef __ROUDN_H_
#define __ROUDN_H_

#include "player.h"

typedef struct Round Round;


/*
	Description: create a new round.
	Input: _players - players array, _numOfPlayers - the number of players in the game, _numOfDecks - number of decks (in this game its 1), 
		_maxPoints - the max number of points you can reach until the game is over.
	Return Value: return pointer to the round.
*/
Round* CreateRound(Player **_players, size_t _numOfPlayers, size_t _numOfDecks, int _maxPoints);

/*
	Description: starts a new round.
	Input: _round - pointer to the round.
	Return Value: nothing returns.
*/
void StartRound(Round *_round);

/*
	Description: destroy the _round.
	Input: _round - pointer to the round.
	Return Value: nothing returns.
*/
void DestroyRound(Round *_round);


#endif
