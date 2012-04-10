#ifndef _ABSTRACTEDGE_H_
#define _ABSTRACTEDGE_H_

//#include "../Nodes/AbstractNode.h"

class AbstractNode;

class AbstractEdge{

public:
	
	int id;
	
	int value;
	
	AbstractEdge(int id);
	
	AbstractEdge(int id, int v);
	
	virtual ~AbstractEdge(){};
	
	
	virtual AbstractNode* getFrom() = 0;
	
	virtual AbstractNode* getTo() = 0;
	
	virtual void printEdge() = 0;
};

#endif