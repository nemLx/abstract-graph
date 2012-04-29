//
//  Edge.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _EDGE_H_
#define _EDGE_H_

#include "../Nodes/Node.h"
#include "AbstractEdge.h"

#include "../incl.h"



class Node;

class AGRAPH_EXPORT Edge : public AbstractEdge{
	
public:
	
	Edge(int id, Node * s, Node * t);
	
	Edge(int id, Node * s, Node * t, int v);
	
	~Edge();
	
	AbstractNode* getFrom();
	
	AbstractNode* getTo();
	
	void printEdge();

private:
	
	Node * from;
	
	Node * to;
};

#endif