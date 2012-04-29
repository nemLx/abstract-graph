//
//  GraphicSequence.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/23/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Algorithms/GraphicSequence.h"



GraphicSequence::GraphicSequence(Graph * g, vector<int> * seq){
	
	this->g = g;
	this->seq = seq;
	
	n = (int)seq->size();
}



/*
 * Recursively checking graphic sequence satisfiability
 * by removing the maximum degree d and subtracting 1 from
 * next d largest numbers
 */
bool GraphicSequence::isGraphic(vector<int> * s){
	
	// base case, one node, degree 0
	if ((int)s->size() == 1 && *s->begin() == 0){
		return true;
	}
	
	if (s->empty()){
		return false;
	}
	
	// sort, retrieve max and remove max
	sort(s->begin(), s->end(), vectorReverse);
	int max = *s->begin();
	s->erase(s->begin());
	
	// no enough nodes left, not graphic
	if ((int)s->size() < max){
		return false;
	}
	
	// enough nodes left, reduce degree and recurse
	for (int i = 0; i < max; i++) {
		s->at(i)--;
	}
	
	return isGraphic(s);
}



/*
 * constructs the simple graph when seq is determined
 * to be graphic
 */
void GraphicSequence::constructGraph(){
	
	// maps the initial indices to each node
	vector< pair<int, int> > degreeList;
	
	for (int i = 0; i < n; i++) {
		degreeList.push_back(pair<int, int>(i, seq->at(i)));
	}
	
	addNodes();
	addEdges(&degreeList);	
}



void GraphicSequence::addNodes(){
	
	for (int i = 0; i < n; i++) {
		g->addNode();
	}
}



/*
 * recursively add edges between the node with
 * highest degree d and the next d largest nodes
 */
void GraphicSequence::addEdges(vector< pair<int, int> > *s){

	// single isolated nodes, base case
	if ((int)s->size() == 1 && s->begin()->second == 0){
		return;
	}
	
	sort(s->begin(), s->end(), pairReverse);
	int max = s->begin()->second;
	int curr = s->begin()->first;
	s->erase(s->begin());
	
	// add max edges with the next max nodes 
	for (int i = 0; i < max; i++) {
		s->at(i).second--;
		g->addEdge(curr, s->at(i).first);
	}
	
	addEdges(s);
}



int GraphicSequence::solve(){
	
	vector<int> s (*seq);
	
	if ( isGraphic(&s) ){
		constructGraph();
		return 1;
	}else{
		return 0;
	}
}









