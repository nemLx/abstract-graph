//
//  Node.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _NODE_H_
#define _NODE_H_

#include "AbstractNode.h"

#include "../incl.h"

using namespace std;



class Edge;

class AGRAPH_EXPORT Node : public AbstractNode{

public:
	
	Node(int id);
	
	~Node();
	
	int addAdjacent(Edge * adj, Node * neighbor);
	
	int removeAdjacent(Edge * adj, Node * neighbor);
	
	map<AbstractEdge*, AbstractNode*> * getAdjacent();
	
	void printNode();

private:
	
	int degree;
	
	map<Edge*, Node*> * adjacent;
};

#endif