#ifndef _DINODE_H_
#define _DINODE_H_

#include "AbstractNode.h"
#include "../Edges/DiEdge.h"

using namespace std;

class DiEdge;

class DiNode : public AbstractNode{
	
public:
	
	int inDegree;
	
	int outDegree;
	
	vector<DiNode*> * inNeighborhood;
	
	vector<DiNode*> * outNeighborhood;
	
	vector<DiEdge*> * inAdjacent;
	
	vector<DiEdge*> * outAdjacent;
	
	
	
	
	DiNode(int id);
	
	~DiNode();
	
	int addInAdjacent(DiEdge * adj, DiNode * neighbor);
	
	int removeInAdjacent(DiEdge * adj, DiNode * neighbor);
	
	int addOutAdjacent(DiEdge * adj, DiNode * neighbor);
	
	int removeOutAdjacent(DiEdge * adj, DiNode * neighbor);
	
};


#endif