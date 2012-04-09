#include "../../include/Nodes/DiNode.h"



DiNode::DiNode(int id):AbstractNode(id){
	
	inDegree = 0;
	
	outDegree = 0;
	
	inAdjacent = new map<int, DiEdge*>;
	
	outAdjacent = new map<int, DiEdge*>;
	
	inNeighborhood = new map<int, DiNode*>;
	
	outNeighborhood = new map<int, DiNode*>;
}



DiNode::~DiNode(){
	
	delete inAdjacent;
	
	delete outAdjacent;
	
	delete inNeighborhood;
	
	delete outNeighborhood;
}



int DiNode::addInAdjacent(DiEdge * adj, DiNode * neighbor){
	
	(*inAdjacent)[adj->id] = adj;
	
	(*inNeighborhood)[neighbor->id] = neighbor;
	
	return 0;
}



int DiNode::removeInAdjacent(DiEdge * adj, DiNode * neighbor){
	
	inAdjacent->erase(inAdjacent->find(adj->id));
	
	inNeighborhood->erase(inNeighborhood->find(neighbor->id));
	
	return 0;
}



int DiNode::addOutAdjacent(DiEdge * adj, DiNode * neighbor){
	
	(*outAdjacent)[adj->id] = adj;
	
	(*outNeighborhood)[neighbor->id] = neighbor;
	
	return 0;
}



int DiNode::removeOutAdjacent(DiEdge * adj, DiNode * neighbor){
	
	outAdjacent->erase(outAdjacent->find(adj->id));
	
	outNeighborhood->erase(outNeighborhood->find(neighbor->id));
	
	return 0;
}

void DiNode::printNode(){
	
	printf("Node: %i || n : ", id);
	
	map<int, DiNode*>::iterator it = outNeighborhood->begin();
	
	while (it != outNeighborhood->end()){
		
		printf("%i ", it->first);
		
		it++;
	}
	
	printf("\n");
	
}







