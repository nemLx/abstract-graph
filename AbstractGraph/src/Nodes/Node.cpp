

#include "../../include/Nodes/Node.h"

Node::Node(int id):AbstractNode(id){
	
	this->degree = 0;
	
	//neighborhood = new map<int, Node*>;
	
	adjacent = new map<Edge*, Node*>;
}

Node::~Node(){
	
	//delete neighborhood;
	delete adjacent;
}

int Node::addAdjacent(Edge * adj, Node * neighbor){
	
	(*adjacent)[adj] = neighbor;
	
	//(*neighborhood)[adj->id] = neighbor;
	
	return 0;
}

int Node::removeAdjacent(Edge * adj, Node * neighbor){
	
	adjacent->erase(adjacent->find(adj));
	
	//neighborhood->erase(neighborhood->find(adj->id));
	
	return 0;
}

//map<int, AbstractNode*> * Node::getReachable(){
//	return (map<int, AbstractNode*> *)neighborhood;
//}

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

