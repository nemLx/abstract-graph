//
//  FordFulkerson.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/10/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_FordFulkerson_h
#define AbstractGraph_FordFulkerson_h

#include <queue>
#include "Algorithm.h"



class FordFulkerson : public Algorithm{
	
public:
	
	FordFulkerson(DiGraph * g, int s, int t, vector< pair<int, int> > * edgeFlow);
	
	int solve();
	
private:
	
	enum State {UNEXPLORED, EXPLORING, EXPLORED};
	
	int s;
	
	int t;
	
	DiGraph * g;
	
	queue<int> * Q;
	
	vector<pair<int, int> > * edgeFlow;
	
	map<pair<int, int>, int> * flow;
	
	map<pair<int, int>, int> * capacity;
	
	map<int, State> * state;
	
	map<int, int> * ancestor;
	
	map<int, vector<int>* > * adjacent;
	
	bool constructPath(int s, int t);
	
	void init();
	
	void resetBfs();
	
	void constructFlow();
};


#endif










