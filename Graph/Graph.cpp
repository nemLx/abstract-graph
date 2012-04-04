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

int Graph::addEdge(int from, int to){

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
	}
}

int Graph::removeEdge(int id){
	if (!exists(id, 0)){
		return 0;
	}else{
		delete E->at(id);
		E->at(id) = NULL;
		m--;
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
    
    if (path == NULL || !exists(s,1) || !exists(t,1) ){
        return 0;
    }
    
    //init a vertex struct with adjacency list
    
    priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G 
    = new priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp>();
    Dijkstra::Vertex * src = initDijkstra(s, G);
    
    Dijkstra::dijkstra(src, G);
    
    int length = 0;
    
    Dijkstra::Vertex * curr = src;
    path->push_back(curr->id);
    
    while (curr->next != NULL){
        curr = curr->next;
        path->push_back(curr->id);
        length++;
    }
    
	return length;
}

Dijkstra::Vertex * Graph::initDijkstra(int s, priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G){
    vector<Dijkstra::Vertex*> * vertices = new vector<Dijkstra::Vertex*>(n);
    
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
    
    return vertices->at(s);
}

Dijkstra::Vertex * Graph::initDijkstraVertex(Node * node){
    Dijkstra::Vertex * v = new Dijkstra::Vertex();
    
    v->id = node->id;
    v->adj = new vector<Dijkstra::Vertex*>();
    v->cost = new vector<int>();
    v->visited = false;
    v->dist = 999999999;
    v->next = NULL;
    
    return v;
}

void Graph::initDijkstraVertexAdj(Dijkstra::Vertex * v, vector<Dijkstra::Vertex*> * vertices){
    
    Node * node = N->at(v->id);
    
    vector<Node*> * reachables = NULL;
    int currId = -1;
    int degree = 0;
    
    if (directed){
        reachables = node->outNeighborhood;
        degree = node->outDegree;
    }else{
        reachables = node->neighborhood;
        degree = node->degree;
    }
    
    for (int i = 0; i < degree; i++) {
        currId = reachables->at(i)->id;
        v->adj->push_back(vertices->at(currId));
        
        Node * from = node;
        Node * to   = reachables->at(i);
        Edge * e    = getEdge(from, to);
        
        if (!directed && e == NULL){
            e = getEdge(to, from);
        }
        
        v->cost->push_back( e->weight );
    }
    
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

Graph::Edge* Graph::getEdge(Node * from, Node * to){
    Edge* curr = NULL;
    
    for (int i = 0; i < m; i++){
        
        curr = E->at(i);
        
        if (from->id == curr->from->id && to->id == curr->to->id){
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
