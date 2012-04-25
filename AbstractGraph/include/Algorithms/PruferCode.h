//
//  PruferCode.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/18/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_PruferCode_h
#define AbstractGraph_PruferCode_h

#include "Algorithm.h"
#include "../Graphs/Graph.h"
#include "../incl.h"



/*
 * two algorithms related to prufer codes,
 * both encoding the prufer code of a tree
 * and decoding a prufer code and constructs 
 * the corresponding tree
 *
 * this algorithm is purely based on the
 * definition of prufer codes see:
 * http://mathworld.wolfram.com/PrueferCode.html
 */
class AGRAPH_EXPORT PruferCode : public Algorithm{

public:
	
	PruferCode(Graph * g, vector<int> * code);
	
	PruferCode(Graph * g, vector<int> * code, map<int, int> * assignment);
	
	int solve();
	
private:
	
	/*
	 * points to working copy of graph
	 */
	Graph * g;
	
	
	
	/*
	 * true if is decoding a code, false if encoding a tree
	 */
	bool decoding;
	
	
	
	/*
	 * number of nodes in the graph
	 */
	int n;
	
	
	
	/*
	 * map of ids and nodes in G
	 */
	map<int, AbstractNode*> * V;
	
	
	
	/*
	 * points to the vector containing the code
	 */
	vector<int> * code;
	
	
	
	/*
	 * maps vertex ids to their labels
	 */
	map<int, int> * label;
	
	
	
	/*
	 * maps vertex ids to their status in DFS
	 */
	map<int, bool> * visited;
	
	
	
	/*
	 * maps vertex ids to sum of all other labels
	 * one vertex is adjacent to
	 */
	map<int, int> * adjacents;
	
	
	
	/*
	 * maps vertex ids to the (available) degree of
	 * it in the (decoding) encoding process
	 */
	map<int, int> * degree;
	
	
	
	/*
	 * set of vertices with degree 1, in increasing order
	 * of their labels
	 */
	set<int> * leaves;
	
	
	
	/*
	 * see implementation for comments below
	 */
	void constructHelper(Graph * g, vector<int> * code);
	
	void init();
	
	int dfs(int v);
	
	void extract(int counter);
	
	bool isTree();
	
	int decode();
	
	int encode();
	
	void nodeSetup();
	
	void degreeSetup();
};

#endif










