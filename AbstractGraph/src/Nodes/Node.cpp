

#include "../../include/Nodes/Node.h"

Node::Node(int id):AbstractNode(id){
	
	this->degree = 0;
	
	neighborhood = new map<int, Node*>;
	
	adjacent = new map<int, Edge*>;
}

Node::~Node(){
	
	delete neighborhood;
	delete adjacent;
}

int Node::addAdjacent(Edge * adj, Node * neighbor){
	
	(*adjacent)[adj->id] = adj;
	
	(*neighborhood)[neighbor->id] = neighbor;
	
	return 0;
}

int Node::removeAdjacent(Edge * adj, Node * neighbor){
	
	adjacent->erase(adjacent->find(adj->id));
	
	neighborhood->erase(neighborhood->find(neighbor->id));
	
	return 0;
}

void Node::printNode(){
	printf("Node: %i || n : ", id);

	map<int, Node*>::iterator it = neighborhood->begin();
	
	while (it != neighborhood->end()){
		
		printf("%i ", it->first);
		
		it++;
	}
	
	printf("\n");
}

