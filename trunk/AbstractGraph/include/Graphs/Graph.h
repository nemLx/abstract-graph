//
//  Graph.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "AbstractGraph.h"
#include "../../include/Nodes/Node.h"
#include "../../include/Edges/Edge.h"



class Graph : public AbstractGraph{

public:
	
	Graph();
	
	Graph(int nodeCount);

	int addNode();
	
	int addEdge(int s, int t);
	
	int addEdge(int s, int t, int v);
	
	int removeNode(int id);
	
	int bipartite(vector<int> * setX, vector<int> * setY);
};

#endif