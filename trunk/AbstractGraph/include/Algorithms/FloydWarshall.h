//
//  FloydWarshall.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/23/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_FloydWarshall_h
#define AbstractGraph_FloydWarshall_h

#include "Algorithm.h"
#include "../Graphs/Graph.h"
#include "../incl.h"



class AGRAPH_EXPORT FloydWarshall : public Algorithm{

public:
	
	FloydWarshall(Graph * g, 
				  map<pair<int, int>, int> * dist,
				  map<pair<int, int>, int> * path);
	
	~FloydWarshall();
	
	int solve();
	
private:
	
	Graph * g;
	
	int n;
	
	map<pair<int, int>, int> * path;
	
	map<pair<int, int>, int> * dist;
	
	
	
	void init();
	
	void initEdges();
	
	bool hasPath(int s, int t);
	
	void relax(int i, int s, int t);
	
	void markNoPath();
};


#endif











