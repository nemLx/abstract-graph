#include "../../include/Algorithms/Prim.h"

using namespace std;

Prim::Prim(AbstractGraph * g, vector<int> * path){
	
	G = new priority_queue<Vertex*, vector<Vertex*>, comp>();
	
	V = new map<int, Vertex*>;
	
	this->path = path;
	
	this->g = g;
	
	initVertices();
}


void Prim::initVertices(){
	
	map<int, AbstractNode*> * N = g->getNodes();
	
	map<int, AbstractNode*>::iterator itNode = N->begin();
	
	s = itNode->first;
	
	while ( itNode != N->end() ){
		(*V)[itNode->first] = initVertex(itNode->second);
		itNode++;
	}
	
	
	
	map<int, Vertex*>::iterator itVertex = V->begin();
	
	while (itVertex != V->end()){
		
		Vertex * vertex = itVertex->second;
		
		AbstractNode * node = (*N)[itVertex->first];
		
		map<AbstractEdge*, AbstractNode*> * adjacent = node->getAdjacent();
		
		map<AbstractEdge*, AbstractNode*>::iterator itAdj = adjacent->begin();
		
		while (itAdj != adjacent->end()) {
			
			// an adjacent edge
			AbstractEdge * edge = itAdj->first;
			
			AbstractNode * to = edge->getTo();
			
			map<int, Vertex*>::iterator curr = vertex->adj->find(to->id);
			
			if (curr == vertex->adj->end()){
				
				// this node has not been included
				
				(*vertex->adj)[to->id] = (*V)[to->id];
				
				(*vertex->cost)[to->id] = edge->value;
				
				(*vertex->edgeId)[to->id] = edge->id;
				
			}else{
				
				if ((*vertex->cost)[to->id] > edge->value) {
					(*vertex->cost)[to->id] = edge->value;
					(*vertex->edgeId)[to->id] = edge->id;
				}
			}
			
			itAdj++;
		}
		
		G->push(itVertex->second);
		
		itVertex++;
	}
}


Prim::Vertex * Prim::initVertex(AbstractNode * node){
	Vertex * v = new Vertex();
    
    v->id = node->id;
    v->adj = new map<int, Vertex*>;
    v->cost = new map<int, int>;
    v->visited = false;
    v->dist = INFINITY;
    v->next = NULL;
    v->edgeId = new map<int, int>;
	
    return v;
}


int Prim::solve(){
    
	//	init src node
    (*V)[s]->dist = 0;
    refreshMin(G);
    
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
			//	values of w depending on prim or Prim	
			w = it->second;
			uwCost = (*u->cost)[it->first];
			
			if ( !w->visited ){
				handleUnvisited(uwCost, w, u);
            }
			
			it++;
		}
		
		refreshMin(G);
    }
	
	return constructMST();
}

void Prim::handleUnvisited(int uwCost, Vertex * w, Vertex * u){
	if (w->dist > uwCost){
		w->dist = uwCost;
		w->next = u;
	}
}

void Prim::refreshMin(priority_queue<Vertex*, vector<Vertex*>, comp> * G){
	Vertex * v = G->top();
    G->pop();
    G->push(v);
}


int Prim::constructMST(){
	
	int totalWeight = 0;
	
	map<int, Vertex*>::iterator it = V->begin();
	
	while (it != V->end()) {
		
		if (it->second->next == NULL){
			it++;
			continue;
		}
		
		Vertex * curr = it->second;
		
		path->push_back((*((*V)[curr->next->id])->edgeId)[curr->id]);
		
		totalWeight += (*((*V)[curr->next->id])->cost)[curr->id];
		
		it++;
	}
	
	return totalWeight;
}












