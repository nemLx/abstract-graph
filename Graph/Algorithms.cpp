#include <vector>

#include "Algorithms.h"

using namespace std;
using namespace Algorithms;

void Dijkstra::dijkstra(bool isPrim, Dijkstra::Vertex * s, priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G){
    
	//	init src node
    s->dist = 0;
    refreshMin(G);
    
	//	keep updating distances while there is node left
    while (G->size() > 0){
        
        Dijkstra::Vertex * u = G->top();
        
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
        Dijkstra::Vertex * w = NULL;
        
		//	for each adjacent node:
        for (int i = 0; i < adjCount; i++){
            w = u->adj->at(i);
            uwCost = u->cost->at(i);
            
			//	if w is unvisited, update corresponding
			//	values of w depending on prim or dijkstra
            if ( !w->visited ){
				handleUnvisited(isPrim, uwCost, w, u);
				refreshMin(G);
            }
        }
    }
}

void Dijkstra::handleUnvisited(bool isPrim, int uwCost, Dijkstra::Vertex * w, Dijkstra::Vertex * u){
	if (isPrim){
		if (w->dist > uwCost){
			w->dist = uwCost;
			w->next = u;
		}
	}else{
		if ( (u->dist + uwCost) < w->dist ){
			w->dist = u->dist + uwCost;
			w->next = u;
		}
	}
}

void Dijkstra::refreshMin(priority_queue<Vertex*, vector<Vertex*>, comp> * G){
	Dijkstra::Vertex * v = G->top();
    G->pop();
    G->push(v);
}


