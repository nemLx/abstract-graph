#include <vector>

#include "Algorithms.h"

using namespace std;
using namespace Algorithms;

int Dijkstra::dijkstra(Dijkstra::Vertex * s, priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G){
	
    printf("dijkstra Called \n");
    
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
        
        printf("%i \n", u->dist);
        
        if (u->dist == 999999999){
            break;
        }
        
        u->visited = true;
        G->pop();
        
        int adjCount = u->adj->size();
        int uwCost = 0;
        Dijkstra::Vertex * w = NULL;
        
        for (int i = 0; i < adjCount; i++){
            w = u->adj->at(i);
            uwCost = u->cost->at(i);
            
            if ( !w->visited ){
                if ( (u->dist + uwCost) < w->dist ){
                    w->dist = u->dist + uwCost;
                    
                    Dijkstra::Vertex * v = G->top();
                    G->pop();
                    G->push(v);
                    
                    w->next = u;
                }
            }
        }
    }
}

