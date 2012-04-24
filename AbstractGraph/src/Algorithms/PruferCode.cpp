//
//  PruferCode.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/18/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/PruferCode.h"



PruferCode::PruferCode(Graph * g, vector<int> * code){
	
	constructHelper(g, code);
	
	n = (int)code->size() + 2;
	
	decoding = true;
}



PruferCode::PruferCode(Graph * g, vector<int> * code, map<int, int> * label){
	
	constructHelper(g, code);
	
	V = g->getNodes();
	
	visited = new map<int, bool>;
	
	adjacents = new map<int, int>;
	
	this->label = label;
	
	decoding = false;
	
	init();
}



void PruferCode::constructHelper(Graph * g, vector<int> * code){
	
	this->g = g;
	
	this->code = code;
	
	degree = new map<int, int>;
	
	leaves = new set<int>;
}



/*
 * initializes the order and preorder low number
 * of each vertex
 */
void PruferCode::init(){
	
	int counter = 0;
	map<int, AbstractNode*>::iterator it = V->begin();
	
	while ( it != V->end() ){
		
		int currId = it->second->id;
		
		(*visited)[currId] = false;
		(*adjacents)[currId] = 0;
		(*label)[currId] = ++counter;
		(*degree)[(*label)[currId]] = (int)it->second->getAdjacent()->size();
		
		it++;
	}
}



/*
 * performs DFS on all vertices, given a root
 * and initializes all leaves
 *
 * returns the total number of nodes visited
 */
int PruferCode::dfs(int v){
	
	if ((*visited)[v]){
		return 0;
	}
	
	map<AbstractEdge*, AbstractNode*> * adj = (*V)[v]->getAdjacent();
	map<AbstractEdge*, AbstractNode*>::iterator it = adj->begin();
	
	// degree of 1 indicates a leaf
	if ((int)adj->size() == 1){
		leaves->insert((*label)[v]);
	}
	
	(*visited)[v] = true;
	
	int visited = 1;
	
	while (it != adj->end()) {
		
		int w = it->second->id;
		
		(*adjacents)[(*label)[v]] += (*label)[w];
		visited += dfs(w);
		
		it++;
	}
	
	return visited;
}



/*
 * given the leaves are all found and all
 * degree and adjacency information is set,
 * extracts prufer code by the labels
 */
void PruferCode::extract(int counter){
	
	// only execute n-3 iterations, as the
	// definition of prufer code
	if (counter == (int)V->size() - 2){
		return;
	}
	
	int curr = *leaves->begin();
	int currParent = (*adjacents)[curr];
	
	// used a leaf, delete it
	leaves->erase(leaves->begin());
	
	// use a leaf's parent as the code
	code->push_back(currParent);
	
	/*
	 * update degree and adjacent label sum
	 * when degree is one, the adjacent value
	 * is simply the label the one remaining node
	 */
	(*degree)[currParent] -= 1;
	
	(*adjacents)[currParent] -= curr;
	
	if ((*degree)[currParent] == 1){
		leaves->insert(currParent);
	}
	
	extract(counter+1);
}



/*
 * a graph is a tree if and only if it is connected
 * and the number of edges is n-1
 */
bool PruferCode::isTree(){
	
	int root = V->begin()->first;
	
	int n = (int)g->getNodes()->size();
	int e = (int)g->getEdges()->size();
	
	// edge count constraint
	if (e != n-1){
		return false;
	}
	
	// all nodes must be reachable from any root
	int visited = dfs(root);
	
	return visited == n;
}



/*
 * initializes nodes for decoding
 *
 */
void PruferCode::nodeSetup(){
	
	int nCount = 0;
	
	while (nCount <= n) {
		g->addNode();
		nCount++;
	}
	
	// discard node 0 as counting from 1
	// is easier in this setting
	g->removeNode(0);
}



/*
 * initializes all initial degree info
 * and leaves for decoding
 */
void PruferCode::degreeSetup(){
	
	/*
	 * degree is set to be 1+ the number of times
	 * a node's label appeared in the code
	 */
	for (int i = 1; i <= n; i++){
		(*degree)[i] = 1;
	}
	
	for (int i = 1; i <= n-2; i++){
		(*degree)[code->at(i-1)] += 1;
	}
	
	// all nodes with degree 1 are leaves
	for (int i = 1; i <= n; i++){
		if ( (*degree)[i] == 1){
			leaves->insert(i);
		}
	}
}



/*
 * decodes a prufer code and constructs the corresponding tree
 */
int PruferCode::decode(){
	
	nodeSetup();
	degreeSetup();
	
	int j, k;
	
	for (int i = 1; i <= n-2; i++){
		
		// j is the smallest label with degree 1
		j = *leaves->begin();
		k = code->at(i-1);
		
		// once used a node of degree 1, it will never have
		// degree 1 again, therefore discarded
		leaves->erase(leaves->begin());
		g->addEdge(j, k);
		
		(*degree)[j] -= 1;
		(*degree)[k] -= 1;
		
		// new leaves may occur, take them into account
		if ((*degree)[k] == 1){
			leaves->insert(k);
		}
	}
	
	// once the loop is over, there is gurranted to
	// have exactly two nodes with degree 1 left, and they form an edge
	g->addEdge(*leaves->begin(), *leaves->rbegin());
	
	return 1;
}



/*
 * encodes a tree or return 0 when the graph is not a tree
 */
int PruferCode::encode(){
	
	if (isTree()){
		extract(0);
		return 1;
	}else{
		return 0;
	}
}



int PruferCode::solve(){
	
	if (decoding){
		return decode();
	}else{
		return encode();
	}
}







