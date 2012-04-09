#include "../../include/Algorithms/Dijkstra.h"

using namespace std;

Dijkstra::Dijkstra(int s, int t, AbstractGraph * g, vector<int> * path){
	
	G = new priority_queue<Vertex*, vector<Vertex*>, comp>();
	
	V = new map<int, Vertex*>;
	
	this->s = s;
	
	this->t = t;
	
	this->path = path;
	
	if (dynamic_cast<Graph*>(g) == NULL){
		
		//directed
		
		DiGraph * h = dynamic_cast<DiGraph*>(g);
		
		initDirected(s, t, h);
		
	}else{
		
		//un-directed
		
		Graph * h = dynamic_cast<Graph*>(g);
		
		initUnDirected(s, t, h);
	}
}



void Dijkstra::initDirected(int s, int t, DiGraph * g){
	
	map<int, AbstractNode*> * N = g->getNodes();
	
	
	map<int, AbstractNode*>::iterator itNode = N->begin();
	
	while ( itNode != N->end() ){
		(*V)[itNode->first] = initVertex(itNode->second);
		itNode++;
	}
	
	
	map<int, Vertex*>::iterator itVertex = V->begin();
	
	while (itVertex != V->end()){
		
		Vertex* vertex = itVertex->second;
		DiNode* node = (DiNode*)(*N)[itVertex->first];
		
		map<int, DiEdge*> * adjacent = node->outAdjacent;
		
		map<int, DiEdge*>::iterator itAdj = adjacent->begin();
		
		while (itAdj != adjacent->end()) {
			
			// an adjacent edge
			DiEdge * edge = itAdj->second;
			
			DiNode * to = edge->to;
			
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


void Dijkstra::initUnDirected(int s, int t, Graph * g){
	
	map<int, AbstractNode*> * N = g->getNodes();
	
	
	map<int, AbstractNode*>::iterator itNode = N->begin();
	
	while ( itNode != N->end() ){
		(*V)[itNode->first] = initVertex(itNode->second);
		itNode++;
	}
	
	
	map<int, Vertex*>::iterator itVertex = V->begin();
	
	while (itVertex != V->end()){
		
		Vertex* vertex = itVertex->second;
		Node* node = (Node*)(*N)[itVertex->first];

		map<int, Edge*> * adjacent = node->adjacent;
		
		map<int, Edge*>::iterator itAdj = adjacent->begin();
		
		while (itAdj != adjacent->end()) {
			
			// an adjacent edge
			Edge * edge = itAdj->second;
			
			Node * to;
			
			if (edge->to->id != node->id){
				to = edge->to;
			}else if (edge->from->id != node->id){
				to = edge->from;
			}else{
				continue;
			}
			
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


Dijkstra::Vertex * Dijkstra::initVertex(AbstractNode * node){
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


int Dijkstra::solve(){
    
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
			//	values of w depending on prim or dijkstra	
			w = it->second;
			uwCost = (*u->cost)[it->first];
			
			if ( !w->visited ){
				handleUnvisited(uwCost, w, u);
				refreshMin(G);
            }
			
			it++;
		}
    }
	
	return constructPath();
}

void Dijkstra::handleUnvisited(int uwCost, Vertex * w, Vertex * u){
	if ( (u->dist + uwCost) < w->dist ){
		w->dist = u->dist + uwCost;
		w->next = u;
	}
}

void Dijkstra::refreshMin(priority_queue<Vertex*, vector<Vertex*>, comp> * G){
	Vertex * v = G->top();
    G->pop();
    G->push(v);
}



int Dijkstra::constructPath(){
	
	map<int, int> * r;
	
	Vertex * curr = (*V)[t];
	
	r = curr->edgeId;
	
	path->push_back((*((*V)[curr->next->id])->edgeId)[curr->id]);

	while (curr->next->id != s){
		curr = (*V)[curr->next->id];
		path->push_back((*((*V)[curr->next->id])->edgeId)[curr->id]);
	}
    
	return (*V)[t]->dist;
}










