#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Grid.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

class Game
{
public:

	Game::Game():
    playerTurn(0) {}
	void newGame();
	void play();
	virtual ~Game(void);

private:

	int playerTurn;

	std::vector<Player*> p;
	Grid grid;

};

#endif 