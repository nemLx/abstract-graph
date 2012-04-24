//
//  GraphicSequence.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/23/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_GraphicSequence_h
#define AbstractGraph_GraphicSequence_h

#include "Algorithm.h"
#include "../Graphs/Graph.h"
#include "../incl.h"



class AGRAPH_EXPORT GraphicSequence : public Algorithm{
	
public:
	
	GraphicSequence(Graph * g, vector<int> * sequence);
	
	int solve();
};




#endif










