//
//  FordFulkerson.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/10/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _AbstractGraph_FordFulkerson_h
#define _AbstractGraph_FordFulkerson_h

#include <queue>
#include "Algorithm.h"



class FordFulkerson : public Algorithm{
	
public:
	
	FordFulkerson(AbstractGraph * g, int s, int t, vector< pair<int, int> > * edgeFlow, vector<int> * cutSet);
	
	~FordFulkerson();
	
	int solve();
	
private:
	
	enum State {UNEXPLORED, EXPLORING, EXPLORED};
	
	int s;
	
	int t;
	
	AbstractGraph * g;
	
	queue<int> * Q;
	
	vector<pair<int, int> > * edgeFlow;
	
	vector<int> * cutSet;
	
	map<pair<int, int>, int> * flow;
	
	map<pair<int, int>, int> * capacity;
	
	map<int, State> * state;
	
	map<int, int> * ancestor;
	
	map<int, vector<int>* > * adjacent;
	
	map<int, bool> * visited;
	
	vector<int> * reachable;
	
	bool constructPath(int s, int t);
	
	void init();
	
	void resetBfs();
	
	void constructFlow();
	
	void constructCut();
};


#endif










