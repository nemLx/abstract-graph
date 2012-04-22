//
//  Gabow.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/22/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/Gabow.h"



Gabow::Gabow(DiGraph * g, vector<int> * scs){
	
	this->g = g;
	this->scs = scs;
	
//	low = new vector<int>;
//	pre = new vector<int>;
//	setId = new vector<int>;
	
	count = 0;
	scCount = 0;
}



Gabow::~Gabow(){
	
	delete low;
	delete pre;
	delete setId;
}



/*
 * initializes the vertex structure, mirroing the
 * nodes and adajcents in the original graph
 */
void Gabow::init(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, AbstractNode*>::iterator it = N->begin();
	
	while ( it != N->end() ){
		
		AbstractNode * curr = it->second;
		map<AbstractEdge*, AbstractNode*>* adj = curr->getAdjacent();
		map<AbstractEdge*, AbstractNode*>::iterator itAdj = adj->begin();
		set<int> * neighbors = new set<int>;
		
		while ( itAdj != adj->end()){
			
			neighbors->insert(itAdj->second->id);
			//(*mappedEdges)[pair<int, int>(curr->id, itAdj->second->id)] = itAdj->first->id;
			itAdj++;
		}
		
		
		
		it++;
	}
}



int Gabow::solve(){
	
	return 0;
}















