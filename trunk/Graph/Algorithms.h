#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include <vector>
#include <queue>

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

		int dijkstra(Vertex * s, priority_queue<Vertex*, vector<Vertex*>, comp> * G);
	}

}

#endif
