//
//  Dijkstra.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Algorithm.h"

using namespace std;



class Dijkstra : public Algorithm{

public:
	
	Dijkstra(int s, int t, AbstractGraph * g, vector<int> * path);
	
	~Dijkstra();
	
	int solve();
	
private:
	
	struct Vertex {
		int id;
		
		//	pointer to adjacent vertices
		map<int, Vertex*> * adj;
		
		//	costs of each adjacent edge
		map<int, int> * cost;
		
		map<int, int> * edgeId;
		
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
	
	
	int s;
	
	int t;
	
	vector<int> * path;
	
	AbstractGraph * g;
	
	map<int, Vertex*> * V;
	
	priority_queue<Vertex*, vector<Vertex*>, comp> * G;
	
	
	
	void initVertexStructure();
	
	void initVertices();
	
	Vertex * initVertex(AbstractNode * node);
	
	void initAdjacent(Vertex * v, AbstractNode * n);
	
	void handleUnvisited(int uwCost, Vertex * w, Vertex * u);
	
	void refreshMin();
	
	int constructPath();
};

#endif
