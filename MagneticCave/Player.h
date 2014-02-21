#ifndef PLAYER_H
#define PLAYER_H

#include "Grid.h"
#include <iostream>

class Player
{
public:
	Player()
	{
	
	}

	virtual ~Player(void);
	Brick getColor();

	void setColor(Brick c);
	virtual void getMove(Grid& grid);

	Point& getPlayPosition()
	{
		return playPosition;
	}
	

protected:
	
	Brick color;
	Point playPosition;

};

#endif// PLAYER_H