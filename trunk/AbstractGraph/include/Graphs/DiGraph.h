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


/*
 * a container for directed graphs
 */
class DiGraph : public AbstractGraph{
	
public:
	
	DiGraph();
	
	~DiGraph();
	
	
	
	/*
	 * nodeCount:	number of nodes to create
	 * 
	 * creates a directed graph with nodeCount
	 * number of isolated vertices
	 */
	DiGraph(int nodeCount);
	
	
	
	/*
	 * see AbstractGraph.h
	 */
	int addNode();
	
	
	
	/*
	 * see AbstractGraph.h
	 */
	int addEdge(int s, int t);
	
	
	
	/*
	 * see AbstractGraph.h
	 */
	int addEdge(int s, int t, int v);
	
	
	
	/*
	 * see AbstractGraph.h
	 */
	int removeNode(int id);
	
	
	
	/*
	 * s:	source node id
	 * 
	 * t:	target node id
	 * 
	 * edgeFlow:	vector of pairs of ints, used to store edge id
	 * 				and flow pair for all edges used in the graph
	 * 				
	 * cutSet:	vector of ints used to store ids of cut
	 * 			edges in the minimum cut
	 */
	int maxFlowMinCut(int s, int t, vector< pair<int, int> > * edgeFlow, vector<int> * cutSet);
};

#endif








