//
//  AbstractGraph.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _ABSTRACTGRAPH_H_
#define _ABSTRACTGRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;



class AbstractNode;

class AbstractEdge;

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
	
	int maxFlowMinCut(int s, int t, vector< pair<int, int> > * edgeFlow, vector<int> * cutSet);
	
	
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









