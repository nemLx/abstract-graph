//
//  DiGraph.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include "../../include/Graphs/DiGraph.h"

using namespace std;

DiGraph::DiGraph():AbstractGraph(){
	
	directed = true;
	
	N = new map<int, AbstractNode*>();
	E = new map<int, AbstractEdge*>();
}



DiGraph::DiGraph(int nodeCount):AbstractGraph(){
	
	directed = true;
	
	N = new map<int, AbstractNode*>();
	E = new map<int, AbstractEdge*>();
	
	while (n < nodeCount){
		addNode();
	}
}



int DiGraph::addNode(){
	
	DiNode * newNode = new DiNode(nCounter);
	
	(*N)[nCounter] = newNode;
	
	n++;
	nCounter++;
	
	return nCounter - 1;
}



int DiGraph::addEdge(int s, int t){
	
	DiNode * from = (DiNode *)(*N)[s];
	DiNode * to = (DiNode *)(*N)[t];
	
	DiEdge * newEdge = new DiEdge(mCounter, from, to, 1);
	
	(*E)[mCounter] = newEdge;
	
	m++;
	mCounter++;
	
	return mCounter - 1;
}



int DiGraph::addEdge(int s, int t, int v){
	
	DiNode * from = (DiNode *)(*N)[s];
	DiNode * to = (DiNode *)(*N)[t];
	
	DiEdge * newEdge = new DiEdge(mCounter, from, to, v);
	
	(*E)[mCounter] = newEdge;
	
	m++;
	mCounter++;
	
	return mCounter - 1;
}



int DiGraph::removeNode(int id){
	
	if (!validNode(id)){
		return 0;
	}else{
		
		DiNode * node = (DiNode*)(*N)[id];
		
		map<int, DiEdge*> inAdjacent (*(node->inAdjacent));
		map<int, DiEdge*> outAdjacent (*(node->outAdjacent));
		
		map<int, DiEdge*>::iterator it;
		
		for (it = inAdjacent.begin(); it != inAdjacent.end(); it++){
			removeEdge(it->first);
		}
		
		for (it = outAdjacent.begin(); it != outAdjacent.end(); it++){
			removeEdge(it->first);
		}
		
		delete node;
		
		n--;
		
		return 1;
	}
}








