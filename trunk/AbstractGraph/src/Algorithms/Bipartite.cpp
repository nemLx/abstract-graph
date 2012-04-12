//
//  Bipartite.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/9/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/Bipartite.h"

using namespace std;



Bipartite::Bipartite(Graph * g, vector<int> * partX, vector<int> * partY){
	
	this->g = g;
	
	this->partX = partX;
	
	this->partY = partY;
	
	Q = NULL;
	
	V = new map<int, Vertex*>;
	
	parity = 0;
	
	initVertexStructure();
}



Bipartite::~Bipartite(){
	
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()) {
		delete it->second->adj;
		
		delete it->second;
		it++;
	}
	
	delete V;
}



void Bipartite::initVertexStructure(){
	
	initVertices();
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()){
		
		Vertex * vertex = it->second;
		
		AbstractNode * node = (*N)[it->first];
		
		initAdjacent(vertex, node);
		
		it++;
	}
}



void Bipartite::initVertices(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, AbstractNode*>::iterator it = N->begin();
	
	while ( it != N->end() ){
		(*V)[it->first] = initVertex(it->second);
		it++;
	}
}



void Bipartite::initAdjacent(Vertex *v, AbstractNode *n){
	
	map<AbstractEdge*, AbstractNode*> * adjacent = n->getAdjacent();
	map<AbstractEdge*, AbstractNode*>::iterator it = adjacent->begin();
	
	while (it != adjacent->end()) {
		
		AbstractNode * to = it->second;
		map<int, Vertex*>::iterator curr = v->adj->find(to->id);
		
		if (curr == v->adj->end()){
			
			// only register neighbor if this vertex has not been visited
			// before, since bipartite only care about neighbor, not edge cost
			(*v->adj)[to->id] = (*V)[to->id];
		}
		
		it++;
	}
}



Bipartite::Vertex * Bipartite::initVertex(AbstractNode *n){
	
	Vertex * v = new Vertex();
	
	v->id = n->id;
	v->state = UNEXPLORED;
	v->partition = N;
	v->adj = new map<int, Vertex*>;
	
	return v;
}



int Bipartite::solve(){
	
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()){
		
		if (it->second->state == EXPLORED){
			it++;
			continue;
		}
			
		if (!solve(it->second)){
			return 0;
		}
		it++;
	}
	
	constructSets();
	
	return 1;
}



bool Bipartite::solve(Vertex *root){
	
	reset(root);
	
	Vertex * u;
	Vertex * v;
	
	while (!Q->empty()){
		
		u = Q->front();
		map<int, Vertex*>::iterator it = u->adj->begin();
		
		while (it != u->adj->end()){
			
			v = it->second;
			
			if (u->partition == v->partition){
				return false;
			}else if (v->state == UNEXPLORED){
				v->state = EXPLORING;
				v->partition = otherPartition(u);
				Q->push(v);
			}
			
			it++;
		}
		
		u->state = EXPLORED;
		Q->pop();
	}
	
	return true;
}



void Bipartite::reset(Vertex *root){
	
	parity = (parity+1)%2;
	
	root->state = EXPLORING;
	
	if (parity){
		root->partition = X;
	}else{
		root->partition = Y;
	}

	delete Q;
	Q = new queue<Vertex*>;
	Q->push(root);
}



Bipartite::Partition Bipartite::otherPartition(Vertex * v){
	
	if (v->partition == X){
		return Y;
	}else{
		return X;
	}
}



void Bipartite::constructSets(){
	
	Vertex * curr;
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()){
		
		curr = it->second;
		
		if (curr->partition == X){
			partX->push_back(curr->id);
		}else{
			partY->push_back(curr->id);
		}
		
		it++;
	}
}








