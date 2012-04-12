//
//  HopcroftKarp.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/11/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/HopcroftKarp.h"



HopcroftKarp::HopcroftKarp(AbstractGraph * g, vector<int> * partX, vector<int> * partY, vector<int> * matching){
	
	this->g = g;
	
	this->partX = partX;
	
	this->partY = partY;
	
	this->matching = matching;
	
	matched = new map<int, int>;
	
	dist = new map<int, int>;
	
	adjacent = new map<int, set<int> *>;
	
	mappedEdges = new map<pair<int, int>, int>;
	
	init();
}



HopcroftKarp::~HopcroftKarp(){
	
	map<int, set<int>*>::iterator it = adjacent->begin();
	
	while (it != adjacent->end()) {
		delete it->second;
		it++;
	}
	
	delete adjacent;
	delete matched;
	delete dist;
	delete mappedEdges;
}



/*
 * initializes the vertex structure, mirroing the
 * nodes and adajcents in the original graph
 */
void HopcroftKarp::init(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, AbstractNode*>::iterator it = N->begin();

	while ( it != N->end() ){
		
		AbstractNode * curr = it->second;
		map<AbstractEdge*, AbstractNode*>* adj = curr->getAdjacent();
		map<AbstractEdge*, AbstractNode*>::iterator itAdj = adj->begin();
		set<int> * neighbors = new set<int>;
		
		while ( itAdj != adj->end()){
			
			neighbors->insert(itAdj->second->id);
			(*mappedEdges)[pair<int, int>(curr->id, itAdj->second->id)] = itAdj->first->id;
			itAdj++;
		}
		
		(*adjacent)[curr->id] = neighbors;
		(*matched)[curr->id] = NULLNODE;
		it++;
	}
	
	(*adjacent)[NULLNODE] = new set<int>;
	(*matched)[NULLNODE] = NULLNODE;
}



/*
 * preps the queue for bfs
 */
void HopcroftKarp::resetBfs(queue<int> * q){
	
	int u, uMatched;
	
	for (int i = 0; i < (int)partX->size(); i++){
		u = partX->at(i);
		uMatched = (*matched)[u];
		
		if (uMatched == NULLNODE){
			(*dist)[u] = 0;
			q->push(u);
		}else{
			(*dist)[u] = INFINITY;
		}
	}
	
	(*dist)[NULLNODE] = INFINITY;
}



/*
 * bfs from all nodes in set X
 */
bool HopcroftKarp::bfs(){
	
	queue<int> q;
	int u, v, uMatched;
	
	resetBfs(&q);
	
	while (!q.empty()) {
		
		v = q.front();
		q.pop();
		
		/*
		 * skipp the null node, which
		 * is not a legal node in g
		 */
		if (v == NULLNODE){
			continue;
		}
		
		set<int> * neighbors = (*adjacent)[v];
		set<int>::iterator it = neighbors->begin();
		
		while (it != neighbors->end()) {
			
			u = *it;
			uMatched = (*matched)[u];
			
			if ((*dist)[uMatched] == INFINITY){
				(*dist)[uMatched] = (*dist)[v] + 1;
				q.push(uMatched);
			}
			
			it++;
		}
	}
	
	return (*dist)[NULLNODE] != INFINITY;
}



/*
 * does a dfs from a particular node
 * 
 * return true if finds a dfs match
 * of any match of its neighbors
 */
bool HopcroftKarp::dfs(int v){
	
	int u, uMatched;
	
	if (v == NULLNODE){
		return true;
	}
	
	set<int> * neighbors = (*adjacent)[v];
	set<int>::iterator it = neighbors->begin();
	
	while (it != neighbors->end()) {
		
		u = *it;
		uMatched = (*matched)[u];
		
		if ( (*dist)[uMatched] != (*dist)[v]+1 ) {
			it++;
			continue;
		}
		
		if (dfs(uMatched)){
			(*matched)[u] = v;
			(*matched)[v] = u;
			
			matching->push_back((*mappedEdges)[pair<int, int>(u,v)]);
			
			return true;
		}
		
		it++;
	}
	
	(*dist)[v] = INFINITY;
	return false;
}



int HopcroftKarp::solve(){
	
	int v;
	int matchingSize = 0;
	
	while (bfs()) {
		
		for (int i = 0; i < (int)partX->size(); i++){
			
			v = partX->at(i);
			if ((*matched)[v] == NULLNODE && dfs(v)){
				matchingSize++;
			}
		}
	}
	
	return matchingSize;
}









