//
//  OddCycle.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/17/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_OddCycle_h
#define AbstractGraph_OddCycle_h

#include "Algorithm.h"
#include "../Graphs/Graph.h"
#include "../incl.h"



/*
 * implementation of an algorithm that carries out
 * a BFS on the vertices of a graph to find odd
 * length cycles, all edges lenghts are assumed 1
 */
class AGRAPH_EXPORT OddCycle : public Algorithm{

public:
	
	OddCycle(Graph * g, vector<int> * cycle);
	
	~OddCycle();
	
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
	 * partition information facilitating
	 * partite set assignment to vertices
	 */
	enum Partition {
		X,	// partite set X 
		Y, 	// partite set Y
		N	// not in any partite set
	};
	
	
	
	/*
	 * a vertex structure used by this particular
	 * algorithm
	 */
	struct Vertex{
		
		/*
		 * id of the corresponding node in the
		 * graph passed in
		 */
		int id;
		
		/*
		 * id of the previous node in the cycle
		 */ 
		int previous;
		
		/*
		 * state in BFS
		 */
		State state;
		
		/*
		 * partite set belonging
		 */
		Partition partition;
		
		/*
		 * contains all adjacent vertices
		 * in the form of a id to vertex map
		 */
		map<int, Vertex*> * adj;
	};
	
	
	/*
	 * points to working copy of graph
	 */
	Graph * g;
	
	
	
	/*
	 * points to vector containing ids of edges
	 * in the odd cycle
	 */
	vector<int> * cycle;
	
	
	
	/*
	 * a map between all ids and vertices
	 * id is the id of the corresponding
	 * node of the vertex in the graph
	 */
	map<int, Vertex*> * V;
	
	
	
	/*	 
	 * a queue of vertices used by BFS 
	 */
	queue<Vertex*> * Q;
	
	
	
	/*
	 * maps a pair of ids of nodes representing the
	 * edge between them to the id of the edge
	 * in the original graph
	 */
	map<pair<int, int>, int> * mappedEdges;
	
	
	
	
	/*
	 * see implementation for comments on functions below
	 */
	void initVertexStructure();
	
	void initVertices();
	
	Vertex* initVertex(AbstractNode* n);
	
	void initAdjacent(Vertex* v, AbstractNode* n);
	
	void reset(Vertex * root);
	
	Partition otherPartition(Vertex* v);
	
	bool foundOddCycle(Vertex * root);
	
	int constructCycle();
};

#endif
