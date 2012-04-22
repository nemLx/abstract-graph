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



class Gabow : public Algorithm{
	
public:
	
	Gabow(DiGraph * g, vector<int> * scs);
	
	int solve();
	
	~Gabow();
	
private:
	
	DiGraph * g;
	
	vector<int> * scs;
	
	stack<int> * s;
	
	int count, scCount;
	
	map<int, int> * pre;
	
	map<int, int> * low;
	
	map<int, int> * setId;
	
	
	
	void init();
	
};



#endif









