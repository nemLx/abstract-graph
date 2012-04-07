#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include "Algorithms.h"

#define INFINITY INT_MAX

using namespace std;
using namespace Algorithms;

class Graph{

public:
	Graph(int numNodes, int directed);
    ~Graph();


    /*	returns:
	 *		a positive id of the node
	 */
    int addNode();



    /*	
	 *	from: id of tail node
	 *	to: id of head node
	 *	weight: should be 1 in unweighted graph
	 *	returns:
	 *		a positive id of the edge on success
	 *		-1 on failure
	 */
    int addEdge(int from, int to, int weight);



    /*	returns:
	 *		1 on success
	 *		0 on failure
	 */
    int removeNode(int id);



    /*	returns:
	 *		1 on success
	 *		0 on failure
	 */
    int removeEdge(int id);



    /*	returns:
	 *		1 on success
	 *		0 on failure
	 */
    int setNodeWeight(int id, int weight);



    /*	returns:
	 *		1 on success
	 *		0 on failure
	 */
    int setEdgeWeight(int id, int weight);


    /*	returns:
	 *		1 on success
	 *		0 on failure
	 */
    int setEdgeCapacity(int id, int capacity);



	/*	returns:
	 *		1 on success
	 *		0 on failure
	 */
    int setEdgeDirection(int id, int from, int to);


	/*	returns:
	 *		weight of the path on success, which is simply the length
	 *		if the edges are not weighted
	 *
	 *		-1 on failure
	 */
    int shortestPath(int s, int t, vector<int> * path);



	/*	returns:
	 *		weight of the spanning tree on success
	 *
	 *		-1 on failure
	 */
	int MST(vector<int> * edges, int root);



	/*	returns:
	 *		weight of the spanning tree on success
	 *
	 *		-1 on failure
	 */
	int maxMatching(vector<int> * matching);

	/*	returns:
	 *		weight of the spanning tree on success
	 *
	 *		-1 on failure
	 */
	int minVertexCover(vector<int> * cover);


	void printGraph();

	
private:
    int n;
    int m;
    int directed;
	class Edge;
	
    class Node{
	public:
		int id;
		int degree;
		int inDegree;
		int outDegree;
		int weight;
		
		vector<Edge*>* adjacent;
		vector<Edge*>* inAdjacent;
		vector<Edge*>* outAdjacent;
		
		vector<Node*>* neighborhood;
		vector<Node*>* inNeighborhood;
		vector<Node*>* outNeighborhood;


		Node(int id){
			this->id = id;
			degree = 0;
			weight = 0;
			
			neighborhood = new vector<Node*>();
			inNeighborhood = new vector<Node*>();
			outNeighborhood = new vector<Node*>();
			
			adjacent = new vector<Edge*>();
			inAdjacent = new vector<Edge*>();
			outAdjacent = new vector<Edge*>();
		}

		void addNeighbor(Edge* adj, Node* neighbor){
			degree++;
			neighborhood->push_back(neighbor);
			adjacent->push_back(adj);
		}

		void addInNeighbor(Edge* adj, Node* neighbor){
			inDegree++;
			inNeighborhood->push_back(neighbor);
			inAdjacent->push_back(adj);
		}

		void addOutNeighbor(Edge* adj, Node* neighbor){
			outDegree++;
			outNeighborhood->push_back(neighbor);
			outAdjacent->push_back(adj);
		}

		void removeNeighbor(Edge* adj, Node* neighbor){
			degree--;
			removeNeighborFrom(neighbor, this->neighborhood);
			removeAdjacentFrom(adj, this->adjacent);
		}

		int removeInNeighbor(Edge* adj, Node* neighbor){
			inDegree--;
			removeNeighborFrom(neighbor, this->inNeighborhood);
			removeAdjacentFrom(adj, this->inAdjacent);	
		}

		int removeOutNeighbor(Edge* adj, Node* neighbor){
			outDegree--;
			removeNeighborFrom(neighbor, this->outNeighborhood);
			removeAdjacentFrom(adj, this->outAdjacent);
		}

		void removeNeighborFrom(Node* neighbor, vector<Node*>* nb){
			vector<Node*>::iterator it = nb->begin();
			
			if (neighbor == NULL){
				return;
			}
			
			while (it != nb->end()){
				if ((*it) == NULL){
					continue;
				}
				
				if ((*it)->id == neighbor->id){
					nb->erase(it);
					break;
				}else{
					it++;
				}
			}
		}
		
		void removeAdjacentFrom(Edge* adj, vector<Edge*>* nb){
			vector<Edge*>::iterator it = nb->begin();
			
			if (adj == NULL){
				return;
			}
			
			while (it != nb->end()){
				if ((*it) == NULL){
					continue;
				}
				
				if ((*it)->id == adj->id){
					nb->erase(it);
					break;
				}else{
					it++;
				}
			}
		}

		void printNode(){
			printf("Node %i's adjs : ", id);
			
			for (int i = 0; i < degree; i++){
				if (neighborhood->at(i)!=NULL){
					printf("%i ", neighborhood->at(i)->id);
				}
			}
			
			printf("\n");
		}
		
		~Node(){
			delete neighborhood;
			delete inNeighborhood;
			delete outNeighborhood;
			
			delete adjacent;
			delete inAdjacent;
			delete outAdjacent;
			
			neighborhood = NULL;
			inNeighborhood = NULL;
			outNeighborhood = NULL;
			
			adjacent = NULL;
			inNeighborhood = NULL;
			outNeighborhood = NULL;
		}
    };

    class Edge{
	public:
		int id;
		Node* from;
		Node* to;
		int directed;
		int weight;
		int capacity;
		
		Edge(int id, Node* fromNode, Node* toNode, int directed){
			this->id = id;
			this->from = fromNode;
			this->to = toNode;
			this->directed = directed;
			weight = 1;
			capacity = 1;

			from->addNeighbor(this, to);
			if (from->id != to->id){
				to->addNeighbor(this, from);
			}

			if (directed == 1){
				from->addOutNeighbor(this, to);
				to->addInNeighbor(this, from);
			}
		}

		int setDirection(Node* fromNode, Node* toNode){
			directed = 1;
			if (fromNode->id != from->id){
				if (fromNode->id != to->id){
					return -1; // err
				}else{
					reverseDirection();
					return 1; // reversed direction
				}
			}else{
				if (toNode->id != to->id){
					return -1; // err
				}else{
					return 0; // no change
				}
			}
		}

		void reverseDirection(){
			from->removeOutNeighbor(this, to);
			to->removeInNeighbor(this, from);

			Node* temp = from;
			from = to;
			to = temp;

			from->addOutNeighbor(this, to);
			to->addInNeighbor(this, from);
		}
        
        void setWeight(int weight){
            this->weight = weight;
        }

		void printEdge(){
			if (directed){
				printf("Edge %i : %i->%i ", id, from->id, to->id);
			}else{
				printf("Edge %i : %i<->%i ", id, from->id, to->id);
			}
			
			printf("w:%i \n", weight);
		}
		
		~Edge(){
			
			if (to == NULL || from ==NULL){
				return;
			}
			
			from->removeNeighbor(this, to);
			if (from->id != to->id){
				to->removeNeighbor(this, from);
			}

			if (directed == 1){
				from->removeOutNeighbor(this, to);
				to->removeInNeighbor(this, from);
			}
		}
    };

    vector<Node*>* N;
    vector<Edge*>* E;

    bool exists(int id, int isNode);
    
    void initDijkstra(int s, vector<Dijkstra::Vertex*> * vertices, priority_queue<Dijkstra::Vertex*, vector<Dijkstra::Vertex*>, Dijkstra::comp> * G);
    
    Dijkstra::Vertex * initDijkstraVertex(Node * node);
    
    void initDijkstraVertexAdj(Dijkstra::Vertex * v, vector<Dijkstra::Vertex*> * vertices);
    
    Edge* getEdge(Node * from, Node * to);
	
	int constructPath(int t, vector<Dijkstra::Vertex*> * vertices, vector<int> * path);
    
	int constructMST(vector<Dijkstra::Vertex*> * vertices, vector<int> * edges);
};

#endif
