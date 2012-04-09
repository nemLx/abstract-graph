#ifndef _ABSTRACTEDGE_H_
#define _ABSTRACTEDGE_H_

#include "../Nodes/AbstractNode.h"

class AbstractEdge{

public:
	
	int id;
	
	int value;
	
	AbstractEdge(int id);
	
	AbstractEdge(int id, int v);
	
	virtual ~AbstractEdge(){};
	
	virtual void printEdge(){};
};

#endif