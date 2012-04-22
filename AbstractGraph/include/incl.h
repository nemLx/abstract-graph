//
//  incl.h
//  AbstractGraph
//
//  Created by Jiageng Li on 4/22/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#ifndef AbstractGraph_incl_h
#define AbstractGraph_incl_h


// Simple window defs
#if _WIN32
#ifndef AGRAPH_PROD
#define AGRAPH_EXPORT __declspec(dllexport)
#else
#define AGRAPH_EXPORT __declspec(dllimport)
#endif
#else
#define AGRAPH_EXPORT // NULL - only necessary for Win32
#endif


#endif
