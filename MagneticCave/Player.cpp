#include "Player.h"
#include <iostream>

using namespace std;

Player::~Player(void)
{
}

Brick Player::getColor()
{
	return color;
}

void  Player::setColor(Brick c)
{
	color = c;
}

void  Player::getMove(Grid& grid)
{
	//Grid is not used for non-ai player 

	//Reset the current value, just in case.
	playPosition.x = -1;
	playPosition.y = -1;
	cin.clear(); //Reset the error output.
	cin.sync(); //Aync the input buffer to clean buffers.

	cout<< "Enter x:" << endl;
	cin >> playPosition.x;

	cout<< "Enter y:" << endl;
	cin.clear();
	cin >> playPosition.y;
}
