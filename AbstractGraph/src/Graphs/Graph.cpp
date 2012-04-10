//
//  Graph.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/7/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>
#include "../../include/Graphs/Graph.h"

using namespace std;

Graph::Graph():AbstractGraph(){
	
	directed = false;
	
	N = new map<int, AbstractNode*>();
	E = new map<int, AbstractEdge*>();
}



Graph::Graph(int nodeCount):AbstractGraph(){
	
	directed = false;
	
	N = new map<int, AbstractNode*>();
	E = new map<int, AbstractEdge*>();
	
	while (n < nodeCount){
		addNode();
	}
}



int Graph::addNode(){
	
	Node * newNode = new Node(nCounter);
	
	(*N)[nCounter] = newNode;
	
	n++;
	nCounter++;
	
	return nCounter - 1;
}



int Graph::addEdge(int s, int t){
	
	Node * from = (Node *)(*N)[s];
	Node * to = (Node *)(*N)[t];
	
	Edge * newEdge = new Edge(mCounter, from, to, 1);
	
	(*E)[mCounter] = newEdge;
	
	m++;
	mCounter++;
	
	return mCounter - 1;
}



int Graph::addEdge(int s, int t, int v){
	
	Node * from = (Node *)(*N)[s];
	Node * to = (Node *)(*N)[t];
	
	Edge * newEdge = new Edge(mCounter, from, to, v);
	
	(*E)[mCounter] = newEdge;
	
	m++;
	mCounter++;
	
	return mCounter - 1;
}


int Graph::removeNode(int id){
	
	if (!validNode(id)){
		return 0;
	}else{
		
		Node * node = (Node*)(*N)[id];
		
		map<Edge*, Node*> adjacent (*(node->adjacent));
		
		map<Edge*, Node*>::iterator it;
		
		for (it = adjacent.begin(); it != adjacent.end(); it++){
			removeEdge(it->first->id);
		}
		
		N->erase(N->find(id));
		
		delete node;
		
		n--;
		
		return 1;
	}
}









