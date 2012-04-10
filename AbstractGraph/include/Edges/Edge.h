#ifndef _EDGE_H_
#define _EDGE_H_

#include "../Nodes/Node.h"
#include "AbstractEdge.h"

class Node;

class Edge : public AbstractEdge{
	
public:
	
	Node * from;
	
	Node * to;
	
	Edge(int id, Node * s, Node * t);
	
	Edge(int id, Node * s, Node * t, int v);
	
	AbstractNode* getFrom();
	
	AbstractNode* getTo();
	
	void printEdge();
	
	~Edge();
};

#endif