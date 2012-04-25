//
//  GraphicSequence.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/23/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_GraphicSequence_h
#define AbstractGraph_GraphicSequence_h

#include "Algorithm.h"
#include "../Graphs/Graph.h"
#include "../incl.h"



/*
 * An algorithm that decides if a sequence of non-negative
 * integers represent a degree list of all nodes in a simple
 * undirected graph. If it is, also populates the parameter
 * graph g with the nodes with the degree list. Expects g to
 * be empty
 */
class AGRAPH_EXPORT GraphicSequence : public Algorithm{
	
public:
	
	GraphicSequence(Graph * g, vector<int> * sequence);
	
	int solve();
	
private:
	
	/*
	 * A comparison function used to sort the sequence of 
	 * pairs, larger second value comes first
	 */
	struct pairReverse {
		bool operator() (pair<int, int> lhs, pair<int, int> rhs){ 
			return (lhs.second > rhs.second);
		}
	}pairReverse;
	
	
	
	/*
	 * A comparison function used to sort the sequence of 
	 * integers, larger integer comes first
	 */
	struct vectorReverse {
		bool operator() (int lhs, int rhs){ 
			return (lhs > rhs);
		}
	}vectorReverse;
	
	
	
	/* 
	 * points to the working copy of graph
	 */
	Graph * g;
	
	
	
	/*
	 * size of the sequence
	 */
	int n;
	
	
	
	/*
	 * points to the degree sequence
	 */
	vector<int> * seq;
	
	
	
	/*
	 * see implementation for comments below
	 */
	void constructGraph();
	
	void addNodes();
	
	void addEdges(vector< pair<int, int> > * s);
	
	bool isGraphic(vector<int> * s);
};




#endif










