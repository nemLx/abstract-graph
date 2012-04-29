//
//  Bridge.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/18/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_Bridge_h
#define AbstractGraph_Bridge_h

#include "Algorithm.h"
#include "../Graphs/Graph.h"
#include "../incl.h"



/*
 * an algorithm that finds all bridging edges
 * in a graph
 *
 */
class AGRAPH_EXPORT Bridge : public Algorithm{

public:
	
	Bridge(Graph * g, vector<int> * bridges);
	
	~Bridge();
	
	int solve();
	
private:
	
	/*
	 * points to working copy of graph
	 */
	Graph * g;
	
	
	
	/*
	 * number of edges visited in DFS
	 */
	int count;
	
	
	
	/*
	 * number of bridging edges found
	 */
	int bridgeCount;
	
	
	
	/*
	 * points to vector of ints used to store
	 * ids of bridges 
	 */
	vector<int> * bridges;
	
	
	
	/*
	 * map of ids and nodes in g
	 */
	map<int, AbstractNode*> * V;
	
	
	
	/*
	 * preorder traversal number of each node
	 * in the DFS
	 */
	map<int, int> * order;
	
	
	
	/*
	 * lowest preorder traversal number of a node
	 */
	map<int, int> * low;
	
	
	
	/*
	 * see implementation for comments below
	 */
	void init();
	
	void search(int s, int t);
	
	void addBridge(int s, int t);
};



#endif










