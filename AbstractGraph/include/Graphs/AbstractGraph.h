//
//  AbstractGraph.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _ABSTRACTGRAPH_H_
#define _ABSTRACTGRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <map>

#include "../incl.h"

using namespace std;


class AbstractNode;

class AbstractEdge;

/*
 * A dynamic graph class used for containing nodes
 * and edges, and with ease to manipulate
 */
class AGRAPH_EXPORT AbstractGraph{

public:
	
	/* ------------------ */
	/* ALGORITHMS SECTION */
	/* ------------------ */
	
	/*
	 * s:	source node id
	 * 
	 * t:	target node id
	 * 
	 * path:	pointer to a vector of ints used to store
	 * 			ids of edges in the shortest path between s,t
	 * 
	 * return:	the total length of the path when there is one
	 * 			-1 if there is no path
	 */
	int shortestPath(int s, int t, vector<int> * path);
	
	
	
	/* ----------------------- */
	/* GRAPH STRUCTURE SECTION */
	/* ----------------------- */
	
	AbstractGraph();
	
	/*
	 * return:	a unique id of a new node
	 */
	virtual int addNode() = 0;
	


	/*
	 * s:	the id of the source node of a directed edge OR
	 * 		the id of one end node of a undirected edge
	 *
	 * t:	the id of the destination node of a directed edge OR
	 * 		the id of the other end node of a undirected edge
	 *
	 * return:	unique id of the edge when successful
	 * 			-1 if either s or t is invalid
	 */
	virtual int addEdge(int s, int t) = 0;
	


	/*
	 * s:	the id of the source node of a directed edge OR
	 * 		the id of one end node of a undirected edge
	 *
	 * t:	the id of the destination node of a directed edge OR
	 * 		the id of the other end node of a undirected edge
	 *
	 * v:	value on the edge, could have different meaning
	 * 		depending on the context
	 *
	 * return:	unique id of the edge when successful
	 * 			-1 if either s or t is invalid
	 */
	virtual int addEdge(int s, int t, int v) = 0;
	


	/*
	 * id:	id of node to be removed
	 *
	 * return:	0 if successful
	 * 			-1 if id is invalid
	 *
	 * This method will also remove all edges with at least one
	 * end being this node
	 */
	virtual int removeNode(int id) = 0;
	
	

	/*
	 * id:	id of edge to be removed
	 *
	 * return:	0 if successful
	 * 			-1 if id is invalid
	 *
	 * This method will update the adjacencies of the two nodes
	 * adjacent to this edge
	 */
	int removeEdge(int id);
	


	/*
	 * id:	id of edge to be updates
	 *
	 * v:	new value of this edge
	 *
	 * return:	0 if successful
	 * 			-1 if id is invalid
	 */
	int setEdgeValue(int id, int v);
	


	/*
	 * return:	true if this is a directed graph
	 * 			false if this is a graph
	 */
	bool isDirected();
	
	
	
	/*
	 * return:	a pointer to the map between node ids and nodes
	 */
	map<int, AbstractNode*> * getNodes();
	
	
	
	/*
	 * return:	a pointer to the map between edge ids and edges
	 */
	map<int, AbstractEdge*> * getEdges();
	
	
	
	/*
	 * prints the graph structure to command line
	 * should only be used for debugging purposes
	 */
	void printGraph();
	
	
	
	
	
	
/*
 * no comment below, you don't need to know this
 */	
	
protected:
	
	int n;
	
	int m;
	
	int nCounter;
	
	int mCounter;
	
	bool directed;
	
	map<int, AbstractNode*> * N;
	
	map<int, AbstractEdge*> * E;

	bool validEdge(int id);
	
	bool validNode(int id);
	
};

#endif









