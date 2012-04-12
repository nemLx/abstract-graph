//
//  HopcroftKarp.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/11/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _AbstractGraph_HopcroftKarp_h_
#define _AbstractGraph_HopcroftKarp_h_

#include <queue>
#include "Algorithm.h"

#define NULLNODE -1


class HopcroftKarp : public Algorithm{

public:
	
	HopcroftKarp(AbstractGraph * g, vector<int> * partX, vector<int> * partY, vector<int> * matching);
	
	~HopcroftKarp();
	
	int solve();
	
private:
	
	AbstractGraph * g;
	
	vector<int> * matching;
	
	vector<int>	* partX;
	
	vector<int>	* partY;
	
	// storing ids of the two end nodes of an edge in the matching
	map<int, int> * matched;
	
	map<int, int> * dist;
	
	map<int, set<int>* > * adjacent;
	
	map<pair<int, int>, int> * mappedEdges;
	
	
	void init();
	
	bool bfs();
	
	bool dfs(int v);
	
	void constructMatching();
};

#endif









