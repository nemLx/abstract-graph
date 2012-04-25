//
//  FloydWarshall.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/23/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/FloydWarshall.h"



FloydWarshall::FloydWarshall(Graph * g,
							 map<pair<int, int>, int> * path,
							 map<pair<int, int>, int> * dist){
	
	this->g = g;
	this->dist = dist;
	this->path = path;
	
	n = (int)g->getNodes()->size();
	
	init();
}



FloydWarshall::~FloydWarshall(){
	
}



/*
 * initialize data structures
 */
void FloydWarshall::init(){
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++){
			(*dist)[pair<int, int>(i,j)] = INFINITY;
		}
	}
	
	initEdges();
	
	for (int i = 0; i < n; i++) {
		(*dist)[pair<int, int>(i,i)] = 0;
	}
}



/*
 * initialize all the edges needed for
 * path computation
 */
void FloydWarshall::initEdges(){
	
	int s, t, d;
	map<int, AbstractEdge*> * edges = g->getEdges();
	map<int, AbstractEdge*>::iterator it = edges->begin();
	
	while (it != edges->end()) {
		
		AbstractEdge * e = it->second;
		s = e->getFrom()->id;
		t = e->getTo()->id;
		d = e->value;
		
		pair<int, int> oldPair (s,t);
		pair<int, int> reversed (t,s);
		int oldDist = (*dist)[oldPair];
		
		if (oldDist > d || oldDist < 1){
			(*dist)[oldPair] = d;
			(*dist)[reversed] = d;
			(*path)[oldPair] = e->id;
			(*path)[reversed] = e->id;
		}
		
		it++;
	}
}



/*
 * a function decides if there is path between s and t
 */
bool FloydWarshall::hasPath(int s, int t){
	
	return path->find(pair<int, int>(s,t)) != path->end() ||
		path->find(pair<int, int>(t,s)) != path->end();
}



/*
 * main procudere of the algorithm, see wiki for algorithm
 * details
 */
int FloydWarshall::solve(){
	
	for (int i = 0; i < n; i++) {
		for (int s = 0; s < n; s++) {
			
			if (!hasPath(i, s)){
				continue;
			}
			
			for (int t = 0; t < n; t++) {
				
				if (s == t){ // self loop, next round
					continue;
				}else{
					relax(i, s, t); // is edge, relax
				}
			}
		}
	}
	
	// replaces infinity distances with -1
	markNoPath();
	
	return 1;
}



/*
 * "relax" operation defined by the algorithm, see
 *	wiki for more detail
 */
void FloydWarshall::relax(int i, int s, int t){
	
	pair<int, int> st (s,t);
	pair<int, int> si (s,i);
	pair<int, int> it (i,t);
	
	if ((*dist)[si] == INFINITY || (*dist)[it] == INFINITY){
		return;
	}
	
	if ((*dist)[st] > ((*dist)[si] + (*dist)[it])){
		(*path)[st] = (*path)[si];
		(*dist)[st] = (*dist)[si] + (*dist)[it];
	}
}



/*
 * replaces all infinity distances with -1
 */
void FloydWarshall::markNoPath(){
	
	map<pair<int, int>, int>::iterator it = dist->begin();
	
	while (it != dist->end()) {
		if (it->second >= INFINITY){
			it->second = -1;
		}
		
		it++;
	}
}









