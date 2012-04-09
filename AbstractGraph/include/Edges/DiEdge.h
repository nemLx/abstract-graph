#ifndef _DIEDGE_H_
#define _DIEDGE_H_

#include "../Nodes/DiNode.h"
#include "AbstractEdge.h"

class DiNode;

class DiEdge : public AbstractEdge{
	
public:
	
	DiNode * from;
	
	DiNode * to;
	
	DiEdge(int id, DiNode * s, DiNode * t);
	
	DiEdge(int id, DiNode * s, DiNode * t, int v);
	
	void printEdge();
	
	~DiEdge();
	
};

#endif