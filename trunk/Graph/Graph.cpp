#include "Graph.h"

using namespace std;
using namespace Algorithms;

Graph::Graph(int numNodes, int directed){

	n = 0;
	m = 0;
	this->directed = directed;
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



int Graph::addEdge(int from, int to, int weight){

	// return -1 if end points out of bound
	if (from >= n || to >= n){
		return -1;
	}

	Edge * newEdge = new Edge(m, N->at(from), N->at(to), directed);
	newEdge->setWeight(weight);
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
	}
}



int Graph::removeEdge(int id){
	if (!exists(id, 0)){
		return 0;
	}else{
		delete E->at(id);
		E->at(id) = NULL;
		return 1;
	}
}



int Graph::setNodeWeight(int id, int weight){
	if (!exists(id, 1) || weight < 0){
		return 0;
	}else{
		N->at(id)->weight = weight;
		return 1;
	}
}



int Graph::setEdgeWeight(int id, int weight){
	if (!exists(id, 0) || weight < 0){
		return 0;
	}else{
		E->at(id)->setWeight(weight);
	}
}



int Graph::setEdgeCapacity(int id, int capacity){
	if (!exists(id, 0) || capacity < 0){
		return 0;
	}else{
		E->at(id)->capacity = capacity;
		return 1;
	}
}



int Graph::setEdgeDirection(int id, int from, int to){
	if (!exists(id, 0)){
		return 0;
	}else{
		return E->at(id)->setDirection(N->at(from), N->at(to));
	}
}



int Graph::shortestPath(int s, int t, vector<int> * path){
    
	// validify
    if (path == NULL || !exists(s,1) || !exists(t,1) ){
        return -1;
    }
    
	// initialized structure needed for Dijkstra's
    priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G 
    = new priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp>();
	
	vector<Dijkstra::Vertex*> * vertices = new vector<Dijkstra::Vertex*>(n);
	
	initDijkstra(s, vertices, G);
	
	// run Dijkstra's
    Dijkstra::dijkstra(false, vertices->at(s), G);
	
	// construct path, cleanup, and return distance
	int dist = constructPath(t, vertices, path);
	
	delete vertices;
	delete G;
	
    return dist;
}



int Graph::MST(vector<int> * edges, int root){
	
	// validify
	if ( directed ){
        return 0;
    }
    
    // initialized structure needed for Dijkstra's
    priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G 
    = new priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp>();
	
	vector<Dijkstra::Vertex*> * vertices = new vector<Dijkstra::Vertex*>(n);
	
	initDijkstra(root, vertices, G);
    
	// run Dijkstra's
    Dijkstra::dijkstra(true, vertices->at(root), G);
	
	// construct tree, clean up, and return total weight
	int totalWeight = constructMST(vertices, edges);
	
	delete vertices;
	delete G;
	
	return totalWeight;
}



int Graph::constructMST(vector<Dijkstra::Vertex*> * vertices, vector<int> * edges){
	int totalWeight = 0;
	
	for (int i = 0; i < n; i++){
		if (vertices->at(i) == NULL || vertices->at(i)->next == NULL){
			continue;
		}
		
		Node * from = N->at(vertices->at(i)->id);
		Node * to	= N->at(vertices->at(i)->next->id);
		Edge * edge = getEdge(from, to);
		
		edges->push_back(edge->id);
		
		totalWeight += edge->weight;
	}
	
	return totalWeight;
}



int Graph::maxMatching(vector<int> * matching){
	return -1;
}



int Graph::minVertexCover(vector<int> * cover){
	return -1;
}



int Graph::constructPath(int t, vector<Dijkstra::Vertex*> * vertices, vector<int> * path){
	
	Dijkstra::Vertex * curr = vertices->at(t);
    path->push_back(curr->id);
    
    while (curr->next != NULL){
        curr = curr->next;
        path->push_back(curr->id);
    }
    
	return vertices->at(t)->dist;
}



void Graph::initDijkstra(
						 int s,
						 vector<Dijkstra::Vertex*> * vertices,
						 priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G)
{
    for (int i = 0; i < n; i++){
        if (N->at(i) != NULL) {
            vertices->at(i) = initDijkstraVertex(N->at(i));
        }else{
            vertices->at(i) = NULL;
        }
    }
	
	for (int i = 0; i < n; i++){
        if (vertices->at(i) != NULL){
            initDijkstraVertexAdj(vertices->at(i), vertices);
            G->push(vertices->at(i));
        }
    }
}



Dijkstra::Vertex * Graph::initDijkstraVertex(Node * node){
    Dijkstra::Vertex * v = new Dijkstra::Vertex();
    
    v->id = node->id;
    v->adj = new vector<Dijkstra::Vertex*>();
    v->cost = new vector<int>();
    v->visited = false;
    v->dist = INFINITY;
    v->next = NULL;
    
    return v;
}



void Graph::initDijkstraVertexAdj(Dijkstra::Vertex * v, vector<Dijkstra::Vertex*> * vertices){
    
    Node * node = N->at(v->id);
    
    vector<Node*> * reachables = NULL;
	vector<Edge*> * weights = NULL;
    int currId = -1;
    int degree = 0;
    
    if (directed){
        reachables = node->outNeighborhood;
		weights = node->outAdjacent;
        degree = node->outDegree;
    }else{
        reachables = node->neighborhood;
		weights = node->adjacent;
        degree = node->degree;
    }
    
    for (int i = 0; i < degree; i++) {
        currId = reachables->at(i)->id;
        v->adj->push_back(vertices->at(currId));
        v->cost->push_back( weights->at(i)->weight );
    }
}



Graph::Edge* Graph::getEdge(Node * from, Node * to){
	Edge* curr = NULL;
    
    for (int i = 0; i < m; i++){
        curr = E->at(i);
        if (from->id == curr->from->id && to->id == curr->to->id){
            return curr;
        }else if (!directed && from->id == curr->to->id && to->id == curr->from->id){
			return curr;
		}
    }
    
    return NULL;
}



void Graph::printGraph(){
	for (int i = 0; i < n; i++){
		if (N->at(i) != NULL){
			N->at(i)->printNode();
		}
	}
	
	for (int i = 0; i < m; i++){
		if (E->at(i) != NULL){
			E->at(i)->printEdge();
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
