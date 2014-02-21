#ifndef GRID_H
#define GRID_H

#include <iostream>
#include "Point.h"
#include <vector>

enum Brick
{
	Brick_Black,
	Brick_White,
	Brick_Blank
};

enum Winner
{
	Winner_White,
	Winner_Black,
	Winner_None,
	Winner_Tie
};


enum GridError
{
	GridError_InvalidPos,
	GridError_NowhereToAttach,
	GridError_Occupied,
	GridError_Success,
	GridError_Unknown
};

#define ROWS 8
#define COLUMNS 8
#define MATRIX_SIZE 64

#define ITEMS_TO_WIN 5

class Grid
{
public:
	Grid(void)
	{
		reset();
	}

	virtual ~Grid(void);

	void reset();
	GridError move(int x, int y, Brick color);

	Winner getWinner();
	void printBoard();

	bool isPosAvailable(int x, int y);

	Brick getBrickAtPos(int x, int y);

	Point& getLastMove() { return lastMove; }

	void getAllAvailablePositions(std::vector<Point>& positions);
	void getAdjacentPositions(const Point& referencePoint, std::vector<Point>& positions);
	
private:

	//Board setting.
	bool isWall(int x, int y);
	bool hasNeighbour(int x, int y);
	int getOffset(int x, int y);

	//Transposed matrix.
	Brick grid[ROWS*COLUMNS];

	Point lastMove;

};

#endif
