//
//  DiGraph.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _DIGRAPH_H_
#define _DIGRAPH_H_

#include "AbstractGraph.h"
#include "../Edges/DiEdge.h"
#include "../Nodes/DiNode.h"



class DiGraph : public AbstractGraph{
	
public:
	
	DiGraph();
	
	DiGraph(int nodeCount);
	
	int addNode();
	
	int addEdge(int s, int t);
	
	int addEdge(int s, int t, int v);
	
	int removeNode(int id);
};

#endif