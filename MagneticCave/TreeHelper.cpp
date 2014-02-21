#include "TreeHelper.h"

TreeHelper::TreeHelper(void)
{
}


TreeHelper::~TreeHelper(void)
{
}

void TreeHelper::printNodesAtLevel(int level)
{
	cout << "Nodes at level " << level  << " are: " << endl;
	std::vector<Node*>& nodes = getLevelToNodesMap()[level];
	for (unsigned int i = 0; i < nodes.size(); ++i)
	{
		cout << nodes[i]->getValue() << endl;
	}
}

void TreeHelper::printTree(Node* rootNode)
{
	cout << "(" << rootNode->getValue()  << ") d:" << 0;
	if (rootNode->getMinMaxType() == eMinMaxType_Max)
		cout << " Max ";
	else if (rootNode->getMinMaxType() == eMinMaxType_Min)
		cout << " Min ";
	formatPrintTraverseNode(rootNode, 0);
}

void TreeHelper::addChildRecursive(Node* n, int number, int maxDepth)
{
	internalAddChildRecursive(n, number, 0 , maxDepth);
}

std::map<int, std::vector<Node*> >& TreeHelper::getLevelToNodesMap()
{
	return levelToNodesMap;
}

void TreeHelper::formatPrintNode(Node* node, int depth)
{
	int td = (depth * 2) - 2; //-2 to remove the |_ spacing and * depth because we have to add twice the number of spaces.
	for (int d = 0; d < td ; ++d)
	{
		cout << " ";
	}
	cout << "|_";
	cout << "(" << node->getValue()  << ") d:" << depth;
	if (node->getMinMaxType() == eMinMaxType_Max)
		cout << " Max ";
	else if (node->getMinMaxType() == eMinMaxType_Min)
		cout << " Min ";
}

void TreeHelper::formatPrintTraverseNode(Node* node, int depth)
{
	++depth;
	std::vector<Node*> nodes = node->getChild();
	unsigned int size = nodes.size();
	for (unsigned int i = 0; i < size ; ++i)
	{
		cout << "\n";
		formatPrintNode(nodes[i], depth);
		formatPrintTraverseNode(nodes[i], depth);
	}
}

void TreeHelper::internalAddChildRecursive(Node* n, int number, int currDepth, int maxDepth)
{
	if (currDepth  >= maxDepth)
		return;
	++currDepth;

	for (int i = 0; i < number; i++)
	{
		Node* child = new Node();

		child->setValue(-1);

		//Add the child of this level.
		levelToNodesMap[currDepth].push_back(child);

		n->addChild(child);
		internalAddChildRecursive(child, number, currDepth, maxDepth);
	}
}