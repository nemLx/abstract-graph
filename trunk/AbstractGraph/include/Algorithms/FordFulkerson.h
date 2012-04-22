//
//  FordFulkerson.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/10/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _AbstractGraph_FordFulkerson_h
#define _AbstractGraph_FordFulkerson_h

#include <queue>
#include "Algorithm.h"

#include "../incl.h"



/*
 * implementaion of the Ford-Fulkerson algorithm on
 * maximum network flor in a directed graph, also
 * constructs the minimum cut at the same time
 */
class AGRAPH_EXPORT FordFulkerson : public Algorithm{
	
public:
	
	FordFulkerson(DiGraph * g, int s, int t, vector< pair<int, int> > * edgeFlow, vector<int> * cutSet);
	
	~FordFulkerson();
	
	int solve();
	
private:
	
	/*
	 * state information used in BFS
	 */
	enum State {
		UNEXPLORED,	// visited it and all neighbors
		EXPLORING,	// visited it but not all neighbors
		EXPLORED	// not visited at all
	};
	
	/*
	 * id of source node
	 */
	int s;
	
	
	
	/*
	 * id of destination node
	 */
	int t;
	
	
	
	/*
	 * points to a working copy of the graph
	 */
	DiGraph * g;
	
	
	
	/*
	 * a queue used for BFS
	 */
	queue<int> * Q;
	
	
	
	/*
	 * points to a vector of all pairs of edge id
	 * and the flow on that edge
	 */
	vector< pair<int, int> > * edgeFlow;
	
	
	
	/*
	 * points to a set of ids of edgs in the
	 * minimum cut set
	 */
	vector<int> * cutSet;
	
	
	
	/*
	 * maps a pair of node ids, which represents
	 * an edge between them, to the flow on that edge
	 */
	map<pair<int, int>, int> * flow;
	
	
	
	/*
	 * maps a pair of node ids, which represents an
	 * edge between them, to the capacity of that edge
	 */
	map<pair<int, int>, int> * capacity;
	
	
	
	/*
	 * maps a vertex id to the state of the vertex
	 * state is used by BFS
	 */
	map<int, State> * state;
	
	
	
	/*
	 * maps the id of a node to the id of its ancestor
	 * int the flow
	 */
	map<int, int> * ancestor;
	
	
	
	/*
	 * maps id of a node to a vector od node ids which
	 * are adjacent to it
	 */
	map<int, vector<int>* > * adjacent;
	
	
	
	/*
	 * maps id of node to bool specifying if it has
	 * been visited by the algorithm
	 */
	map<int, bool> * visited;
	
	
	
	/*
	 * points to a vector representing the nodes reachable
	 * from the source node in the final residual graph,
	 * used to construct the min cut
	 */
	vector<int> * reachable;
	
	
	
	/*
	 * see implementation for comments below
	 */
	bool constructPath(int s, int t);
	
	void init();
	
	void resetBfs();
	
	void constructFlow();
	
	void constructCut();
};


#endif










