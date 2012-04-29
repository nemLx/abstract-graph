//
//  Gabow.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/22/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_Gabow_h
#define AbstractGraph_Gabow_h

#include "Algorithm.h"
#include "../Graphs/DiGraph.h"
#include "../incl.h"



/*
 * an implementation of Gabow's algorithm
 * which identifies all strong components
 * in a directed graph
 *
 * see http://en.wikipedia.org/wiki/Path-based_strong_component_algorithm
 * for details
 */
class AGRAPH_EXPORT Gabow : public Algorithm{
	
public:
	
	Gabow(DiGraph * g, map<int, int> * scMap);
	
	int solve();
	
	~Gabow();
	
private:
	
	/*
	 * points to working copy of digraph
	 */
	DiGraph * g;
	
	
	
	/*
	 * count is counter for graph searching
	 * scCount is counter for strong components
	 */
	int count, scCount;
	
	
	
	/*
	 * maps each node's id to the id of the
	 * strong components it belongs to
	 */
	map<int, int> * scMap;
	
	
	
	/*
	 * stack used for searching
	 */
	stack<int> * search;
	
	
	
	/*
	 * stack used for keeping track of strong
	 * components
	 */
	stack<int> * path; 
	
	
	
	/*
	 * preorder traversal in dfs
	 */
	map<int, int> * pre;
	
	
	
	/*
	 * maps a node's id to a set of ids of its
	 * adjacent nodes
	 */
	map<int, set<int>* > * adjs;
	
	
	
	/*
	 * see implementation for comments below
	 */
	void init();
	
	void scSearch(int w);
	
};



#endif









