//
//  DiNode.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include "../../include/Nodes/DiNode.h"



DiNode::DiNode(int id):AbstractNode(id){
	
	inDegree = 0;
	
	outDegree = 0;
	
	inAdjacent = new map<DiEdge*, DiNode*>;
	
	outAdjacent = new map<DiEdge*, DiNode*>;
}



DiNode::~DiNode(){
	
	delete inAdjacent;
	
	delete outAdjacent;
}



int DiNode::addInAdjacent(DiEdge * adj, DiNode * neighbor){
	
	(*inAdjacent)[adj] = neighbor;
	
	return 0;
}



int DiNode::removeInAdjacent(DiEdge * adj, DiNode * neighbor){
	
	inAdjacent->erase(inAdjacent->find(adj));
	
	return 0;
}



int DiNode::addOutAdjacent(DiEdge * adj, DiNode * neighbor){
	
	(*outAdjacent)[adj] = neighbor;
	
	return 0;
}



int DiNode::removeOutAdjacent(DiEdge * adj, DiNode * neighbor){
	
	outAdjacent->erase(outAdjacent->find(adj));
	
	return 0;
}



map<AbstractEdge*, AbstractNode*> * DiNode::getAdjacent(){
	
	return (map<AbstractEdge*, AbstractNode*> *)outAdjacent;
}



map<DiEdge*, DiNode*> * DiNode::getInAdjacent(){
	
	return inAdjacent;
}



void DiNode::printNode(){
	
	printf("Node: %i || n : ", id);
	
	map<DiEdge*, DiNode*>::iterator it = outAdjacent->begin();
	
	while (it != outAdjacent->end()){
		
		printf("%i ", it->second->id);
		
		it++;
	}
	
	printf("\n");
}







