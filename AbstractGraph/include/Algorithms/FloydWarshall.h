//
//  FloydWarshall.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/23/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_FloydWarshall_h
#define AbstractGraph_FloydWarshall_h

#include "Algorithm.h"
#include "../Graphs/Graph.h"
#include "../incl.h"



/*
 * an implementation of Floyd Warshall algorithm that
 * computes all pairs shortest path in n^3 time
 *
 * see http://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
 * for details
 */
class AGRAPH_EXPORT FloydWarshall : public Algorithm{

public:
	
	FloydWarshall(Graph * g, 
				  map<pair<int, int>, int> * dist,
				  map<pair<int, int>, int> * path);
	
	~FloydWarshall();
	
	int solve();
	
private:
	
	/*
	 * points to working copy of graph
	 */
	Graph * g;
	
	
	
	/*
	 * number of nodes in the graph
	 */
	int n;
	
	
	
	/*
	 * maps a pair of ids, the source and destination
	 * to the id of the next step to take form source
	 * in the shortest path
	 */
	map<pair<int, int>, int> * path;
	
	
	
	/*
	 * maps a paird of ids, the source and destination
	 * to the shortest path distance between them
	 */
	map<pair<int, int>, int> * dist;
	
	
	
	/*
	 * see implementation for comments below
	 */
	void init();
	
	void initEdges();
	
	bool hasPath(int s, int t);
	
	void relax(int i, int s, int t);
	
	void markNoPath();
};


#endif











