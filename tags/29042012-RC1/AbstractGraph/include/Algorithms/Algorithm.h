//
//  Algorithm.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <limits.h>

#include "../Graphs/AbstractGraph.h"
#include "../Graphs/Graph.h"
#include "../Graphs/DiGraph.h"
#include "../incl.h"

#define INFINITY INT_MAX


/*
 * a super algorithm class, all algorithm
 * implementation must extend this class
 */
class AGRAPH_EXPORT Algorithm{

public:
	
	virtual int solve() = 0;
};

#endif
































