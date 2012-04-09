#ifndef _NODE_H_
#define _NODE_H_

#include "AbstractNode.h"
#include "../Edges/Edge.h"

using namespace std;

class Edge;

class Node : public AbstractNode{

public:
	
	int degree;
	
	map<int, Node*> * neighborhood;
	
	map<int, Edge*> * adjacent;
	
	
	
	Node(int id);
	
	~Node();
	
	int addAdjacent(Edge * adj, Node * neighbor);
	
	int removeAdjacent(Edge * adj, Node * neighbor);
	
	void printNode();
	
};

#endif