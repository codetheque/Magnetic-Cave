/*

  Concordia University
  Intro to AI - Fall 2012.

  Aline Czarnobai

  Deliverables:
  Minimax, and manual play - 12/11/2012.
  Minimax, heuristics, and UI. 27/11/2012.
   
*/
#include <iostream>
#include "Node.h"
#include "TreeHelper.h"
#include "Minimax.h"
#include "Board.h"
#include "Grid.h"
#include "Player.h"
#include "Game.h"

using namespace std;
TreeHelper helper;


//Game settings.
bool startBoardAsMax = true;//Should the board root node be min or max?
int depth = 3;//Depth limit for the minimax 

//Tree layout.
int treeDepth = 3;
int numChildPerNodes = 16;//Number of children per node.

//Debug
bool printOriginalTree = false;//Print the original tree.
bool printTreeAfterMinMax = false;//Print the tree after after running the minimax algorithm.


int main()
{
	/*
	cout<< "\n\n ----------- MINIMAX ---------- \n" <<endl  ;
	cout<< endl;

	Node* root = new Node();
	root->setValue(1);
	root->setParent(nullptr);

	helper.addChildRecursive(root, numChildPerNodes, treeDepth);

	//std::vector<Node*>& nodes = helper.getLevelToNodesMap()[1];
	if (printOriginalTree)
	{
		cout<< "\n------------ Original Tree ----------------\n" <<endl  ;
		helper.printTree(root);
		cout<< "\n-------------------------------------------\n\n" <<endl  ;
	}
	//helper.printNodesAtLevel(3);

	Minimax minimax;
	minimax.populateTree(root);

	if (printTreeAfterMinMax)
	{
		cout<< "\n------------ Tree after Minimax -----------\n" <<endl;
		helper.printTree(root);
		cout<< "\n-------------------------------------------\n\n" <<endl;
	}

	Board board(startBoardAsMax);
	board.setDepth(depth);
	board.setRoot(root);

	while (board.move() == continueGame)
	{ 
		cout << "(- moving -) " <<  endl;
	}
	
	*/

	Grid grid;

	bool res = false;
	
	cout<< "Welcome to the Magnetic Cave!" << endl;

	Game game1;
	game1.newGame();
	game1.play();

	getchar();	
	getchar();

	return 0;

}