//
//  Dijkstra.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include "../../include/Algorithms/Dijkstra.h"

using namespace std;



Dijkstra::Dijkstra(int s, int t, AbstractGraph * g, vector<int> * path){
	
	G = new priority_queue<Vertex*, vector<Vertex*>, comp>();
	
	V = new map<int, Vertex*>;
	
	this->s = s;
	
	this->t = t;
	
	this->path = path;
	
	this->g = g;
	
	initVertexStructure();
}



void Dijkstra::initVertexStructure(){
	
	initVertices();
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, Vertex*>::iterator itVertex = V->begin();
	
	while (itVertex != V->end()){
		
		Vertex * vertex = itVertex->second;
		
		AbstractNode * node = (*N)[itVertex->first];
		
		initAdjacent(vertex, node);
		
		G->push(itVertex->second);
		
		itVertex++;
	}
}



void Dijkstra::initAdjacent(Vertex * v, AbstractNode * n){
	
	map<AbstractEdge*, AbstractNode*> * adjacent = n->getAdjacent();
	map<AbstractEdge*, AbstractNode*>::iterator itAdj = adjacent->begin();
	
	while (itAdj != adjacent->end()) {
		
		// an adjacent edge
		AbstractEdge * edge = itAdj->first;
		AbstractNode * to = itAdj->second;
		map<int, Vertex*>::iterator curr = v->adj->find(to->id);
		
		if (curr == v->adj->end()){
			
			// this node has not been included
			(*v->adj)[to->id] = (*V)[to->id];
			(*v->cost)[to->id] = edge->value;
			(*v->edgeId)[to->id] = edge->id;
			
		}else if ((*v->cost)[to->id] > edge->value) {
			
			// this node has been visited but the new edge offer
			// lower cost
			(*v->cost)[to->id] = edge->value;
			(*v->edgeId)[to->id] = edge->id;
		}
		
		itAdj++;
	}
}



void Dijkstra::initVertices(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	
	map<int, AbstractNode*>::iterator itNode = N->begin();
	
	while ( itNode != N->end() ){
		(*V)[itNode->first] = initVertex(itNode->second);
		itNode++;
	}
}



Dijkstra::Vertex * Dijkstra::initVertex(AbstractNode * node){
	
	Vertex * v = new Vertex();
    
    v->id = node->id;
    v->visited = false;
    v->dist = INFINITY;
    v->next = NULL;
	v->adj = new map<int, Vertex*>;
    v->cost = new map<int, int>;
    v->edgeId = new map<int, int>;
	
    return v;
}



int Dijkstra::solve(){
    
	//	init src node
    (*V)[s]->dist = 0;
    refreshMin();
    
	//	keep updating distances while there is node left
    while (G->size() > 0){
        
        Vertex * u = G->top();
        
		//	the node with smallest cost is dist, meaning
		//	it is disconnected from the src, break
        if (u->dist == INFINITY){
            break;
        }
        
		//	mark visited, and remove from queue
        u->visited = true;
        G->pop();
		
        int uwCost = 0;
        Vertex * w = NULL;
		
		map<int, Vertex*>::iterator it = u->adj->begin();
		
		//	for each adjacent node:
		while (it != u->adj->end()) {
			
			//	if w is unvisited, update corresponding
			//	values of w depending on prim or dijkstra	
			w = it->second;
			uwCost = (*u->cost)[it->first];
			
			if ( !w->visited ){
				handleUnvisited(uwCost, w, u);
            }
			it++;
		}
		
		// update the priority queue
		refreshMin();
    }
	
	// construct the path and return the distance from t
	return constructPath();
}



void Dijkstra::handleUnvisited(int uwCost, Vertex * w, Vertex * u){
	
	if ( (u->dist + uwCost) < w->dist ){
		w->dist = u->dist + uwCost;
		w->next = u;
	}
}



void Dijkstra::refreshMin(){
	
	Vertex * v = G->top();
    G->pop();
    G->push(v);
}



int Dijkstra::constructPath(){
	
	if ((*V)[t]->dist == INFINITY) {
		return -1;
	}
	
	Vertex * curr = (*V)[t];
	Vertex * ancestor;
	
	ancestor = (*V)[curr->next->id];
	path->push_back( (*(ancestor)->edgeId)[curr->id] );

	while (curr->next->id != s){
		curr = (*V)[curr->next->id];
		ancestor = (*V)[curr->next->id];
		path->push_back( (*(ancestor)->edgeId)[curr->id] );
	}
    
	return (*V)[t]->dist;
}










