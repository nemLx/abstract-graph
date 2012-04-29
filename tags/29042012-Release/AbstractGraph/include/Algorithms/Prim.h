//
//  Prim.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _PRIM_H_
#define _PRIM_H_

#include "Algorithm.h"
#include "../incl.h"

using namespace std;



class AGRAPH_EXPORT Prim : public Algorithm{
	
public:
	
	Prim(Graph * g, vector<int> * path);
	
	~Prim();
	
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
	 * number of nodes visited by the solve algorithm
	 */
	int numVisited;
	
	
	
	/*
	 * points to the vector used to store edge ids
	 * along the shortest path
	 */
	vector<int> * path;
	
	
	
	/*
	 * points to a working copy of the graph
	 */
	Graph * g;
	
	
	
	/*
	 * maps id to each vertex in the graph
	 */
	map<int, Vertex*> * V;
	
	
	
	/*
	 * priority queue used by the algorithm,
	 * vertices ordered in precedence of distance
	 * to the source
	 */
	//priority_queue<Vertex*, vector<Vertex*>, comp> * G;
	set<Vertex*, comp> * Q;
	
	
	
	/*
	 * see implementation for comments below
	 */
	void initVertexStructure();
	
	void initVertices();
	
	Vertex * initVertex(AbstractNode * node);
	
	void initAdjacent(Vertex * v, AbstractNode * n);
	
	void handleUnvisited(int uwCost, Vertex * w, Vertex * u);
	
	void refreshMin(Vertex * v);
	
	int constructMST();
};

#endif
