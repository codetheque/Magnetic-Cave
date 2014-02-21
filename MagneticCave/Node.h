#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Point.h"

enum eMinMaxType
	{
		eMinMaxType_Invalid,
		eMinMaxType_Min,
		eMinMaxType_Max
	};


class Node
{
	

public:
	Node();
	virtual ~Node();
	Node* getParent();
	void setParent(Node* p);
	int getValue();
	void setValue(int v);
	std::vector<Node*>& getChild();
	void addChild(Node* c);
	void addChild(int count);
	void setMinMaxType( eMinMaxType type);
	eMinMaxType getMinMaxType();

	Point position;
	
private:
	Node* parent;
	int value;
	std::vector<Node*> child;
	eMinMaxType minMaxType;

};

#endif