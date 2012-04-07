#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include <limits.h>
#include <vector>
#include <queue>

#define INFINITY INT_MAX

using namespace std;

namespace Algorithms{

	namespace Dijkstra{
		
		/*
		 *	s vertex structure used by the Dijkstra algorithm
		 */
		struct Vertex {
            int id;
			
			//	pointer to adjacent vertices
			vector<Vertex*> * adj;
			
			//	costs of each adjacent edge
            vector<int> * cost;
			
			//	true if visited
			bool visited;
			
			//	distance to src
			int dist;
			
			//	marks a previous node in the path
			Vertex * next;
		};
        
		
		/*
		 *	comparitor for the priority queue
		 */
        class comp{
        public:
            bool operator() (Vertex * lhs, Vertex * rhs) const{
                
                if (lhs->dist > rhs->dist){
                    return true;
                }else{
                    return false;
                }
            }
        };

		
		/*
		 *	fills up the distance of each node to the src,
		 *	and determines the previous node in the path of each node
		 */
		void dijkstra(bool isPrim, Vertex * s, priority_queue<Vertex*, vector<Vertex*>, comp> * G);
		
		
		/*
		 *	updates distance/cost information of a node depending
		 *	on if running prim's or dijkstra's
		 */
		void handleUnvisited(bool isPrim, int uwCost, Dijkstra::Vertex * w, Dijkstra::Vertex * u);
		
		
		/*
		 *	updates a priority queue
		 */
		void refreshMin(priority_queue<Vertex*, vector<Vertex*>, comp> * G);
	}

}

#endif
