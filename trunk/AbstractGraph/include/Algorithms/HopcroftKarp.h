//
//  HopcroftKarp.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/11/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _AbstractGraph_HopcroftKarp_h_
#define _AbstractGraph_HopcroftKarp_h_

#include <queue>
#include "Algorithm.h"
#include "../incl.h"

#define NULLNODE -1



/*
 * implementation of the Hopcroft-Karp algorithm
 * which find the maximum matching in a bipartite
 * graph, given the partite sets
 */
class AGRAPH_EXPORT HopcroftKarp : public Algorithm{

public:
	
	HopcroftKarp(AbstractGraph * g, vector<int> * partX, vector<int> * partY, vector<int> * matching);
	
	~HopcroftKarp();
	
	int solve();
	
private:
	
	/*
	 * points to working copy of graph
	 */
	AbstractGraph * g;
	
	
	
	/*
	 * points to vector of ints containing edges
	 * in the matching
	 */
	vector<int> * matching;
	
	
	
	/*
	 * points to vector used to store partite
	 * set X
	 */
	vector<int> * partX;
	
	
	
	/*
	 * points to vector used to store partite
	 * set Y
	 */
	vector<int> * partY;
	
	
	
	/* 
	 * storing ids of the two end nodes of an edge in the matching
	 */
	map<int, int> * matched;
	
	
	
	/*
	 * a distance between two nodes used by the algorithm
	 */
	map<int, int> * dist;
	
	
	
	/*
	 * maps id of a vertex to a set of ids of its neighbors
	 */
	map<int, set<int>* > * adjacent;
	
	
	
	/*
	 * maps a pair of ids of nodes representing the
	 * edge between them to the id of the edge
	 * in the original graph
	 */
	map<pair<int, int>, int> * mappedEdges;
	
	
	
	/*
	 * see implementation for comments below
	 */
	void init();
	
	void resetBfs(queue<int> * q);
	
	bool bfs();
	
	bool dfs(int v);
	
	void constructMatching();
};

#endif









