//
//  DiNode.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _DINODE_H_
#define _DINODE_H_

#include "AbstractNode.h"

#include "../incl.h"

using namespace std;



class DiEdge;

class AGRAPH_EXPORT DiNode : public AbstractNode{
	
public:
	
	DiNode(int id);
	
	~DiNode();
	
	int addInAdjacent(DiEdge * adj, DiNode * neighbor);
	
	int removeInAdjacent(DiEdge * adj, DiNode * neighbor);
	
	int addOutAdjacent(DiEdge * adj, DiNode * neighbor);
	
	int removeOutAdjacent(DiEdge * adj, DiNode * neighbor);
	
	map<AbstractEdge*, AbstractNode*> * getAdjacent();
	
	map<DiEdge*, DiNode*> * getInAdjacent();
	
	void printNode();
	
private:
	
	int inDegree;
	
	int outDegree;
	
	map<DiEdge*, DiNode*> * inAdjacent;
	
	map<DiEdge*, DiNode*> * outAdjacent;
};


#endif