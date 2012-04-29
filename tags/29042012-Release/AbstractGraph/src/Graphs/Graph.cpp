//
//  Graph.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/7/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>
#include "../../include/Graphs/Graph.h"
#include "../../include/Algorithms/Bipartite.h"
#include "../../include/Algorithms/FordFulkerson.h"
#include "../../include/Algorithms/HopcroftKarp.h"
#include "../../include/Algorithms/Prim.h"
#include "../../include/Algorithms/OddCycle.h"
#include "../../include/Algorithms/EulerianPath.h"
#include "../../include/Algorithms/Bridge.h"
#include "../../include/Algorithms/PruferCode.h"
#include "../../include/Algorithms/FloydWarshall.h"
#include "../../include/Algorithms/GraphicSequence.h"

using namespace std;



Graph::Graph():AbstractGraph(){
	
	directed = false;
	
	N = new map<int, AbstractNode*>;
	E = new map<int, AbstractEdge*>;
}



Graph::Graph(int nodeCount):AbstractGraph(){
	
	directed = false;
	
	N = new map<int, AbstractNode*>;
	E = new map<int, AbstractEdge*>;
	
	while (n < nodeCount){
		addNode();
	}
}



Graph::~Graph(){
	
	map<int, AbstractNode*> nCopy(*N);
	map<int, AbstractNode*>::iterator itNode = nCopy.begin();
	
	while (itNode !=nCopy.end()) {
		removeNode(itNode->second->id);
		itNode++;
	}
	
	delete N;
	delete E;
}



int Graph::addNode(){
	
	Node * newNode = new Node(nCounter);
	
	(*N)[nCounter] = newNode;
	
	n++;
	nCounter++;
	
	return nCounter - 1;
}



int Graph::addEdge(int s, int t){
	
	if (!validNode(s) || !validNode(t)){
		return -1;
	}
	
	Node * from = (Node *)(*N)[s];
	Node * to = (Node *)(*N)[t];
	
	Edge * newEdge = new Edge(mCounter, from, to, 1);
	
	(*E)[mCounter] = newEdge;
	
	m++;
	mCounter++;
	
	return mCounter - 1;
}



int Graph::addEdge(int s, int t, int v){
	
	if (!validNode(s) || !validNode(t)){
		return -1;
	}
	
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
		return -1;
	}else{
		
		Node * node = (Node*)(*N)[id];
		
		map<Edge*, Node*> adjacent (*(map<Edge*, Node*> *)(node->getAdjacent()));
		
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



int Graph::mst(vector<int> * edges){
	
	Prim mstSolver(this, edges);
	
	return mstSolver.solve();
}



int Graph::bipartite(vector<int> * setX, vector<int> * setY){
	
	Bipartite bpSolver(this, setX, setY);
	
	return bpSolver.solve();
}



int Graph::maxMatching(vector<int> * matching){
	
	vector<int>	partX;
	vector<int> partY;
	
	if (this->bipartite(&partX, &partY)){
		HopcroftKarp mmSolver(this, &partX, &partY, matching);
		return mmSolver.solve();
	}else{
		return -1;
	}
}



int Graph::getOddCycle(vector<int> *cycle){
	
	OddCycle oddCycleSolver(this, cycle);
	
	return oddCycleSolver.solve();
}



bool Graph::eulerianPath(int s, int t, vector<int> * path){
	
	EulerianPath eulerianSolver(this, s, t, path);
	
	return eulerianSolver.solve();
}



int Graph::getBridges(vector<int> *bridges){
	
	Bridge bridgeSolver(this, bridges);
	
	return bridgeSolver.solve();
}



int Graph::getPruferCode(vector<int> * code, map<int, int> * label){
	
	PruferCode gen(this, code, label);
	
	return gen.solve();
}



void Graph::buildFromPruferCode(vector<int> *code){
	
	PruferCode builder(this, code);
	
	builder.solve();
}



void Graph::allPairSP(map<pair<int, int>, int> *path, map<pair<int, int>, int> *dist){
	
	FloydWarshall spSolver(this, path, dist);
	
	spSolver.solve();
}



int Graph::buildFromSequence(vector<int> *sequence){
	
	GraphicSequence gsBuilder(this, sequence);
	
	return gsBuilder.solve();
}











