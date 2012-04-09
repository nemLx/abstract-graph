#ifndef _ABSTRACTNODE_H_
#define _ABSTRACTNODE_H_

#include <vector>
#include <map>

class AbstractNode{
	
public:
	
	int id;
	
	AbstractNode(int id);

	virtual void printNode();
	
	virtual ~AbstractNode(){};
};

#endif