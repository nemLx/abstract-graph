//
//  Bipartite.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/9/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _AbstractGraph_Bipartite_h
#define _AbstractGraph_Bipartite_h

#include <queue>
#include "Algorithm.h"



class Bipartite : public Algorithm{
	
public:	
	
	Bipartite(Graph * g, vector<int> * partX, vector<int> * partY);
	
	int solve();
	
private:
	
	enum State {UNEXPLORED, EXPLORING, EXPLORED};
	
	enum Partition {X, Y, N};
	
	struct Vertex{
		
		int id;
		
		State state;
		
		Partition partition;
		
		//	pointer to adjacent vertices
		map<int, Vertex*> * adj;
	};
	
	Graph * g;
	
	map<int, Vertex*> * V;
	
	queue<Vertex*> * Q;
	
	vector<int> * partX;
	
	vector<int> * partY;
	
	int parity;
	
	
	
	void initVertexStructure();
	
	void initVertices();
	
	Vertex* initVertex(AbstractNode* n);
	
	void initAdjacent(Vertex* v, AbstractNode* n);

	bool solve(Vertex * root);
	
	void reset(Vertex * root);
	
	Partition otherPartition(Vertex* v);
	
	void constructSets();
};

#endif









