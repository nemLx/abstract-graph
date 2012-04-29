//
//  Dijkstra.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Algorithm.h"
#include "../incl.h"

//#include <boost/heap/fibonacci_heap.hpp>
//#include <boost/heap/policies.hpp>

using namespace std;
//using namespace boost;


/*
 * implementation of Dijkstra's algorithm of
 * shortest path between two nodes
 */
class AGRAPH_EXPORT Dijkstra : public Algorithm{

public:
	
	Dijkstra(int s, int t, AbstractGraph * g, vector<int> * path);
	
	~Dijkstra();
	
	int solve();
	
private:
	
	struct Vertex {
		int id;
		
		/*	
		 * pointer to adjacent vertices
		 */
		map<int, Vertex*> * adj;
		
		/*
		 * costs of each adjacent edge
		 */	
		map<int, int> * cost;
		
		/*
		 * maps each neighbor's id to the
		 * id of the edge connecting them
		 */
		map<int, int> * edgeId;
		
		/*
		 * true if visited by the algorithm
		 */
		bool visited;
		
		/*
		 * current best distance to source
		 */
		int dist;
		
		/*
		 * points to the last step in the shortest path
		 */
		Vertex * next;
	};
	
	
	
	/*
	 * functor used by the priority queue, vertices
	 * are ordered according to lowest distance to source
	 */
	class comp 
	: std::binary_function<Vertex*, Vertex*, bool>{
	public:
		bool operator() (const Vertex * lhs, const Vertex * rhs) const{
			return lhs->dist < rhs->dist;
		}
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
	 * points to the vector used to store edge ids
	 * along the shortest path
	 */
	vector<int> * path;
	
	
	
	/*
	 * points to a working copy of the graph
	 */
	AbstractGraph * g;
	
	
	
	/*
	 * maps id to each vertex in the graph
	 */
	map<int, Vertex*> * V;
	
	
	
	/*
	 * priority queue used by the algorithm,
	 * vertices ordered in precedence of distance
	 * to the source
	 */
	set<Vertex*, comp> * Q;
	
	
	/*
	 * see implementation for comments below
	 */
	void initVertexStructure();
	
	void initVertices();
	
	Vertex * initVertex(AbstractNode * node);
	
	void initAdjacent(Vertex * v, AbstractNode * n);
	
	void handleUnvisited(int uwCost, Vertex * w, Vertex * u);
	
	void refreshMin(Vertex* w);
	
	int constructPath();
};

#endif
