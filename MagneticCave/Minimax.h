
#ifndef MINIMAX_H
#define MINIMAX_H
#include "Node.h"

class Minimax
{

public:
	Minimax(){}
	int minmax (Node* n, bool isMax);
	void populateTree(Node* root);

private:
	int internalMinimaxRecursive(Node* node, bool isMax );
	int getRandomValue();

};

#endif
