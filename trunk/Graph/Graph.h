#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>

using namespace std;

class Graph{

public:
	Graph(int numNodes);
    ~Graph();


    /*	returns:
	 *		a positive id of the node
	 */
    int addNode();



    /*	returns:
	 *		a positive id of the edge on success
	 *		-1 on failure
	 */
    int addEdge(int from, int to, int directed);



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
	 *		the edges are not weighted
	 *
	 *		-1 on failure
	 */
    int shortestPath(int s, int t, vector<int> * path);



	/*	returns:
	 *		weight of the spanning tree on success
	 *
	 *		-1 on failure
	 */
	int MST(vector<int> * edges);



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

    class Node{
	public:
		int id;
		int degree;
		int weight;
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
		}

		int addNeighbor(Node* neighbor){
			return addNeighborTo(neighbor, neighborhood);
		}

		int addInNeighbor(Node* neighbor){
			return addNeighborTo(neighbor, inNeighborhood);
		}

		int addOutNeighbor(Node* neighbor){
			return addNeighborTo(neighbor, outNeighborhood);
		}

		int removeNeighbor(Node* neighbor){
			return removeNeighborFrom(neighbor, this->neighborhood);	
		}

		int removeInNeighbor(Node* neighbor){
			return removeNeighborFrom(neighbor, this->inNeighborhood);	
		}

		int removeOutNeighbor(Node* neighbor){
			return removeNeighborFrom(neighbor, this->outNeighborhood);	
		}

		int addNeighborTo(Node* neighbor, vector<Node*>* neighborhood){
			vector<Node*>::iterator it = neighborhood->begin();

			while (it != neighborhood->end()){
				if ((*it)->id == neighbor->id){
					return 0;
				}else{
					++it;
				}
			}

			neighborhood->push_back(neighbor);

			return 1;
		}

		int removeNeighborFrom(Node* neighbor, vector<Node*>* neighborhood){
			vector<Node*>::iterator it = neighborhood->begin();

			while (it != neighborhood->end()){
				if ((*it)->id == neighbor->id){
					it = neighborhood->erase(it);
					return 0;
				}else{
					++it;
				}
			}

			return 1;
		}

		void printNode(){
			printf("%i : ", id);
			
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
			neighborhood = NULL;
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

			from->degree++;
			to->degree++;

			from->addNeighbor(to);
			to->addNeighbor(from);

			if (directed == 1){
				from->addOutNeighbor(to);
				to->addInNeighbor(from);
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
			from->removeOutNeighbor(to);
			to->removeInNeighbor(from);

			Node* temp = from;
			from = to;
			to = temp;

			from->addOutNeighbor(to);
			to->addInNeighbor(from);
		}

		~Edge(){
			from->degree--;
			to->degree--;

			from->removeNeighbor(to);
			to->removeNeighbor(from);

			if (directed == 1){
				from->removeOutNeighbor(to);
				to->removeInNeighbor(from);
			}
		}
    };

    vector<Node*>* N;
    vector<Edge*>* E;

    bool exists(int id, int isNode);
};

#endif
