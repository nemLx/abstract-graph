#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#define INFINITY 1000

#include "../Graphs/AbstractGraph.h"
#include "Algorithm.h"

using namespace std;

class AbstractGraph;

class Dijkstra : public Algorithm{

public:
	
	Dijkstra(int s, int t, AbstractGraph * g, vector<int> * path);
	
	int solve();
	
private:
	
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
	
	Vertex * s;
	
	priority_queue<Vertex*, vector<Vertex*>, comp> * G;
	
	void handleUnvisited(int uwCost, Vertex * w, Vertex * u);
	
	void refreshMin(priority_queue<Vertex*, vector<Vertex*>, comp> * G);
	
};

#endif
