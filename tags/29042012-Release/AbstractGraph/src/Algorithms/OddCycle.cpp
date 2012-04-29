//
//  OddCycle.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/17/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/OddCycle.h"

OddCycle::OddCycle(Graph * g, vector<int> * cycle){
	
	this->g = g;
	
	this->cycle = cycle;
	
	V = new map<int, Vertex*>;
	
	Q = new queue<Vertex*>;
	
	mappedEdges = new map<pair<int, int>, int>;
	
	initVertexStructure();
}



OddCycle::~OddCycle(){
	
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()) {
		delete it->second->adj;
		
		delete it->second;
		it++;
	}
	
	delete V;
	delete Q;
	delete mappedEdges;
}



/*
 * initializes the vertex structure, mirroing the
 * nodes and adajcents in the original graph
 */
void OddCycle::initVertexStructure(){
	
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
void OddCycle::initVertices(){
	
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
void OddCycle::initAdjacent(Vertex *v, AbstractNode *n){
	
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
			(*mappedEdges)[pair<int, int>(v->id, to->id)] = it->first->id;
			(*mappedEdges)[pair<int, int>(to->id, v->id)] = it->first->id;
		}
		
		it++;
	}
}



/*
 * initializes a new vertex
 */
OddCycle::Vertex * OddCycle::initVertex(AbstractNode *n){
	
	Vertex * v = new Vertex();
	
	v->id = n->id;
	v->previous = -1;
	v->state = UNEXPLORED;
	v->partition = N;
	v->adj = new map<int, Vertex*>;
	
	return v;
}



int OddCycle::solve(){
	
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
		 * find odd cycle,
		 * construct and return its length
		 */
		if (foundOddCycle(curr)){
			return constructCycle();
		}
		
		it++;
	}
	
	/*
	 * no odd cycle
	 */
	return 0;
}



/*
 * preps the queue and the parity bit
 */
void OddCycle::reset(Vertex *root){
	
	root->state = EXPLORING;
	
	root->partition = X;
	
	delete Q;
	Q = new queue<Vertex*>;
	Q->push(root);
}



OddCycle::Partition OddCycle::otherPartition(Vertex * v){
	
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
bool OddCycle::foundOddCycle(Vertex *root){
	
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
				 * found odd cycle, record u, v
				 * and return true
				 */
				cycle->push_back(u->id);
				cycle->push_back(v->id);
				return true;
			}else if (v->state == UNEXPLORED){
				
				v->state = EXPLORING;
				v->partition = otherPartition(u);
				v->previous = u->id;
				Q->push(v);
			}
			
			it++;
		}
		
		u->state = EXPLORED;
		
		Q->pop();
	}
	
	return false;
}



int OddCycle::constructCycle(){
	
	Vertex * u = (*V)[cycle->at(0)];
	Vertex * v = (*V)[cycle->at(1)];
	
	cycle->erase(cycle->begin());
	cycle->erase(cycle->begin());
	
	cycle->push_back((*mappedEdges)[pair<int, int>(u->id, v->id)]);
	
	int uPrev = u->previous; 
	int vPrev = v->previous;
	
	while (uPrev != -1){
		
		cycle->push_back((*mappedEdges)[pair<int, int>(u->id, uPrev)]);
		cycle->push_back((*mappedEdges)[pair<int, int>(v->id, vPrev)]);
		
		u = (*V)[uPrev];
		v = (*V)[vPrev];
		
		uPrev = u->previous;
		vPrev = v->previous;
	}
	
	return (int)cycle->size();
}













