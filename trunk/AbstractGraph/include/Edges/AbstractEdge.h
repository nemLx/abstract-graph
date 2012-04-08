#ifndef _ABSTRACTEDGE_H_
#define _ABSTRACTEDGE_H_

#include "../Nodes/AbstractNode.h"

class AbstractEdge{

public:
	
	int id;
	
	int value;
	
	AbstractNode * from;
	
	AbstractNode * to;
	
};

#endif