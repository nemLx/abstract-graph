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



class AGRAPH_EXPORT GraphicSequence : public Algorithm{
	
public:
	
	GraphicSequence(Graph * g, vector<int> * sequence);
	
	int solve();
	
private:
	
	struct pairReverse {
		bool operator() (pair<int, int> lhs, pair<int, int> rhs){ 
			return (lhs.second > rhs.second);
		}
	}pairReverse;
	
	struct vectorReverse {
		bool operator() (int lhs, int rhs){ 
			return (lhs > rhs);
		}
	}vectorReverse;
	
	Graph * g;
	
	int n;
	
	vector<int> * seq;
	
	
	
	void constructGraph();
	
	void addNodes();
	
	void addEdges(vector< pair<int, int> > * s);
	
	bool isGraphic(vector<int> * s);
};




#endif










