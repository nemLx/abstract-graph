//
//  DiGraph.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include "../../include/Graphs/DiGraph.h"
#include "../../include/Algorithms/HopcroftKarp.h"
#include "../../include/Algorithms/FordFulkerson.h"
#include "../../include/Algorithms/Gabow.h"

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



DiGraph::~DiGraph(){
	
	map<int, AbstractNode*> nCopy(*N);
	
	map<int, AbstractNode*>::iterator itNode = nCopy.begin();
	
	while (itNode != nCopy.end()) {
		removeNode(itNode->second->id);
		itNode++;
	}
	
	delete N;
	delete E;
}



int DiGraph::addNode(){
	
	DiNode * newNode = new DiNode(nCounter);
	
	(*N)[nCounter] = newNode;
	
	n++;
	nCounter++;
	
	return nCounter - 1;
}



int DiGraph::addEdge(int s, int t){
	
	if (!validNode(s) || !validNode(t)){
		return -1;
	}
	
	DiNode * from = (DiNode *)(*N)[s];
	DiNode * to = (DiNode *)(*N)[t];
	
	DiEdge * newEdge = new DiEdge(mCounter, from, to, 1);
	
	(*E)[mCounter] = newEdge;
	
	m++;
	mCounter++;
	
	return mCounter - 1;
}



int DiGraph::addEdge(int s, int t, int v){
	
	if (!validNode(s) || !validNode(t)){
		return -1;
	}
	
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
		return -1;
	}else{
		
		DiNode * node = (DiNode*)(*N)[id];
		
		map<DiEdge*, DiNode*> inAdjacent (*(map<DiEdge*, DiNode*> *)(node->getInAdjacent()));
		map<DiEdge*, DiNode*> outAdjacent (*(map<DiEdge*, DiNode*> *)(node->getAdjacent()));
		
		map<DiEdge*, DiNode*>::iterator it;
		
		for (it = inAdjacent.begin(); it != inAdjacent.end(); it++){
			removeEdge(it->first->id);
		}
		
		for (it = outAdjacent.begin(); it != outAdjacent.end(); it++){
			removeEdge(it->first->id);
		}
		
		N->erase(N->find(id));
		
		delete node;
		
		n--;
		
		return 1;
	}
}



int DiGraph::maxFlowMinCut(int s, int t, vector< pair<int, int> > * edgeFlow, vector<int> * cutEdges){
	
	if (s == t){
		return 0;
	}
	
	FordFulkerson maxFlowMinCutSolver(this, s, t, edgeFlow, cutEdges);
	
	return maxFlowMinCutSolver.solve();
}



int DiGraph::getSCs(map<int, int> * scMap){
	
	Gabow scFinder(this, scMap);
	
	return scFinder.solve();
}








