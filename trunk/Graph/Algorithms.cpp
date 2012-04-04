#include <vector>

#include "Algorithms.h"

using namespace std;
using namespace Algorithms;

int Dijkstra::dijkstra(bool isPrim, Dijkstra::Vertex * s, priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G){
    
    s->dist = 0;
    
    refreshMin(G);
    
    while (G->size() > 0){
        
        Dijkstra::Vertex * u = G->top();
        
        if (u->dist == INFINITY){
            break;
            //printf("broken with: %i \n", u->dist);
        }
        
        u->visited = true;
        G->pop();
        
        int adjCount = u->adj->size();
        int uwCost = 0;
        Dijkstra::Vertex * w = NULL;
        
        for (int i = 0; i < adjCount; i++){
            w = u->adj->at(i);
            uwCost = u->cost->at(i);
            
            //printf("iteration: %i -- w: %i -- u: %i -- uwCost: %i \n", i, w->id, u->id, uwCost);
            
            if ( !w->visited ){
                //printf("unvisited \n");
				
				if (isPrim){
					if (w->dist > uwCost){
						w->dist = uwCost;
						refreshMin(G);
						w->next = u;
					}
				}else{
					if ( (u->dist + uwCost) < w->dist ){
						w->dist = u->dist + uwCost;
						refreshMin(G);
						w->next = u;
						//printf("w->dist: %i, u->dist: %i, uwCost: %i w->next: %i \n", w->dist, u->dist, uwCost, w->next->id);
					}
				}
            }
        }
    }
}

void Dijkstra::refreshMin(priority_queue<Vertex*, vector<Vertex*>, comp> * G){
	Dijkstra::Vertex * v = G->top();
    G->pop();
    G->push(v);
}


