//
//  DiEdge.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _DIEDGE_H_
#define _DIEDGE_H_

#include "../Nodes/DiNode.h"
#include "AbstractEdge.h"



class DiNode;

class DiEdge : public AbstractEdge{
	
public:
	
	DiEdge(int id, DiNode * s, DiNode * t);
	
	DiEdge(int id, DiNode * s, DiNode * t, int v);
	
	~DiEdge();
	
	AbstractNode* getFrom();
	
	AbstractNode* getTo();
	
	void printEdge();
	
	
	DiNode * from;
	
	DiNode * to;
};

#endif