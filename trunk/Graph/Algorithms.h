#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include <limits.h>
#include <vector>
#include <queue>

#define INFINITY INT_MAX

using namespace std;

namespace Algorithms{

	namespace Dijkstra{
		struct Vertex {
            int id;
			vector<Vertex*> * adj;
            vector<int> * cost;
			bool visited;
			int dist;
			Vertex * next;
		};
        
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

		int dijkstra(bool isPrim, Vertex * s, priority_queue<Vertex*, vector<Vertex*>, comp> * G);
		
		void refreshMin(priority_queue<Vertex*, vector<Vertex*>, comp> * G);
	}

}

#endif
