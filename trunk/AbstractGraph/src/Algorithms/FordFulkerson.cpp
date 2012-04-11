//
//  FordFulkerson.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/10/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/FordFulkerson.h"



FordFulkerson::FordFulkerson(AbstractGraph * g, int s, int t, vector< pair<int, int> > * edgeFlow, vector<int> * cutSet){
	
	this->g = g;
	
	this->s = s;
	
	this->t = t;
	
	this->edgeFlow = edgeFlow;
	
	this->cutSet = cutSet;
	
	Q = new queue<int>;
	
	flow = new map<pair<int, int>, int>;
	
	capacity = new map<pair<int, int>, int>;
	
	state = new map<int, State>;
	
	ancestor = new map<int, int>;
	
	adjacent = new map<int, vector<int>* >;
	
	visited = new map<int, bool>;
	
	reachable = new vector<int>;
	
	init();
}



void FordFulkerson::init(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, AbstractNode*>::iterator it = N->begin();
	
	while ( it != N->end() ){
		
		AbstractNode * curr = it->second;
		map<AbstractEdge*, AbstractNode*>* adj = curr->getAdjacent();
		map<AbstractEdge*, AbstractNode*>::iterator itAdj = adj->begin();
		vector<int> * neighbors = new vector<int>;
		
		while (itAdj != adj->end()) {
			
			AbstractEdge * adjEdge = itAdj->first;
			AbstractNode * adjNode = itAdj->second;
			pair<int, int> con(curr->id, adjNode->id);
			
			neighbors->push_back(adjNode->id);
			(*capacity)[con] += adjEdge->value;
			(*flow)[con] = 0;
			
			(*visited)[adjEdge->id] = false;
			itAdj++;
		}
		
		(*adjacent)[curr->id] = neighbors;
		(*state)[curr->id] = UNEXPLORED;
		(*ancestor)[curr->id] = -1;
		
		it++;
	}
	
}



bool FordFulkerson::constructPath(int s, int t){
	
	int u;
	int v;
	
	resetBfs();
	Q->push(s);
	
	while (!Q->empty()) {
		
		u = Q->front();
		vector<int> * neighbors = (*adjacent)[u];
		
		for (int i = 0; i < (int)neighbors->size(); i++){
			
			v = neighbors->at(i);
			pair<int, int> con(u, v);
			
			if ((*state)[v] != UNEXPLORED) {
				continue;
			}
			
			if ( (*capacity)[con] > (*flow)[con] || ( (*ancestor)[v] == u && (*flow)[con] < 0 ) ) {
				
				Q->push(v);
				(*state)[v] = EXPLORING;
				(*ancestor)[v] = u;
				reachable->push_back(v);
			}
		}
		
		
		(*state)[u] = EXPLORED;
		Q->pop();
	}
	
	return (*state)[t] == EXPLORED;
}



void FordFulkerson::resetBfs(){
	
	map<int, State>::iterator itS = state->begin();
	
	while (itS != state->end()){
		
		itS->second = UNEXPLORED;
		itS++;
	}
	
	map<int, int>::iterator itA = ancestor->begin();
	
	while (itA != ancestor->end()) {
		
		itA->second = -1;
		itA++;
	}
	
	if (reachable != NULL){
		delete reachable;
	}
	
	reachable = new vector<int>;
}



int FordFulkerson::solve(){
	
	int u = -1;
	int maxFlow = 0;
	
	while (constructPath(s, t)) {
		
		int inc = INFINITY;
		
		for (u = t; (*ancestor)[u] > -1; u = (*ancestor)[u]) {
			pair<int, int> con((*ancestor)[u], u);
			inc = min(inc, (*capacity)[con]-(*flow)[con]);
		}
		
		for (u = t; (*ancestor)[u] > -1; u = (*ancestor)[u]) {
			
			pair<int, int> forward((*ancestor)[u], u);
			pair<int, int> backward(u, (*ancestor)[u]);
			
			(*flow)[forward] += inc;
			(*flow)[backward] -= inc;
			
			(*adjacent)[u]->push_back((*ancestor)[u]);
		}
		
		maxFlow += inc;
	}
	
	constructFlow();
	
	constructCut();
	
	return maxFlow;
}



void FordFulkerson::constructFlow(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, AbstractNode*>::iterator it = N->begin();
	
	while ( it != N->end() ){
		
		AbstractNode * curr = it->second;
		map<AbstractEdge*, AbstractNode*>* adj = curr->getAdjacent();
		map<AbstractEdge*, AbstractNode*>::iterator itAdj = adj->begin();
		
		while (itAdj != adj->end()) {
			
			AbstractEdge * adjEdge = itAdj->first;
			AbstractNode * adjNode = itAdj->second;
			pair<int, int> con(curr->id, adjNode->id);
			int adjFlow = (*flow)[con];
			
			if ((*visited)[adjEdge->id]){
				itAdj++;
				continue;
			}
			
			if (adjFlow <= 0) {
				edgeFlow->push_back(pair<int, int>(adjEdge->id, 0));
			}else if (adjFlow > adjEdge->value){
				edgeFlow->push_back(pair<int, int>(adjEdge->id, adjEdge->value));
				(*flow)[con] -= adjEdge->value;
			}else{
				edgeFlow->push_back(pair<int, int>(adjEdge->id, adjFlow));
			}
			
			(*visited)[adjEdge->id] = true;
			itAdj++;
		}
		
		it++;
	}
}



void FordFulkerson::constructCut(){
	cutSet->push_back(s);
	for (int i = 0; i < (int)reachable->size(); i++){
		cutSet->push_back(reachable->at(i));
	}
}








