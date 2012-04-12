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



/*
 * initializes the vertex structure, mirroing the
 * nodes and adajcents in the original graph
 */
void Bipartite::initVertexStructure(){
	
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
void Bipartite::initVertices(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, AbstractNode*>::iterator it = N->begin();
	
	while ( it != N->end() ){
		(*V)[it->first] = initVertex(it->second);
		it++;
	}
}



/*
 * populate adj for each vertex according to
 * adjacents in the original graph
 * 
 * adjacents is defined only for reachable nodes
 */
void Bipartite::initAdjacent(Vertex *v, AbstractNode *n){
	
	map<AbstractEdge*, AbstractNode*> * adjacent = n->getAdjacent();
	map<AbstractEdge*, AbstractNode*>::iterator it = adjacent->begin();
	
	while (it != adjacent->end()) {
		
		AbstractNode * to = it->second;
		map<int, Vertex*>::iterator curr = v->adj->find(to->id);
		
		/*
		 * only register neighbor if this vertex has 
		 * not been visited before, since bipartite only 
		 * care about neighboring node, not edge
		 */
		if (curr == v->adj->end()){
			
			(*v->adj)[to->id] = (*V)[to->id];
		}
		
		it++;
	}
}



/*
 * initializes a new vertex
 */
Bipartite::Vertex * Bipartite::initVertex(AbstractNode *n){
	
	Vertex * v = new Vertex();
	
	v->id = n->id;
	v->state = UNEXPLORED;
	v->partition = N;
	v->adj = new map<int, Vertex*>;
	
	return v;
}



int Bipartite::solve(){
	
	Vertex * curr;
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()){
		
		curr = it->second;
		
		/*
		 * skip explored nodes
		 */
		if (curr->state == EXPLORED){
			it++;
			continue;
		}
		
		/*
		 * return 0 if find neighbor with same
		 * partition as a node
		 */
		if (!solve(curr)){
			return 0;
		}
		it++;
	}
	
	/*
	 * no odd cycle, construct the
	 * partite sets accordingly
	 */
	constructSets();
	
	return 1;
}



/*
 * preps the queue and the parity bit
 */
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



/*
 * starting at the root, finds a path
 * alternating between two partite sets
 * 
 * return false if no such path exists
 */
bool Bipartite::solve(Vertex *root){
	
	reset(root);
	
	Vertex * u;
	Vertex * v;
	
	while (!Q->empty()){
		
		u = Q->front();
		map<int, Vertex*>::iterator it = u->adj->begin();
		
		/*
		 * for each vertex adjacent to u
		 */
		while (it != u->adj->end()){
			
			v = it->second;
			
			if (u->partition == v->partition){
				/*
				 * return false since a neighbor is found
				 * to be in the same partite set
				 */
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



/*
 * simply fills the partite sets with node ids
 * based on their partition assignment
 */
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








