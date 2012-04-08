#include "../../include/Algorithms/Dijkstra.h"

using namespace std;


Dijkstra::Dijkstra(int s, int t, AbstractGraph * g, vector<int> * path){
	G = new priority_queue<Vertex*, vector<Vertex*>, comp>();
}

int Dijkstra::solve(){
    
	//	init src node
    s->dist = 0;
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
        
        int adjCount = u->adj->size();
        int uwCost = 0;
        Vertex * w = NULL;
        
		//	for each adjacent node:
        for (int i = 0; i < adjCount; i++){
            w = u->adj->at(i);
            uwCost = u->cost->at(i);
            
			//	if w is unvisited, update corresponding
			//	values of w depending on prim or dijkstra
            if ( !w->visited ){
				handleUnvisited(uwCost, w, u);
				refreshMin(G);
            }
        }
    }
	
	return 0;
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