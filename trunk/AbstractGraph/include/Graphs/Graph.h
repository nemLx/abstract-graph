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
	
	~Graph();
	
	
	
	/*
	 * nodeCount:	number of nodes to create
	 * 
	 * creates a graph with nodeCount
	 * number of isolated vertices
	 */
	Graph(int nodeCount);
	
	
	
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
	 * edges:	pointer to a vector of ints storing the ids
	 * 			of all MST tree edges, in no particular order
	 * 			
	 * return:	the total weight of the MST edges if G is connected
	 * 			-1 if G is disconnected ( YET TO BE IMPLEMENTED )
	 */
	int mst(vector<int> * edges);
	
	
	
	/*
	 * setX:	pointer to vector of ints used to store
	 * 			the ids of nodes in partite set X
	 * 			
	 * setY:	pointer to vector of ints used to store
	 * 			the ids of nodes in partite set Y
	 * 			
	 * return:	1 if the graph is bipartite
	 * 			0 otherwise
	 */
	int bipartite(vector<int> * setX, vector<int> * setY);
	
	
	
	/*
	 * matching:	pointer to vector of ints used to store
	 * 				ids of edges in the maximum matching
	 * 				
	 * return:	the size of the maximum matching
	 */
	int maxMatching(vector<int> * matching);
};

#endif








