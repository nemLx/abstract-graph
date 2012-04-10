#include "../../include/Nodes/DiNode.h"



DiNode::DiNode(int id):AbstractNode(id){
	
	inDegree = 0;
	
	outDegree = 0;
	
	inAdjacent = new map<DiEdge*, DiNode*>;
	
	outAdjacent = new map<DiEdge*, DiNode*>;
	
	//inNeighborhood = new map<int, DiNode*>;
	
	//outNeighborhood = new map<int, DiNode*>;
}



DiNode::~DiNode(){
	
	delete inAdjacent;
	
	delete outAdjacent;
	
	//delete inNeighborhood;
	
	//delete outNeighborhood;
}



int DiNode::addInAdjacent(DiEdge * adj, DiNode * neighbor){
	
	(*inAdjacent)[adj] = neighbor;
	
	//(*inNeighborhood)[neighbor->id] = neighbor;
	
	return 0;
}



int DiNode::removeInAdjacent(DiEdge * adj, DiNode * neighbor){
	
	inAdjacent->erase(inAdjacent->find(adj));
	
	//inNeighborhood->erase(inNeighborhood->find(neighbor->id));
	
	return 0;
}



int DiNode::addOutAdjacent(DiEdge * adj, DiNode * neighbor){
	
	(*outAdjacent)[adj] = neighbor;
	
	//(*outNeighborhood)[adj->id] = neighbor;
	
	return 0;
}



int DiNode::removeOutAdjacent(DiEdge * adj, DiNode * neighbor){
	
	outAdjacent->erase(outAdjacent->find(adj));
	
	//outNeighborhood->erase(outNeighborhood->find(adj->id));
	
	return 0;
}


//map<int, AbstractNode*> * DiNode::getReachable(){
//	return (map<int, AbstractNode*> *)outNeighborhood;
//}

map<AbstractEdge*, AbstractNode*> * DiNode::getAdjacent(){
	return (map<AbstractEdge*, AbstractNode*> *)outAdjacent;
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







