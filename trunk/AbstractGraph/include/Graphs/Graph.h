//
//  Graph.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "AbstractGraph.h"
#include "../../include/Nodes/Node.h"
#include "../../include/Edges/Edge.h"

#include "../incl.h"


class AGRAPH_EXPORT Graph : public AbstractGraph{

public:
		
	
	/*
	 * edges:	pointer to a vector of ints storing the ids
	 * 			of all MST tree edges, in no particular order
	 * 			
	 * return:	the total weight of the MST edges if G is connected
	 * 			-1 if G is disconnected
	 */
	int mst(vector<int> * edges);
	
	
	
	/*
	 * setX:	pointer to vector of ints used to store
	 * 			the ids of nodes in partite set X
	 * 			
	 * setY:	pointer to vector of ints used to store
	 * 			the ids of nodes in partite set Y
	 * 			
	 * return:	1 if the graph is bipartite
	 * 			0 otherwise
	 */
	int bipartite(vector<int> * setX, vector<int> * setY);
	
	
	
	/*
	 * matching:	pointer to vector of ints used to store
	 * 				ids of edges in the maximum matching
	 * 				
	 * return:	the size of the maximum matching
	 */
	int maxMatching(vector<int> * matching);
	
	
	
	/*
	 * cycle:	pointer to vector of ints used to store
	 *			ids of edges in the odd cycle
	 *
	 * return:	length of odd cycle when there is one
	 *			0 when there is no odd cycle
	 * 
	 * GUI:	highlight all edges with ids listed in cycle
	 *		if there is an odd cycle, notify user when
	 *		there is no cycle
	 */
	int getOddCycle(vector<int> * cycle);
	
	
	
	/*
	 * path:	pointer to vector of ints used to store
	 *			ids of nodes in the order of them being
	 *			visited in the path/cycle
	 *
	 * return:	true if there is eulerian path between s and t
	 *			false if there is not
	 *
	 * GUI:	label edges with their order of appearance as
	 *		ordered in the vector path, when there is Eulerian
	 *		path between s,t. Notify user when there is not.
	 */
	bool eulerianPath(int s, int t, vector<int> * path);
	
	
	
	/*
	 * bridges:	pointer to vector of ints used to store
	 *			ids of bridge edges
	 *
	 * return:	number of bridges in the graph
	 *			0 if there isn't any
	 *
	 * GUI:	highlight edges in bridges, if there any bridge
	 *		is found. Notify user when no bridge is found.
	 */
	int getBridges(vector<int> * bridges);
	
	
	
	/*
	 * code:	pointer to vector of ints used to store
	 *			prufer code of the tree
	 *
	 * label:	a map between nodes' ids and their label
	 *			used in the prufer code encoding
	 *
	 * return:	1 if the graph is a tree and prufer code
	 *			is properly encoded
	 *			0 id the graph is not a tree and no prufer
	 *			code exists
	 * 
	 * GUI:	display the code and label to the user, either
	 *		on canvas or through a popup, if the graph is a
	 *		tree. Notify user if it is not a tree.
	 */
	int getPruferCode(vector<int> * code, map<int, int> * label);
	
	
	
	/*
	 * code:	pointer to vector of ints used to store
	 *			prufer code of the tree
	 *
	 * GUI:	this method should be treated as a way of graph
	 *		construction. The resulting graph should be able
	 *		to be manipulated by the user just as the ones
	 *		created by hand or imported through xml. Also it
	 *		treats the graph as empty.
	 */
	void buildFromPruferCode(vector<int> * code);
	
	
	
	/*
	 * path:	the id of the next node in the path
	 *			reachable from first int, to the second
	 *
	 * dist:	the distance between two nodes
	 *
	 * GUI:	After this method is executed, you should retrieve
	 *		shortest path information from path and dist, instead
	 *		of running the individual pair shortest path each time.
	 *
	 * path usage:	if the shortest path between 1 and 8 is
	 *				1->5->2->9->8 then:
	 *				path[(1,8)] = 5
	 *				path[(5,8)] = 2
	 *				path[(2,8)] = 9
	 *				path[(9,8)] = 8
	 *
	 *				also notice the shortest path between 5 and 8
	 *				is exactly 5->2->9->8
	 */
	void allPairSP(map<pair<int, int>, int> * path, map<pair<int, int>, int> *dist);
	
	
	
	/*
	 * sequence:	points to a vector of nonegative integers
	 *				represent a degree list of nodes in the graph
	 *
	 * return:	1 if the sequence is graphic, and populates the graph
	 *			0 if the sequence is not graphic, does nothing
	 *
	 * GUI:	this method should be treated as a way of graph
	 *		construction. The resulting graph should be able
	 *		to be manipulated by the user just as the ones
	 *		created by hand or imported through xml. Also it
	 *		treats the graph as empty.
	 */
	int buildFromSequence(vector<int> * sequence);
	
	
	
	Graph();
	
	~Graph();
	
	/*
	 * nodeCount:	number of nodes to create
	 * 
	 * creates a graph with nodeCount
	 * number of isolated vertices
	 */
	Graph(int nodeCount);
	
	
	
	/*
	 * see AbstractGraph.h
	 */
	int addNode();
	
	
	
	/*
	 * see AbstractGraph.h
	 */
	int addEdge(int s, int t);
	
	
	
	/*
	 * see AbstractGraph.h
	 */
	int addEdge(int s, int t, int v);
	
	
	
	/*
	 * see AbstractGraph.h
	 */
	int removeNode(int id);
};

#endif








