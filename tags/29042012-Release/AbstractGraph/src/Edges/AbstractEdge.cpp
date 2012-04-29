//
//  AbstractEdge.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <iostream>

#include "../../include/Edges/AbstractEdge.h"



AbstractEdge::AbstractEdge(int id){
	
	this->id = id;
}



AbstractEdge::AbstractEdge(int id, int v){
	
	this->id = id;
	
	this->value = v;
}