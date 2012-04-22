//
//  AbstractEdge.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _ABSTRACTEDGE_H_
#define _ABSTRACTEDGE_H_

#include "../incl.h"


class AbstractNode;

class AGRAPH_EXPORT AbstractEdge{

public:
	
	AbstractEdge(int id);
	
	AbstractEdge(int id, int v);
	
	
	virtual ~AbstractEdge(){};
	
	virtual AbstractNode* getFrom() = 0;
	
	virtual AbstractNode* getTo() = 0;
	
	virtual void printEdge() = 0;
	
	
	int id;
	
	int value;
};

#endif