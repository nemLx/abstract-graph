#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "AbstractGraph.h"
#include "../Nodes/Node.h"
#include "../Edges/Edge.h"

class Graph : public AbstractGraph{

public:
	
	Graph();
	
	Graph(int nodeCount);

	int addNode();
	
	int addEdge(int s, int t);
	
	int addEdge(int s, int t, int v);
	
private:
	
	
};

#endif