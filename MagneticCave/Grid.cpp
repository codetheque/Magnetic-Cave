#include "Grid.h"
#include <assert.h>
#include <vector>

using namespace std;

Grid::~Grid(void)
{
}

void Grid::reset()
{
	for (int i = 0 ;i < MATRIX_SIZE; ++i)
	{
		grid[i] = Brick_Blank;
	}
	lastMove.x = -1;
	lastMove.y = -1;
}

GridError Grid::move(int x, int y, Brick color)
{
	if (x >= ROWS || y >= COLUMNS)
	{
		return GridError_InvalidPos;
	}

	int pos = getOffset(x,y);

	//Bound checking.
	if (pos < 0 || x >= MATRIX_SIZE)
	{
		return GridError_InvalidPos;
	}

	//Is an empty cell?
	if (isPosAvailable(x,y))
	{
		//Is on the wall ?
		//Does it have a brick of any color directly on my left or right?

		if(isWall(x,y) || hasNeighbour(x,y))
		{
			//If all passes then move is valid.
			cout<< "Moved " << x << "," << y  << endl;
			int pos = getOffset(x,y);
			if (pos >= 0)
			{
				grid[pos] = color;
				lastMove.x = x;
				lastMove.y = y;
				return GridError_Success;
			}
		}
		else
		{
			cout << "**** Invalid Play:\n You need to attach the brick to another brick or a wall. Try again " << endl; 
			return GridError_NowhereToAttach;
		}
	}
	else
	{
		return GridError_Occupied;
	}

	return GridError_Unknown;
}

Winner Grid::getWinner()
{

	int cBlack = 0;
	int cWhite = 0;

	for (int y = 0; y < ROWS ; ++y)
	{
		for (int x = 0; x < COLUMNS; ++x)
		{
			int pos = getOffset(x,y);
			if (pos < 0)
			{
				cout << "Negative position in internal method.";
				assert(false);
				return Winner_None;
			}
			//Same sequence in a row.
			if(grid[pos] == Brick_Black )
			{
				//cout << " Black Brick " << " (" << x << "," << y << ")"<< endl ;
				++cBlack;
				if (cWhite > 0)
				{
					cWhite = 0;
				}

			}
			else if (grid[pos] == Brick_White)
			{
				//cout << " White Brick " << " (" << x << "," << y << ")"<< endl;
				++cWhite;

				if(cBlack > 0)
				{
					cBlack = 0;
				}
			}	
			else
			{

				cBlack = 0;
				cWhite = 0;
			}

			if (cWhite >= ITEMS_TO_WIN)
			{
				return Winner_White;	
			}

			if (cBlack >= ITEMS_TO_WIN)
			{
				return Winner_Black;
			}

		}//end for 
	}

	// checking for COLUMN
	for (int x = 0; x < ROWS ; ++x)
	{
		for (int y = 0; y < COLUMNS; ++y)
		{
			int pos = getOffset(x,y);
			if (pos < 0)
			{
				cout << "negative position in internal method, should never happen!";
				assert(false);
				return Winner_None;
			}

			//Same sequence in a row.
			if (grid[pos] == Brick_Black)
			{
				//cout << " Black Brick " << " (" << x << "," << y << ")"<< endl ;
				++cBlack;

				if (cWhite > 0)
				{
					cWhite = 0;
				}

			}
			else if (grid[pos] == Brick_White)
			{
				//cout << " White Brick " << " (" << x << "," << y << ")"<< endl ;
				++cWhite;
				if(cBlack > 0)
				{
					cBlack = 0;
				}
			}	
			else
			{

				cBlack = 0;
				cWhite = 0;
			}


			if (cWhite >= ITEMS_TO_WIN)
			{
				return Winner_White;	
			}

			if (cBlack >= ITEMS_TO_WIN)
			{
				return Winner_Black;
			}

		}//end for 
	}

	//Checking for diagonal.
	for (int y = 0; y < ROWS; ++y)
	{
		for (int x = 0; x < COLUMNS ; ++x)
		{
			int pos = getOffset(x,y);
			if (pos < 0)
			{
				cout << "negative position in internal method, should never happen!";
				assert(false);
				return Winner_None;
			}

			cWhite=0;
			cBlack=0;

			if (grid[pos] == Brick_White )
			{	
				cWhite=1;
				for (int dd = 0; dd < 4; ++dd) //4 is half way to the end of the board.
				{
					if (x < 4) //After the column E, you cannot win on diagonal to the right.
					{
						pos = pos + ROWS + 1;
					}
					else //But you can win on a diagonal to the left and vice versa.
					{
						pos = pos + ROWS - 1;
					}

					if (pos >= MATRIX_SIZE) //Probably in a for passing half of the matrix, going out of the board.
					{
						break;
					}
					if (grid[pos] == Brick_White)
					{
						cWhite++;
					}
					else
					{
						break;
					}
				}

			}
			else if (grid[pos] == Brick_Black)
			{
				//blacks
				cBlack=1;
				for (int dd = 0; dd < 4; ++dd)
				{
					if (x < 4) //After the column E, you cannot win on diagonal to the right.
					{
						pos = pos + ROWS + 1;
					}
					else //But you can win on a diagonal to the left and vice versa.
					{
						pos = pos + ROWS - 1;
					}

					if (pos >= MATRIX_SIZE)//Probably in  a for passing half of the matrix, going out of the board.
					{
						break; //Quit the diagonal search.
					}
					if (grid[pos] == Brick_Black)
					{
						cBlack++;
					}
					else
					{
						break;
					}
				}

			}//end else 

			if (cWhite >= ITEMS_TO_WIN)
			{
				return Winner_White;	
			}

			if (cBlack >= ITEMS_TO_WIN)
			{
				return Winner_Black;
			}

		}//end for 
	}
	return Winner_None;
}

void Grid::printBoard()
{
	cout << "-------------------- BOARD --------------------" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "Y / X ";

	for (int y = 0; y < 8; ++y)
	{
		cout  << y << "    ";
	}
	cout << endl;

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8 ; ++x)
		{
			int pos = getOffset(x,y);
			if (x == 0 )
			{
				cout << y  << " ||";
			}
			if (grid[pos] == Brick_Black)
			{
				if (lastMove.x == x && lastMove.y == y)
				{
					cout << "+ b +";
				}
				else
				{
					cout << "[ b ]";
				}
			}
			else if (grid[pos] == Brick_White)
			{
				if (lastMove.x == x && lastMove.y == y)
				{

					cout << "+ W +";
				}
				else
				{
					cout << "[ W ]";
				}
			}
			else
			{
				cout << "[   ]";
			}
			if (x == (ROWS - 1))
			{
				cout << " ||";
				//cout << endl;
			}

		}
		cout << endl;
	}
	cout << "-----------------------------------------------" << endl;
}

bool Grid::isPosAvailable(int x, int y)
{
	int pos = getOffset(x,y);
	return (grid[pos] == Brick_Blank);
}

bool Grid::isWall(int x, int y)
{
	//Left wall.
	if(x == 0 && y < ROWS )
	{
		return true;
	}
	//Right wall.
	if(x == (ROWS - 1) && y < COLUMNS)
	{ 
		return true;
	}

	return false;
}

bool Grid::hasNeighbour(int x, int y)
{
	int pos = getOffset(x,y);
	if (pos  < 0)
	{
		return false;
	}
	if (grid[pos-1] != Brick_Blank || grid[pos+1] != Brick_Blank)
	{
		return true;			
	}
	return false;

}

int Grid::getOffset(int x, int y)
{
	if (x > ROWS || y > COLUMNS || x < 0 || y < 0)
	{
		return -1;
	}

	return (ROWS*y)+x;
}

Brick Grid::getBrickAtPos(int x, int y)
{
	int pos = getOffset(x, y);
	if (pos  < 0)
	{
		return Brick_Blank;
	}
	return grid[pos];
}

void Grid::getAllAvailablePositions(std::vector<Point>& positions)
{
	for (int x = 0 ; x < ROWS; ++x)
	{
		for (int y = 0 ; y < COLUMNS; ++y)
		{
			if ((isWall(x,y) || hasNeighbour(x,y)) && isPosAvailable(x, y))
			{
				positions.push_back(Point(x,y));
			}
		}
	}
}

void Grid::getAdjacentPositions(const Point& referencePoint, std::vector<Point>& positions)
{
	if (isPosAvailable(referencePoint.x+1,referencePoint.y))
	{
		positions.push_back(Point(referencePoint.x+1, referencePoint.y));
	}

	if (isPosAvailable(referencePoint.x-1,referencePoint.y))
	{
		positions.push_back(Point(referencePoint.x-1, referencePoint.y));
	}

	if (isPosAvailable(referencePoint.x,referencePoint.y-1))
	{
		positions.push_back(Point(referencePoint.x, referencePoint.y-1));
	}

	if (isPosAvailable(referencePoint.x,referencePoint.y+1))
	{
		positions.push_back(Point(referencePoint.x+1, referencePoint.y+1));
	}
}