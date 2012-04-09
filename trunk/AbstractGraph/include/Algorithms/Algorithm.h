#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <vector>
#include <queue>
#include <map>
#include <limits.h>

#include "../Graphs/AbstractGraph.h"

#include "../Graphs/Graph.h"
#include "../Graphs/DiGraph.h"

#define INFINITY INT_MAX

class AbstractGraph;

class Graph;

class DiGraph;

class Algorithm{

public:
	
	virtual int solve() = 0;
	
};

#endif
































