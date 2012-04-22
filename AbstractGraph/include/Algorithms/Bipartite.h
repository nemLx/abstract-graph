//
//  Bipartite.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/9/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _AbstractGraph_Bipartite_h
#define _AbstractGraph_Bipartite_h

#include <queue>
#include "Algorithm.h"

#include "../incl.h"

/*
 * A algorithm determines bipartiteness and
 * finds the partite sets if they exist
 */
class AGRAPH_EXPORT Bipartite : public Algorithm{
	
public:
	
	Bipartite(Graph * g, vector<int> * partX, vector<int> * partY);
	
	~Bipartite();
	
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
	 * a queue of vertices used by BFS 
	 */
	queue<Vertex*> * Q;
	
	
	
	/*
	 * a map between all ids and vertices
	 * id is the id of the corresponding
	 * node of the vertex in the graph
	 */
	map<int, Vertex*> * V;
	
	
	
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
	 * used to balance the distribution of vertices
	 * between the two partite sets
	 */
	int parity;
	
	
	
	/*
	 * see implementation for comments on functions below
	 */
	void initVertexStructure();
	
	void initVertices();
	
	Vertex* initVertex(AbstractNode* n);
	
	void initAdjacent(Vertex* v, AbstractNode* n);
	
	void reset(Vertex * root);
	
	Partition otherPartition(Vertex* v);
	
	bool solve(Vertex * root);
	
	void constructSets();
};

#endif









