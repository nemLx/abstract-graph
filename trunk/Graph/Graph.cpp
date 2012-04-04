#include "Graph.h"

using namespace std;

Graph::Graph(int numNodes){

	n = 0;
	m = 0;
	N = new vector<Node*>();
	E = new vector<Edge*>();

	while (n < numNodes){
		addNode();
	}
}

Graph::~Graph(){
	
}

int Graph::addNode(){

	Node * newNode = new Node(n);
	N->push_back(newNode);
	n++;
	
	return n;
}

int Graph::addEdge(int from, int to, int directed){

	// return -1 if end points out of bound
	if (from >= n || to >= n){
		return -1;
	}

	Edge * newEdge = new Edge(m, N->at(from), N->at(to), directed);
	E->push_back(newEdge);
	m++;
	
	return m;
}

int Graph::removeNode(int id){
	if (!exists(id, 1)){
		return 0;
	}else{
		delete N->at(id);
		N->at(id) = NULL;
		n--;
	}
}

int Graph::removeEdge(int id){
	if (!exists(id, 0)){
		return 0;
	}else{
		delete E->at(id);
		E->at(id) = NULL;
		m--;
	}
}

int Graph::setNodeWeight(int id, int weight){
	if (!exists(id, 1) || weight < 0){
		return 0;
	}else{
		N->at(id)->weight = weight;
	}
}

int Graph::setEdgeWeight(int id, int weight){
	if (!exists(id, 0) || weight < 0){
		return 0;
	}else{
		E->at(id)->weight = weight;
	}
}

int Graph::setEdgeCapacity(int id, int capacity){
	if (!exists(id, 0) || capacity < 0){
		return 0;
	}else{
		E->at(id)->capacity = capacity;
	}
}

int Graph::setEdgeDirection(int id, int from, int to){

}

int Graph::shortestPath(int s, int t, vector<int> * path){
	return -1;
}

int Graph::MST(vector<int> * edges){
	return -1;
}

int Graph::maxMatching(vector<int> * matching){
	return -1;
}

int Graph::minVertexCover(vector<int> * cover){
	return -1;
}

void Graph::printGraph(){
	for (int i = 0; i < n; i++){
		if (N->at(i) != NULL){
			N->at(i)->printNode();
		}
	}
}

bool Graph::exists(int id, int isNode){
	if (isNode == 1){
		if (id >= n){
			return false;
		}else{
			if (N->at(id) != NULL){
				return true;
			}else{
				return false;
			}
		}
	}else if (isNode == 0){
		if (id >= m){
			return false;
		}else{
			if (E->at(id) != NULL){
				return true;
			}else{
				return false;
			}
		}
	}else{
		return false;
	}
}
