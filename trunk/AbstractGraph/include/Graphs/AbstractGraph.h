#ifndef _ABSTRACTGRAPH_H_
#define _ABSTRACTGRAPH_H_

#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <map>

#include "../Edges/AbstractEdge.h"
#include "../Nodes/AbstractNode.h"

#include "../Algorithms/Algorithm.h"
#include "../Algorithms/Dijkstra.h"

using namespace std;

class AbstractGraph{

public:
	
	AbstractGraph();
	
	~AbstractGraph();
	
	virtual int addNode() = 0;
	
	virtual int addEdge(int s, int t) = 0;
	
	virtual int addEdge(int s, int t, int v) = 0;
	
	
	int removeNode(int id);
	
	int removeEdge(int id);
	
	int setEdgeValue(int id, int v);
	
	
	bool validEdge(int id);
	
	bool validNode(int id);
	
	
	int shortestPath(int s, int t, vector<int> * path);
	
	
protected:
	
	int n;
	
	int m;
	
	int nCounter;
	
	int mCounter;
	
	bool directed;
	
	map<int, AbstractNode*> * N;
	
	map<int, AbstractEdge*> * E;
	
};

#endif