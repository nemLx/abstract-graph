//
//  AbstractGraph.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/7/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Graphs/AbstractGraph.h"


AbstractGraph::AbstractGraph(){
	n = 0;
	m = 0;
	nCounter = 0;
	mCounter = 0;
}


AbstractGraph::~AbstractGraph(){
	map<int, AbstractNode*>::iterator itNodes;
	
	for (itNodes = N->begin(); itNodes != N->end(); itNodes++){
		delete itNodes->second;
	}
	
	map<int, AbstractEdge*>::iterator itEdges;
	
	for (itEdges = E->begin(); itEdges != E->end(); itEdges++){
		delete itEdges->second;
	}
	
	delete N;
	delete E;
}


int AbstractGraph::removeNode(int id){
	if (!validNode(id)){
		return 0;
	}else{
		delete (*E)[id];
		E->erase(id);
		m--;
		return 1;
	}
}

int AbstractGraph::removeEdge(int id){
	if (!validEdge(id)){
		return 0;
	}else{
		delete (*N)[id];
		N->erase(id);
		n--;
		return 1;
	}
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
		return true;
	}else{
		return false;
	}
}

bool AbstractGraph::validNode(int id){
	if (N->find(id) == N->end()){
		return true;
	}else{
		return false;
	}
}

int AbstractGraph::shortestPath(int s, int t, vector<int> * path){
		
	Dijkstra spSolver(s, t, this, path);
	
	spSolver.solve();
	
	return 0;
}


//int AbstractGraph::addNode(){
//	return -1;
//}
//
//int AbstractGraph::addEdge(int s, int t){
//	return -1;
//}
//
//int AbstractGraph::addEdge(int s, int t, int v){
//	return -1;
//}


