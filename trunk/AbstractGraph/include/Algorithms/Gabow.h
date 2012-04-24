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



class AGRAPH_EXPORT Gabow : public Algorithm{
	
public:
	
	Gabow(DiGraph * g, map<int, int> * scMap);
	
	int solve();
	
	~Gabow();
	
private:
	
	DiGraph * g;
	
	int count, scCount;
	
	map<int, int> * scMap;
	
	stack<int> * search;
	
	stack<int> * path; 
	
	map<int, int> * pre;
	
	map<int, set<int>* > * adjs;
	
	
	
	void init();
	
	void scSearch(int w);
	
};



#endif









