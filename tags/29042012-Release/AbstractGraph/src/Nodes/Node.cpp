//
//  Node.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include "../../include/Nodes/Node.h"

using namespace std;



Node::Node(int id):AbstractNode(id){
	
	this->degree = 0;
	
	adjacent = new map<Edge*, Node*>;
}



Node::~Node(){
	
	delete adjacent;
}



int Node::addAdjacent(Edge * adj, Node * neighbor){
	
	(*adjacent)[adj] = neighbor;
	
	return 0;
}



int Node::removeAdjacent(Edge * adj, Node * neighbor){
	
	adjacent->erase(adjacent->find(adj));
	
	return 0;
}



map<AbstractEdge*, AbstractNode*> * Node::getAdjacent(){
	
	return (map<AbstractEdge*, AbstractNode*> *)adjacent;
}



void Node::printNode(){
	
	printf("Node: %i || n : ", id);

	map<Edge*, Node*>::iterator it = adjacent->begin();
	
	while (it != adjacent->end()){
		
		printf("%i ", it->second->id);
		
		it++;
	}
	
	printf("\n");
}

