//
//  AbstractGraph.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/7/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Graphs/AbstractGraph.h"
#include "../../include/Algorithms/Dijkstra.h"
#include "../../include/Algorithms/Prim.h"
#include "../../include/Algorithms/FordFulkerson.h"

using namespace std;


AbstractGraph::AbstractGraph(){
	
	n = 0;
	m = 0;
	nCounter = 0;
	mCounter = 0;
}



int AbstractGraph::setEdgeValue(int id, int v){
	
	if(!validEdge(id)){
		return 0;
	}else{
		(*E)[id]->value = v;
		return 1;
	}
}



bool AbstractGraph::validEdge(int id){
	
	if (E->find(id) == E->end()){
		return false;
	}else{
		return true;
	}
}

bool AbstractGraph::validNode(int id){
	
	if (N->find(id) == N->end()){
		return false;
	}else{
		return true;
	}
}



int AbstractGraph::removeEdge(int id){
	
	if (!validEdge(id)){
		return 0;
	}else{
		delete (*E)[id];
		E->erase(E->find(id));
		m--;
		return 1;
	}
}



bool AbstractGraph::isDirected(){
	
	return directed;
}



map<int, AbstractNode*> * AbstractGraph::getNodes(){
	
	return N;
}



map<int, AbstractEdge*> * AbstractGraph::getEdges(){
	
	return E;
}



void AbstractGraph::printGraph(){
	
	map<int, AbstractNode*>::iterator itN = N->begin();
	
	while (itN != N->end()) {
		itN->second->printNode();
		
		itN++;
	}
	
	map<int, AbstractEdge*>::iterator itE = E->begin();
	
	while (itE != E->end()) {
		itE->second->printEdge();
		
		itE++;
	}
}



int AbstractGraph::shortestPath(int s, int t, vector<int> * path){
	
	Dijkstra spSolver(s, t, this, path);
	
	return spSolver.solve();
}



