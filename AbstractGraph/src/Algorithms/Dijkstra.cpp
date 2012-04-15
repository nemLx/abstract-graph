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
	
	Q = new set<Vertex*, comp>;
	
	this->s = s;
	
	this->t = t;
	
	this->path = path;
	
	this->g = g;
	
	initVertexStructure();
}



Dijkstra::~Dijkstra(){
	
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()) {
		
		delete it->second->adj;
		delete it->second->cost;
		delete it->second->edgeId;
		delete it->second;
		
		it++;
	}
	
	delete V;
	delete G;
}



/*
 * initializes the vertex structure, mirroing the
 * nodes and adajcents in the original graph
 */
void Dijkstra::initVertexStructure(){
	
	initVertices();
	
	map<int, AbstractNode*> * N = g->getNodes();
	map<int, Vertex*>::iterator itVertex = V->begin();
	
	while (itVertex != V->end()){
		
		Vertex * vertex = itVertex->second;
		AbstractNode * node = (*N)[itVertex->first];
		
		/*
		 * according to the adjacent structure
		 * in the original graph, initialize
		 * the adjacents for all vertices
		 */
		initAdjacent(vertex, node);
		
		//G->push(vertex);
		//H->push(vertex);
		Q->insert(vertex);
		
		itVertex++;
	}
}



/*
 * create a new vertex for each node in g
 */
void Dijkstra::initVertices(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	
	map<int, AbstractNode*>::iterator itNode = N->begin();
	
	while ( itNode != N->end()){
		(*V)[itNode->first] = initVertex(itNode->second);
		
		//if (!itNode->second->getAdjacent()->empty()){
			printf("%i\n", itNode->first);
		//}
		
		itNode++;
	}
}



/*
 * populate adj for each vertex according to
 * adjacents in the original graph
 * 
 * adjacents is defined only for reachable nodes
 */
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



/*
 * initializes a new vertex
 */
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
    
	if (s == t){
		return 0;
	}
	
	//	init src node
    (*V)[s]->dist = 0;
    refreshMin((*V)[s]);
    
	//	keep updating distances while there is node left
   // while (G->size() > 0){
		while (!Q->empty()){
			
		
		//Vertex * u = G->top();
		Vertex * u = *(Q->begin());
			
		//	the node with smallest cost is dist, meaning
		//	it is disconnected from the src, break
        if (u->dist == INFINITY){
			printf("break: %i\n", u->id);
            break;
        }
        
		//	mark visited, and remove from queue
        u->visited = true;
        //G->pop();
		Q->erase(Q->begin());
		
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
				// update the priority queue
				refreshMin(w);
				
//				if (w->id == 5){
//				
//					while (!G->empty()){
//						Vertex * q = G->top();
//						G->pop();
//						
//						printf("q: %i\n", q->dist);
//					}
//					
//				}
				
				
				
            }
			//refreshMin();
			it++;
		}
    }
	
	// construct the path and return the distance from t
	return constructPath();
}



void Dijkstra::handleUnvisited(int uwCost, Vertex * w, Vertex * u){
	
	printf("w: %i  u: %i  uwC: %i\n", w->id, u->id, uwCost);
	
	if ( (u->dist + uwCost) < w->dist ){
		w->dist = u->dist + uwCost;
		w->next = u;
		printf("w newDist: %i\n", w->dist);
	}
}



void Dijkstra::refreshMin(Vertex* w){
	
//	Vertex * v = G->top();
//	
//	//printf("update v: %i, %i\n", v->id, v->dist);
//	
//    G->pop();
//    G->push(v);
//	
//	
//	v = G->top();
//	printf("update v: %i, %i\n", v->id, v->dist);
	
	Q->erase(w);
	Q->insert(w);
}



/*
 * simply constructs path form the 
 * dist and next structure after the 
 * algorithm sets them up
 */
int Dijkstra::constructPath(){
	
	/*
	 * the destination node cannot
	 * reach the source
	 */
	if ((*V)[t]->dist == INFINITY) {
		printf("no path\n");
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










