//
//  DiEdge.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include "../../include/Edges/DiEdge.h"

using namespace std;



DiEdge::DiEdge(int id, DiNode * s, DiNode * t):AbstractEdge(id){
	
	from = s;
	
	to = t;
	
	from->addOutAdjacent(this, to);
	
	to->addInAdjacent(this, from);
}



DiEdge::DiEdge(int id, DiNode * s, DiNode * t, int v):AbstractEdge(id, v){
	
	from = s;
	
	to = t;
	
	from->addOutAdjacent(this, to);
	
	to->addInAdjacent(this, from);
}



DiEdge::~DiEdge(){
	
	from->removeOutAdjacent(this, to);
	
	to->removeInAdjacent(this, from);
}



AbstractNode* DiEdge::getFrom(){
	
	return (AbstractNode*)from;
}



AbstractNode* DiEdge::getTo(){
	
	return (AbstractNode*)to;
}



void DiEdge::printEdge(){
	
	printf("DiEdge: %i, %i->%i value: %i\n", id, from->id, to->id, value);
}









