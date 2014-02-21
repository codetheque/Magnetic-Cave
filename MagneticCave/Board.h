#ifndef BOARD_H
#define BOARD_H

#define BOARD_H
#include <vector>
#include "Node.h"


enum GameState{

	gameOver,
	noMoreAction,
	continueGame,
	newGame
};

class Board
{

public:
	Board(bool isMax);

	GameState move();
	void setDepth(int depth_p);
	void setRoot(Node* root);

	int getScore();
	void setScore(int score);

private:

	int score;
	Node* root;
	Node* current;
	bool isCurrentMax;
	int currentDepth;
	int finalDepth;
	GameState state;

};

#endif
