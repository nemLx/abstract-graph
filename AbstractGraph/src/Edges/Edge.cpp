
#include "../../include/Edges/Edge.h"

Edge::Edge(int id, Node * s, Node * t):AbstractEdge(id){
	
	from = s;
	
	to = t;
	
	from->addAdjacent(this, to);
	
	to->addAdjacent(this, from);
}

Edge::Edge(int id, Node * s, Node * t, int v):AbstractEdge(id, v){
	
	from = s;
	
	to = t;
	
	from->addAdjacent(this, to);
	
	to->addAdjacent(this, from);
}

Edge::~Edge(){
	
	from->removeAdjacent(this, to);
	
	to->removeAdjacent(this, from);
}

void Edge::printEdge(){
	printf("Edge: %i, %i<->%i value: %i \n", id, from->id, to->id, value);
}