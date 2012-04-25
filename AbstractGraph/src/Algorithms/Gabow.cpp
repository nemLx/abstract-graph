//
//  Gabow.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/22/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/Gabow.h"



Gabow::Gabow(DiGraph * g, map<int, int> * scMap){
	
	this->g = g;
	this->scMap = scMap;
	
	pre = new map<int, int>;
	search = new stack<int>;
	path = new stack<int>;
	adjs = new map<int, set<int>* >;
	
	count = 0;
	scCount = 0;
	
	init();
}



Gabow::~Gabow(){
	
	map<int, set<int>* >::iterator it = adjs->begin();
	
	while (it != adjs->end()) {
		if (it->second != NULL)
		delete it->second;
		
		it++;
	}
	
	delete adjs;
	delete pre;
	delete search;
	delete path;
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
			itAdj++;
		}
		
		(*adjs)[curr->id] = neighbors;
		(*pre)[curr->id] = -1;
		(*scMap)[curr->id] = -1;
		
		it++;
	}
}



/*
 * a dfs on g and recursively identifies
 * scs based on path
 */
void Gabow::scSearch(int w){
	
	int v;
	
	(*pre)[w] = count++;
	search->push(w);
	path->push(w);
	
	set<int> * adj = (*adjs)[w];
	set<int>::iterator it = adj->begin();
	
	while (it != adj->end()) {
		
		int t = *it;
		
		if ( (*pre)[t] == -1 ){
			scSearch(t);
		}else if ( (*scMap)[t] == -1 ){
			while ((*pre)[path->top()] > (*pre)[t] ) {
				path->pop();
			}
		}
		
		it++;
	}
	
	if ( path->top() == w ){
		path->pop();
	}else{
		return;
	}
	
	do{
		(*scMap)[v = search->top()] = scCount;
		search->pop();
	}while (v != w);
	
	scCount++;
}



int Gabow::solve(){
	
	map<int, AbstractNode*>::iterator it = g->getNodes()->begin();
	
	// performs scSearch on all connected components
	while (it != g->getNodes()->end()) {
		if ( (*pre)[it->first] == -1 ){
			scSearch(it->first);
		}
		
		it++;
	}
	
	return scCount;
}















