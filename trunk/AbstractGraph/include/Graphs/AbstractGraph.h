#ifndef _ABSTRACTGRAPH_H_
#define _ABSTRACTGRAPH_H_

#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <map>

#include "../Edges/AbstractEdge.h"
#include "../Nodes/AbstractNode.h"

using namespace std;

class AbstractGraph{

public:
	
	AbstractGraph();
	
	~AbstractGraph();
	
	virtual int addNode() = 0;
	
	virtual int addEdge(int s, int t) = 0;
	
	virtual int addEdge(int s, int t, int v) = 0;
	
	virtual int removeNode(int id) = 0;
	
	
	int removeEdge(int id);
	
	int setEdgeValue(int id, int v);
	
	bool validEdge(int id);
	
	bool validNode(int id);
	
	bool isDirected();
	
	map<int, AbstractNode*> * getNodes();
	
	map<int, AbstractEdge*> * getEdges();
	
	void printGraph();
	
	
	int shortestPath(int s, int t, vector<int> * path);
	
	int mst(vector<int> * edges);
	
	
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