#include <vector>

#include "Algorithms.h"

using namespace std;
using namespace Algorithms;

int Dijkstra::dijkstra(Dijkstra::Vertex * s, priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G){
    
    s->dist = 0;
    
    Dijkstra::Vertex * v = G->top();
    G->pop();
    G->push(v);
    
//    while (G->size() > 0){
//        printf("%i \n", G->top()->dist);
//        G->pop();
//    }
    
    while (G->size() > 0){
        
        Dijkstra::Vertex * u = G->top();
        
        if (u->dist == 999999999){
            break;
            printf("broken with: %i \n", u->dist);
        }
        
        u->visited = true;
        G->pop();
        
        int adjCount = u->adj->size();
        int uwCost = 0;
        Dijkstra::Vertex * w = NULL;
        
        for (int i = 0; i < adjCount; i++){
            w = u->adj->at(i);
            uwCost = u->cost->at(i);
            
            printf("iteration: %i -- w: %i -- u: %i -- uwCost: %i \n", i, w->id, u->id, uwCost);
            
            if ( !w->visited ){
                printf("unvisited \n");
                if ( (u->dist + uwCost) < w->dist ){
                    w->dist = u->dist + uwCost;
                    
                    Dijkstra::Vertex * v = G->top();
                    G->pop();
                    G->push(v);
                    
                    w->next = u;
                    
                    printf("w->dist: %i, u->dist: %i, uwCost: %i w->next: %i \n", w->dist, u->dist, uwCost, w->next->id);
                }
            }
        }
    }
}

