//#include <tree.hh>
#include "Minimax.h"
#include "Node.h"
#include <iostream>

using namespace std;

int Minimax::minmax (Node* n, bool isMax)
{     
	vector<Node*> child = n->getChild();

	if (child.size() == 0) 
	{
		return n->getValue();
	}
	else if (!isMax) 
	{
		int min = 9999999;

		for (unsigned int i = 0; i < child.size(); ++i)
		{
			if (child[i]->getValue() < min)
			{
				min = child[i]->getValue();
			}	
		}
		return min;
	}
	else
	{
		int max = -9999999;

		for (unsigned int i = 0; i < child.size(); ++i)
		{
			if (child[i]->getValue() > max)
			{
				max= child[i]->getValue();
			}	
		}
		return max;
	}
}

void Minimax::populateTree(Node* node )
{
	bool max = false;
	internalMinimaxRecursive(node, max);

}

int Minimax::internalMinimaxRecursive(Node* node, bool isMax )
{
	isMax = !isMax;
	std::vector<Node*> child = node->getChild();

	int currValue;

	//cout << "max ? "<< isMax << endl;
	if (isMax)
		currValue = -9999999;
	else
		currValue = 9999999;

	if (child.size())
	{

		for (unsigned int i = 0; i < child.size(); ++i)
		{
			int value = internalMinimaxRecursive(child[i], isMax);
			if (isMax && value > currValue) 
			{
				currValue = value;
				//cout << "Is Max" << endl;
			}
			else
			{ 
				if (!isMax && value < currValue)
				{
					currValue = value;
					//cout << "! Is max" << endl;
				}
			}
		}
	}
	else
	{
		currValue = getRandomValue();
	}
	//std::cout << " currValue " << currValue << endl;
	if (isMax)
	{
		node->setMinMaxType(eMinMaxType_Max);
	}
	else
	{

		node->setMinMaxType(eMinMaxType_Min);
	}
	node->setValue(currValue);
	return currValue;

}

int valChanger = 0;
int Minimax::getRandomValue()
{
	return (int) ((rand()/(float)RAND_MAX) * 10) + valChanger++;
}