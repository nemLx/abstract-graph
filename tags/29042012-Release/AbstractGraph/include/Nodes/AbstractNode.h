//
//  AbstractNode.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _ABSTRACTNODE_H_
#define _ABSTRACTNODE_H_

#include <stdio.h>
#include <vector>
#include <map>

#include "../incl.h"

using namespace std;

class AbstractEdge;

class AGRAPH_EXPORT AbstractNode{
	
public:
	
	AbstractNode(int id);
	
	virtual ~AbstractNode(){};
	
	virtual void printNode() = 0;
	
	virtual map<AbstractEdge*, AbstractNode*> * getAdjacent() = 0;

	
	int id;
};

#endif
