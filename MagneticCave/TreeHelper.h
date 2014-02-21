#ifndef TREE_HELPER_H
#define TREE_HELPER_H

#include "Node.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class TreeHelper
{
public:
	TreeHelper(void);
	~TreeHelper(void);

	void printNodesAtLevel(int level);
	void printTree(Node* rootNode);


	void addChildRecursive(Node* n, int number, int maxDepth);

	std::map<int, std::vector<Node*> >& getLevelToNodesMap();

private:

	void formatPrintNode(Node* node, int depth);
	void formatPrintTraverseNode(Node* node, int depth);
	void internalAddChildRecursive(Node* n, int number, int currDepth, int maxDepth);


	std::map<int, std::vector<Node*> > levelToNodesMap;
};

#endif