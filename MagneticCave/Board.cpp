#include "Board.h"
#include <iostream>

//root = MAX
Board::Board(bool isMax)
	:score(0), root(nullptr), current(nullptr), isCurrentMax(isMax), currentDepth(0), finalDepth(0), state(newGame)
{}
void Board::setRoot(Node* root_p)
{
	root = root_p;
	current = root;
}
void Board::setDepth(int depth_p)
{
	finalDepth= depth_p;
}

GameState Board::move()
{
	std::vector<Node*> children =  current->getChild();

	std::cout << "\n\n-> current node: " << current->getValue() << std::endl; 

	if (children.size() == 0)
	{
		return noMoreAction;
	}

	currentDepth++;

	if (isCurrentMax)
	{
		std::cout << ">> checking  MAX " << std::endl;
		Node* nodeMaxValue= children[0];
		std::cout << ">>  MAX  ? " << children[0]->getValue()  << std::endl;
		for (unsigned int i = 1; i < children.size(); ++i)
		{  
			std::cout << ">> MAX ? " << children[i]->getValue() << std::endl; 		
			if(children[i]->getValue() > nodeMaxValue->getValue())
			{
				nodeMaxValue = children[i]; 
			}
		}
		current= nodeMaxValue;
		std::cout << ">> going to MAX node: " << current->getValue() << std::endl; 			
	}
	else
	{
		std::cout << ">> checking  MIN " << std::endl;
		Node* nodeMinValue = children[0];
		std::cout << ">>  MIN ? " << children[0]->getValue()  << std::endl;
		for (unsigned int i = 1; i < children.size(); ++i)
		{  
			std::cout << ">>  MIN ? " << current->getValue() << std::endl; 
			if (children[i]->getValue() < nodeMinValue->getValue())
			{
				nodeMinValue = children[i]; 
			}
		}

		current = nodeMinValue;
		std::cout << ">> going to  MIN node: " << current->getValue() << std::endl; 
	}
	isCurrentMax = !isCurrentMax;

	if (finalDepth == currentDepth)
		return gameOver;
	else 
		return continueGame;
}
