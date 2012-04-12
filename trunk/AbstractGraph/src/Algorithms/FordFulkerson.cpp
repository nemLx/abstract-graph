//
//  FordFulkerson.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/10/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/FordFulkerson.h"



FordFulkerson::FordFulkerson(DiGraph * g, int s, int t, vector< pair<int, int> > * edgeFlow, vector<int> * cutSet){
	
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



FordFulkerson::~FordFulkerson(){
	
	map<int, vector<int>*>::iterator it = adjacent->begin();
	
	while (it != adjacent->end()) {
		delete it->second;
		it++;
	}
	
	delete adjacent;
	delete Q;
	delete flow;
	delete capacity;
	delete state;
	delete ancestor;
	delete visited;
	delete reachable;
}



/*
 * initializes the vertex structure, mirroing the
 * nodes and adajcents in the original graph
 */
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
			
			/*
			 * flow is all initialized to 0
			 */
			(*flow)[con] = 0;
			
			/*
			 * visited is all initialized to false
			 */
			(*visited)[adjEdge->id] = false;
			
			itAdj++;
		}
		
		(*adjacent)[curr->id] = neighbors;
		(*state)[curr->id] = UNEXPLORED;
		(*ancestor)[curr->id] = -1;
		
		it++;
	}
	
}



/*
 * finds a path that could send more flow, in either
 * the graph or the residual graph, here the residual
 * graph is represented by flow in the opposite direction
 */
bool FordFulkerson::constructPath(int s, int t){
	
	int u;
	int v;
	
	resetBfs();
	Q->push(s);
	
	while (!Q->empty()) {
		
		u = Q->front();
		vector<int> * neighbors = (*adjacent)[u];
		
		/*
		 * visiting each neighbor of u
		 */
		for (int i = 0; i < (int)neighbors->size(); i++){
			
			v = neighbors->at(i);
			pair<int, int> con(u, v);
			
			/*
			 * skipp if visited a node before
			 */
			if ((*state)[v] != UNEXPLORED) {
				continue;
			}
			
			if ( 	(*capacity)[con] > (*flow)[con] ||	// there is room left
					( (*ancestor)[v] == u && (*flow)[con] < 0 ) // a backward edge
				) {
				
				Q->push(v);
				(*state)[v] = EXPLORING;
				(*ancestor)[v] = u;
				reachable->push_back(v);
			}
		}
		
		(*state)[u] = EXPLORED;
		Q->pop();
	}
	
	/*
	 * if destination is explored, then there is
	 * a path between s and t
	 */
	return (*state)[t] == EXPLORED;
}



/*
 * preps the states and ancestors for BFS
 */
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



/*
 * continues to loop to find more path,
 * until there is no more path to be found
 */
int FordFulkerson::solve(){
	
	int u = -1;
	int maxFlow = 0;
	
	while (constructPath(s, t)) {
		
		int inc = INFINITY;
		
		/*
		 * finds the bottleneck flow on the path
		 */
		for (u = t; (*ancestor)[u] > -1; u = (*ancestor)[u]) {
			pair<int, int> con((*ancestor)[u], u);
			inc = min(inc, (*capacity)[con]-(*flow)[con]);
		}
		
		/*
		 * updates the flow with the bottleneck along the path
		 */
		for (u = t; (*ancestor)[u] > -1; u = (*ancestor)[u]) {
			
			pair<int, int> forward((*ancestor)[u], u);
			pair<int, int> backward(u, (*ancestor)[u]);
			
			(*flow)[forward] += inc;
			(*flow)[backward] -= inc;
			
			(*adjacent)[u]->push_back((*ancestor)[u]);
		}
		
		/*
		 * updates max flow with the new increment
		 */
		maxFlow += inc;
	}
	
	constructFlow();
	constructCut();
	
	return maxFlow;
}



/*
 * construct the actual flow by reading the
 * flow on the edges
 */
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
			
			/*
			 * visite adjacent edge only once
			 */
			if ((*visited)[adjEdge->id]){
				itAdj++;
				continue;
			}
			
			if (adjFlow <= 0) {	
				// no flow or a backwardedge
				edgeFlow->push_back(pair<int, int>(adjEdge->id, 0));
			}else if (adjFlow > adjEdge->value){	
				/*
				 * flow is greater than capacity, only possible
				 * with multi edges, then distribute them
				 */
				edgeFlow->push_back(pair<int, int>(adjEdge->id, adjEdge->value));
				(*flow)[con] -= adjEdge->value;
			}else{
				// flow is smaller than bottleneck yet positive
				edgeFlow->push_back(pair<int, int>(adjEdge->id, adjFlow));
			}
			
			(*visited)[adjEdge->id] = true;
			itAdj++;
		}
		
		it++;
	}
}



/*
 * fill up the min cut vertices by reachable
 */
void FordFulkerson::constructCut(){
	cutSet->push_back(s);
	for (int i = 0; i < (int)reachable->size(); i++){
		cutSet->push_back(reachable->at(i));
	}
}








