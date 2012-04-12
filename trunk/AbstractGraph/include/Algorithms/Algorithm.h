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
#include <map>
#include <set>
#include <algorithm>
#include <limits.h>

#include "../Graphs/AbstractGraph.h"
#include "../Graphs/Graph.h"
#include "../Graphs/DiGraph.h"

#define INFINITY INT_MAX



class Algorithm{

public:
	
	virtual int solve() = 0;
};

#endif
































