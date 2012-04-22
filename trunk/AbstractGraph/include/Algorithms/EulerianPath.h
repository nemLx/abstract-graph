//
//  EulerianPath.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/18/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_EulerianPath_h
#define AbstractGraph_EulerianPath_h

#include "Algorithm.h"
#include "../Graphs/Graph.h"
#include "../incl.h"



/*
 * an algorithm that identifies the Eulerian path
 * between any two given nodes, if any. when passed
 * in the same start and end, it detect Eulerian cycle
 */
class AGRAPH_EXPORT EulerianPath : public Algorithm{

public:
	
	EulerianPath(Graph * g, int s, int t, vector<int> * path);
	
	~EulerianPath();
	
	int solve();
	
private:
	
	/*
	 * a vertex structure used by this particular
	 * algorithm
	 */
	struct Vertex{
		
		/*
		 * degree of the corresponding node in the
		 * graph passed in
		 */
		int id;
		
		
		/*
		 * id of the corresponding node in the
		 * graph passed in
		 */
		int degree;
		
		
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
	 * points to vector containing vertex
	 * ids in the order of the path
	 */
	vector<int> * path;
	
	
	
	/*
	 * ids of source and target vertex
	 */
	int s, t;
	
	
	
	/*
	 * stack used by the tour function
	 */
	stack<int> * S;
	
	
	
	/*
	 * a map between all ids and vertices
	 * id is the id of the corresponding
	 * node of the vertex in the graph
	 */
	map<int, Vertex*> * V;
	
	
	
	map<pair<int, int>, int> * edges;
	
	
	
	/*
	 * see implementation for comments on functions below
	 */
	bool isEulerian();
	
	void removeEdge(int e, int s, int t);
	
	int tour(int v);
	
	void constructPath();
	
	void initVertexStructure();
	
	void initVertices();
	
	Vertex* initVertex(AbstractNode* n);
	
	void initAdjacent(Vertex* v, AbstractNode* n);
	
};

#endif










