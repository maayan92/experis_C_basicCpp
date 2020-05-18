#ifndef __HEART_GAME_H_
#define __HEART_GAME_H_

typedef struct Game Game;

/*
	Description: create a new game.
	Input: _names - the players name, _numOfComputerPlayers - number of computer players, _numOfRealPlayers - number of real players,
		_numOfDecks - number of decks, _maxPoints - the max number of points you can reach until the game is over.
	Return Value: return pointer to the game, or NULL if the allocation fails.
*/
Game* CreateGame(char **_names, size_t _numOfComputerPlayers, size_t _numOfRealPlayers, size_t _numOfDecks, int _maxPoints);

/*
	Description: destroy the game, destroy the players.
	Input: _game - pointer to the game.
	Return Value: nothig returns.
*/
void DestroyGame(Game *_game);

/*
	Description: start the game.
	Input: _game - pointer to the game.
	Return Value: nothing returns.
*/
void StartGame(Game *_game);

#endif
