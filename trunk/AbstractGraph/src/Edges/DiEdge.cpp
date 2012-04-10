
#include "../../include/Edges/DiEdge.h"

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