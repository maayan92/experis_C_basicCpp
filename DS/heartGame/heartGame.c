#include <stdio.h>
#include <stdlib.h>
#include "heartGame.h"
#include "round.h"

#define GAME_MAGIC_NUMBER 0x0000AAAA
#define IS_NOT_EXIST(_game) (!_game || _game->m_magicNumber != GAME_MAGIC_NUMBER)

struct Game
{
	size_t m_magicNumber;
	Player **m_players;
	Round *m_round;
	size_t m_numOfPlayers;
};

/*create the players by there type (computer or real)*/
static Player** CreatePlayersByType(Player **_players, char **_names, size_t _size, int *_index, size_t _computerPlayer);
/*create the players*/
static Player** CreateAllPlayers(char **_names, size_t _size, size_t _numOfComputerPlayers);
/*destroy the players*/
static void DestroyAllPlayers(Game *_game);

/* create a new game */

Game* CreateGame(char **_names, size_t _numOfComputerPlayers, size_t _numOfRealPlayers, size_t _numOfDecks, int _maxPoints)
{	
	Game *game = (Game*)malloc(sizeof(Game));
	if(!game)
	{
		return NULL;
	}
	
	CreateLog("heartGame.log");

	game->m_numOfPlayers = _numOfComputerPlayers + _numOfRealPlayers;
	game->m_magicNumber = GAME_MAGIC_NUMBER;
		
	if(!(game->m_players = CreateAllPlayers(_names,game->m_numOfPlayers,_numOfComputerPlayers)))
	{
		CloseLog();
		free(game);
		return NULL;
	}

	game->m_round = CreateRound(game->m_players,game->m_numOfPlayers,_numOfDecks,_maxPoints);
	if(!(game->m_round))
	{
		DestroyGame(game);
		return NULL;
	}
	
	
	return game;
}

void DestroyGame(Game *_game)
{
	if(!IS_NOT_EXIST(_game))
	{
		DestroyAllPlayers(_game);
		DestroyRound(_game->m_round);
		
		_game->m_magicNumber = 0;
		free(_game);
		
		CloseLog();
	}
}

/* start the game */

void StartGame(Game *_game)
{
	if(!IS_NOT_EXIST(_game))
	{
	
		StartRound(_game->m_round);
		
		DestroyGame(_game);	
	}
}


/* SUB FUNCTIONS */

/* create the players */

static Player** CreatePlayersByType(Player **_players, char **_names, size_t _size, int *_index, size_t _computerPlayer)
{
	
	while((*_index) < _size)
	{
		_players[(*_index)] = CreatePlayer(_names[(*_index)],(*_index),_computerPlayer);
		if(!(_players[(*_index)]))
		{
			return NULL;
		}
		
		++(*_index);
	}	
	
	return _players;
}

static Player** CreateAllPlayers(char **_names, size_t _size, size_t _numOfComputerPlayers)
{
	int i = 0;
	Player **players;
	
	players = (Player**)malloc(_size*sizeof(Player*));
	if(!(players))
	{
		return NULL;
	}
	
	if(!CreatePlayersByType(players,_names,_numOfComputerPlayers,&i,1))
	{
		return NULL;
	}
	
	if(!CreatePlayersByType(players,_names,_size,&i,0))
	{
		return NULL;
	}
	
	return players;
}

static void DestroyAllPlayers(Game *_game)
{
	int i;
	
	for(i = 0;i < _game->m_numOfPlayers;++i)
	{
		if(_game->m_players[i])
		{
			DestroyPlayer(_game->m_players[i]);
		}
	}	
}












