#include "AIPlayer.h"
#include "TreeHelper.h"

#include <vector>

AIPlayer::AIPlayer(void)
{
	/*
	for (int row = 0; row < ROWS; ++row)
	{
		wallPositions.push(Point(row, 0)); //the last item 
		wallPositions.push(Point(row, COLUMNS-1)); //the last item 
	}
	*/
}

AIPlayer::~AIPlayer(void)
{
	delete root;
}

void AIPlayer::getMove(Grid& grid)
{
	bool shouldAttack = true;
	//Check if we are in risk of losing and block the opponent.
	int riskX, riskY;
	Risk risk = checkRisk(grid, getOtherPlayerColor(), riskX, riskY); 
	//Before this, have to check if the risk of losing is smaller than the risk of wining.

	//Use heuristics later we may take more risk.
	switch(risk)
	{ 
		case Risk_Medium:
		case Risk_High:
		case Risk_WinTheGame:
		{
			playPosition.x = riskX;
			playPosition.y  = riskY;
			//shouldAttack = false; //we gotta defend!
		}
		break;
	}

	//Else try playing using the minimax algorithm.
	if (shouldAttack)
	{
		AIMove move = findBestMove(grid);
		playPosition = move.position;
	}
}

Brick AIPlayer::getOtherPlayerColor()
{
	if (getColor() == Brick_White)
	{
		return Brick_Black;
	}
	else
	{
		return Brick_White;
	}
}

AIMove AIPlayer::findBestMove(Grid& grid)
{
	AIMove bestMove;
	TreeHelper helper;

	std::vector<Point> availablePositions;
	std::vector<Point> adjacent;

	grid.getAllAvailablePositions(availablePositions);

	//Run the minmax for all of them.
	for (unsigned int i = 0; i < availablePositions.size(); ++i)
	{
		Minimax minimax;

		Point p = availablePositions[i];
		grid.getAdjacentPositions(p, adjacent);

		int win = checkForWin(grid, p.x, p.y); 

		//Create root node for the minimax.
		Node root;

		//The number of children for this node is equal to the number of adjacent nodes.
		root.addChild(adjacent.size());
		root.setValue(win);
		root.setParent(nullptr);

		//For each adjacent node.
		std::vector<Node*>& nodes = root.getChild();
		for (unsigned int n = 0; n < nodes.size() ; ++n)
		{
			//Set value to -1, assuming the other player will play in that position.
			nodes[n]->setValue(-1); //first level we assume is bad because the player will block our game.

			//Check for 2nd level adjacency.
			//Not for each first level adjacent node, get the adjacent nodes to that and build the second level.
			//So we can try to predict if its going to be good or not.
			Point pa2nd = adjacent[n];
			std::vector<Point> adjacent2nd;
			grid.getAdjacentPositions(pa2nd, adjacent2nd);

			//Add the number of children equal to the number of adjacent nodes.
			nodes[n]->addChild(adjacent2nd.size());
			std::vector<Node*>& secondLevel = nodes[n]->getChild();
			for (unsigned int l2 = 0; l2 < secondLevel.size() ; ++l2)
			{
				//int winWin = checkForWin(grid, adjacent2nd[l2].x, adjacent2nd[l2].y);
				//give it the weight of victory
				secondLevel[l2]->setValue(1); 
			}

			//Run the minimax.
			minimax.minmax(&root, true);

			int value = root.getValue();
			if (bestMove.value < value)
			{
				bestMove.value = value;
				bestMove.position = p;
			}
		}
		adjacent.clear();
	}

	return bestMove;
}

Risk AIPlayer::checkRisk(Grid& grid, Brick color, int& riskX, int& riskY)
{

	int vertical = 0;
	int horizontal = 0;
	int diagonal = 0;
	//Store the dangerous next positon to play.
	//Danger positions in vertical.
	int xv = 0;
	int yv = 0;
	//Danger in horizontal.
	int xh = 0;
	int yh = 0;
	//Danger in diagonal.
	int xd = 0;
	int yd = 0;

	for(int y = 0; y < COLUMNS ; ++y)
	{
		int currVertical = 0;//We can only win if all are in the same row, each time we change row it resets.
		for(int x = 0; x < ROWS; ++x)
		{
			//Same sequence in a row
			if(grid.getBrickAtPos(x, y) == color )
			{
				++currVertical;
				xv = x+1; //Next vertical position is dangerous
				yv = y;

				if (yv >= COLUMNS)
				{
					currVertical = 0;
				}
			}
		}

		if (currVertical > vertical)
		{
			vertical = currVertical;
		}
	}

	for(int x= 0; x < ROWS ; ++x)
	{
		int currHorizontal = 0; //We can only win if all are in the same line, each time we change line it resets.
		for(int y = 0; y < COLUMNS; ++y)
		{
			//Same sequence in a row.
			if(grid.getBrickAtPos(x, y) == color )
			{
				++currHorizontal;
				xh = x; //Next horizontal position is dangerous.
				yh = y+1;
				if (xh >= ROWS)
				{
					currHorizontal = 0;//The dangerous play is outside of the board.
				}
			}
		}
		if (currHorizontal > horizontal)
		{
			horizontal = currHorizontal ;
		}
	}

	int risky = horizontal;//Take one as possible then check against other.
	riskX = xh;
	riskY = yh;
	if (risky < vertical)
	{
		risky = vertical;
		riskX = xv;
		riskY = yv;
	}
	if (risky < diagonal)
	{
		risky = diagonal;
		riskX = xd;
		riskY = yd;
	}
	Risk risk;
	if (risky >= Risk_WinTheGame)
	{
		risk = Risk_WinTheGame;
	}
	else
	{
		risk = (Risk) risky;
	}

	return risk;
}

int AIPlayer::checkForWin(Grid& grid, int x, int y)
{

	int vertical = 0;
	int horizontal = 0;
	int diagonal = 0;


	for(int yy = 0; yy < COLUMNS ; ++yy)
	{
		//Same sequence in a row.
		if (grid.getBrickAtPos(x, yy) == getColor())
		{
			++vertical;
		}
		else if (grid.getBrickAtPos(x, yy) == getOtherPlayerColor())
		{
			vertical = 0;
		}
	}

	// Checking for COLUMN.
	for(int xx = 0; xx < ROWS ; ++xx)
	{
		//Same sequence in a row.
		if(grid.getBrickAtPos(xx, y) == getColor() )
		{
			++horizontal;
		}
		else if(grid.getBrickAtPos(xx, y) == getOtherPlayerColor() )
		{
			horizontal = 0;
		}
	}

	/////////////////////////////////////////////////////////////////
	//checking for diagonal
	/*int dir = 0;
	if (x < 4) //after the column E, you cannot win on diagonal to the right
	{
	dir =  1;
	for (int dd = 0; dd < 4; ++dd)
	{
	//same as y = y + COLUMNS + 1 or y = y + COLUMNS -1 
	y = y + COLUMNS + dir;

	if (grid.getBrickAtPos(x, y) == getColor() )
	{
	++diagonal;
	}
	}
	}
	else // but you can win on a diagonal to the left and vice versa
	{
	dir = - 1;
	}*/

	int risky = horizontal;//Take one as possible then check against other.
	if (risky < vertical)
	{
		risky = vertical;
	}
	if (risky < diagonal)
	{
		risky = diagonal;
	}

	return risky;
}