#ifndef _ABSTRACTNODE_H_
#define _ABSTRACTNODE_H_

#include <vector>
#include <map>

using namespace std;

class AbstractEdge;

class AbstractNode{
	
public:
	
	int id;
	
	AbstractNode(int id);
	
	virtual ~AbstractNode(){};
	
	virtual void printNode() = 0;
	
	//virtual map<int, AbstractNode*> * getReachable() = 0;
	
	virtual map<AbstractEdge*, AbstractNode*> * getAdjacent() = 0;
};

#endif