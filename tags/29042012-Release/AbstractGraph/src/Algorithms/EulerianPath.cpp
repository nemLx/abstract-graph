//
//  EulerianPath.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/18/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/EulerianPath.h"



EulerianPath::EulerianPath(Graph * g, int s, int t, vector<int> * path){
	
	this->g = g;
	
	this->s = s;
	
	this->t = t;
	
	this->path = path;
	
	V = new map<int, Vertex*>;
	S = new stack<int>;
	edges = new map<pair<int, int>, int>;

	initVertexStructure();
}



EulerianPath::~EulerianPath(){
	
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()) {
		delete it->second->adj;
		
		delete it->second;
		it++;
	}
	
	delete V;
	delete S;
}



/*
 * initializes the vertex structure, mirroing the
 * nodes and adajcents in the original graph
 */
void EulerianPath::initVertexStructure(){
	
	/*
	 * create a new vertex for each
	 * node first
	 */
	initVertices();
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()){
		
		Vertex * vertex = it->second;
		AbstractNode * node = (*N)[it->first];
		
		/*
		 * according to the adjacent structure
		 * in the original graph, initialize
		 * the adjacents for all vertices
		 */
		initAdjacent(vertex, node);
		
		it++;
	}
}



/*
 * create a new vertex for each node in g
 */
void EulerianPath::initVertices(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, AbstractNode*>::iterator it = N->begin();
	
	while ( it != N->end() ){
		(*V)[it->first] = initVertex(it->second);
		it++;
	}
}



/*
 * initializes a new vertex
 */
EulerianPath::Vertex * EulerianPath::initVertex(AbstractNode *n){
	
	Vertex * v = new Vertex();
	
	v->id = n->id;
	v->degree = -1;
	v->adj = new map<int, Vertex*>;
	
	return v;
}



/*
 * populate adj for each vertex according to
 * adjacents in the original graph
 * 
 * adjacents is defined only for reachable nodes
 */
void EulerianPath::initAdjacent(Vertex *v, AbstractNode *n){
	
	map<AbstractEdge*, AbstractNode*> * adjacent = n->getAdjacent();
	map<AbstractEdge*, AbstractNode*>::iterator it = adjacent->begin();
	
	while (it != adjacent->end()) {
		
		AbstractEdge * adjEdge = it->first;
		AbstractNode * adjNode = it->second;
		
		(*v->adj)[adjEdge->id] = (*V)[adjNode->id];
		(*edges)[pair<int, int>(v->id, adjNode->id)] = adjEdge->id;
		(*edges)[pair<int, int>(adjNode->id, v->id)] = adjEdge->id;
		
		it++;
	}
	
	v->degree = (int)v->adj->size();
}



/*
 * removes references of an edge from its two end
 * vertices
 */
void EulerianPath::removeEdge(int e, int s, int t){
	
	Vertex * src = (*V)[s];
	Vertex * tgt = (*V)[t];
	
	src->adj->erase(e);
	tgt->adj->erase(e);
}



/*
 * a helper function facilitating the construction
 * of the path by finding a local cycle
 */
int EulerianPath::tour(int v){
	
	int w;
	
	while (true) {
		
		if ((*V)[v]->adj->empty()){
			break;
		}
		
		w = (*V)[v]->adj->begin()->second->id;
		
		S->push(v);
		
		removeEdge((*V)[v]->adj->begin()->first, v, w);
		
		v = w;
	}
	
	return v;
}


void EulerianPath::constructPath(){
	
	int v = s;
	
	vector<int> pathNode;
	
	pathNode.push_back(s);
	
	while (tour(v) == v && !S->empty()) {
	
		v = S->top();
		S->pop();
		
		pathNode.push_back(v);
	}
	
	for (int i = 0; i < (int)pathNode.size()-1; i++){
		path->push_back((*edges)[pair<int, int>(pathNode.at(i), pathNode.at(i+1))]);
	}
}



/*
 * checks for the parity of all vertices's degrees
 * 
 * returns true if all degree other than d(s), d(t) 
 * are even and d(s)+d(t) is even
 */
bool EulerianPath::isEulerian(){
	
	int temp = (*V)[s]->degree + (*V)[t]->degree;
	
	if ( (temp%2) != 0 ){
		return false;
	}
	
	Vertex * v;
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()) {
		
		v = it->second;
		if ( (v->degree % 2) != 0 ){
			
			if (v->id != s && v->id != t){
				return false;
			}
		}
		
		it++;
	}
	
	return true;
}



int EulerianPath::solve(){
	
	if (isEulerian()){
		
		constructPath();
		
		return 1;
	}
	
	return 0;
}









