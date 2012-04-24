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



bool GraphicSequence::isGraphic(vector<int> * s){
	
	if ((int)s->size() == 1 && *s->begin() == 0){
		return true;
	}
	
	sort(s->begin(), s->end(), vectorReverse);
	int max = *s->begin();
	s->erase(s->begin());
	
	if ((int)s->size() < max){
		return false;
	}
	
	for (int i = 0; i < max; i++) {
		s->at(i)--;
	}
	
	return isGraphic(s);
}



void GraphicSequence::constructGraph(){
	
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



void GraphicSequence::addEdges(vector< pair<int, int> > *s){

	if ((int)s->size() == 1 && s->begin()->second == 0){
		return;
	}
	
	sort(s->begin(), s->end(), pairReverse);
	int max = s->begin()->second;
	int curr = s->begin()->first;
	s->erase(s->begin());
	
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









