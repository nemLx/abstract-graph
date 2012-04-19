//
//  Bridge.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/18/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/Bridge.h"



Bridge::Bridge(Graph * g, vector<int> * bridges){
	
	this->g = g;
	
	this->bridges = bridges;
	
	count = 0;
	
	bridgeCount = 0;
	
	V = g->getNodes();
	
	order = new map<int, int>;
	
	low = new map<int, int>;

	init();
}



Bridge::~Bridge(){
	
	delete order;
	delete low;
}



/*
 * initializes the order and preorder low number
 * of each vertex
 */
void Bridge::init(){
	
	map<int, AbstractNode*>::iterator it = V->begin();
	
	while ( it != V->end() ){
		
		AbstractNode * curr = it->second;
		
		(*order)[curr->id] = -1;
		(*low)[curr->id] = -1;
		
		it++;
	}	
}



/*
 * finds and adds the id of the bridging edge
 * to the vector, if there is no multi-edges
 */
void Bridge::addBridge(int s, int t){
	
	int multiEdge = -1;
	int edgeId = -1;
	AbstractNode * n = (*V)[s];
	map<AbstractEdge*, AbstractNode*> * adj = n->getAdjacent();
	map<AbstractEdge*, AbstractNode*>::iterator it = adj->begin();
	
	while (it != adj->end()) {
		
		if (it->second->id == t){
			
			// multiEdge will be positive if there are multiple edges
			multiEdge++; 
			edgeId = it->first->id;
		}
		it++;
	}
	
	// record bridge if there is no multi-edge
	if (!multiEdge){
		bridges->push_back(edgeId);
		bridgeCount++;
	}
}



/*
 * performs a DFS on the entire connected component,
 * and identifies bridges according to the preorder
 * traversal number, ignoring multi-edges.
 */
void Bridge::search(int v, int w){
	
	(*order)[w] = count++;
	(*low)[w] = (*order)[w];
	
	int t;
	map<AbstractEdge*, AbstractNode*> * adj = (*V)[w]->getAdjacent();
	map<AbstractEdge*, AbstractNode*>::iterator it = adj->begin();
	
	
	while (it != adj->end()) {
		
		t = it->second->id;
		
		// if node t has not been visited, visit it
		if ((*order)[t] == -1){
			
			search(w,t);
			
			// update preorder traversal low number
			if ((*low)[w] > (*low)[t]){
				(*low)[w] = (*low)[t];
			}
			
			if ((*low)[t] == (*order)[t]){
				addBridge(w, t); // found bridge w-t
			}
		}else if (t != v){
			
			// update preorder traversal low number
			if ((*low)[w] > (*order)[t]){
				(*low)[w] = (*order)[t];
			}
		}
		
		it++;
	}
}



/*
 * carries out DFS on all connected components
 * and finds bridges for all of them
 */
int Bridge::solve(){
	
	int v;
	map<int, AbstractNode*>::iterator it = V->begin();
	
	while (it != V->end()) {
		
		v = it->first;
		
		// order is -1 means has not been visited
		if ((*order)[v] == -1){
			search(v, v);
		}
		it++;
	}
	
	return bridgeCount;
}








