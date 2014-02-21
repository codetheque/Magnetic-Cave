
#ifndef AI_PlAYER_H
#define AI_PLAYER_H

#include "Player.h"
#include "Grid.h"
#include <stack>
#include "Minimax.h"
#include "Point.h"

enum Risk
{
	Risk_None,
	Risk_Small,
	Risk_Medium,
	Risk_High,
	Risk_WinTheGame
};

class AIMove
{
public:
	AIMove() : value(-9999), position(-1,-1){}
	Point position;
	int value;
};

class AIPlayer : public Player
{
public:
	AIPlayer(void);
	virtual ~AIPlayer(void);

	virtual void getMove(Grid& grid);

private:

	Brick getOtherPlayerColor();
	Risk checkRisk(Grid& grid, Brick color, int& riskX, int& riskY);

	AIMove findBestMove(Grid& grid);

	int checkForWin(Grid& grid, int x, int y);

	Node* root;

};

#endif