
#include "Node.h"

Node::Node()
	: parent(nullptr)
{
}

Node::~Node()
{
	for (unsigned int i = 0; i < child.size(); ++i)
	{
		delete child[i];
	}
	child.clear();
}

Node* Node::getParent()
{
	return parent;
}

void Node::setParent(Node* p)
{
	parent = p;
}

int Node::getValue()
{
	return value;
}

void Node::setValue(int v)
{
	value= v;
}

std::vector<Node*>& Node::getChild()
{
	return child;
}

void Node::addChild(int count)
{
	for (int i = 0; i < count; ++i)
	{
		addChild(new Node());
	}
}

void Node::addChild(Node* c)
{
	child.push_back(c);
	c->setParent(this);
}
void Node::setMinMaxType( eMinMaxType type)
{
	minMaxType = type;
}

eMinMaxType Node::getMinMaxType()
{
	return minMaxType;	
}
