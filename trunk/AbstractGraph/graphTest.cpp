//
//  graphTest.cpp
//  AbstractGraph
//
//  Created by Jiageng Li on 4/8/12.
//  Copyright (c) 2012 University of Illinois at Urbana-Champaign. All rights reserved.
//

#include <stdio.h>
#include <vector>

#include "include/Graphs/Graph.h"
#include "include/Graphs/DiGraph.h"

using namespace std;



void printVector(vector<int> * v){
	
	vector<int>::iterator it;
	
	for (it = v->begin(); it != v->end(); it++){
		printf("%i ", *it);
	}
}



void shortestPathTest(){
	
	DiGraph g(19);
	
	g.addEdge(1,2,2);
	g.addEdge(1,4,1);
	g.addEdge(2,4,3);
	g.addEdge(2,5,10);
	g.addEdge(3,1,4);
	g.addEdge(3,6,5);
	g.addEdge(4,3,2);
	g.addEdge(4,5,2);
	g.addEdge(4,6,8);
	g.addEdge(4,7,4);
	g.addEdge(5,7,6);
	g.addEdge(7,6,1);
	
	g.addEdge(5, 7, 3);
	
	g.removeNode(4);
	
	//Graph g(3);
	
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(0, 1);
	
	printf("\n");
	g.printGraph();
    
    vector<int> path;
	
	int from = 1;
	int to = 7;
    
	printf("\nshortest path from %i to %i: \ndistance: %i \npath: ", from, to, g.shortestPath(from, to, &path));
	
	printVector(&path);
	
	printf("\n");
}

void mstTest(){
	
	Graph g(8);
	
	g.removeNode(0);
	
	g.addEdge(1,2,2);
	g.addEdge(1,4,1);
	g.addEdge(2,4,3);
	g.addEdge(2,5,10);
	g.addEdge(3,1,4);
	g.addEdge(3,6,5);
	g.addEdge(4,3,2);
	g.addEdge(4,5,7);
	g.addEdge(4,6,8);
	g.addEdge(4,7,4);
	g.addEdge(7,5,6);
	g.addEdge(7,6,1);
	
	printf("\n");
	g.printGraph();
	
	vector<int> mstEdges;
	
	printf("\nMST: \ntotal weight: %i \ntree edges: ", g.mst(&mstEdges));
	
	printVector(&mstEdges);
	
	printf("\n");
}



void bipartiteTest(){
	
	Graph g(7);
	
	g.addEdge(1,3);
	g.addEdge(1,4);
	g.addEdge(1,5);
	g.addEdge(2,3);
	g.addEdge(2,4);
	g.addEdge(2,5);
	
//	g.addEdge(1,2);
//	g.addEdge(2,3);
//	g.addEdge(1,3);
	
	printf("\n");
	g.printGraph();
	
	vector<int> partX;
	vector<int> partY;
	
	int isBipartite = g.bipartite(&partX, &partY);
	
	if (isBipartite){
		
		printf("\npartite set X: ");
		printVector(&partX);
		
		printf("\n");
		
		printf("partite set Y: ");
		printVector(&partY);
		
		printf("\n");
	}else{
		printf("Not Bipartite \n");
	}
	
}



void maxFlowTest(){

//	DiGraph g(7);
//	
//	g.addEdge(0, 1, 3);
//	g.addEdge(0, 2, 2);
//	g.addEdge(1, 2, 1);
//	g.addEdge(1, 3, 3);
//	g.addEdge(1, 4, 4);
//	g.addEdge(2, 4, 2);
//	g.addEdge(3, 5, 2);
//	g.addEdge(4, 5, 4);
//	g.addEdge(0, 1, 2);

	DiGraph g(4);
	
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(0, 3);
	g.addEdge(1, 3);
	g.addEdge(3, 2);
	
	printf("\n");
	g.printGraph();
	
	int from = 0;
	int to = 3;
	
	vector< pair<int, int> > edgeFlow;
	vector<int> cutSet;
	
	int maxFlow = g.maxFlowMinCut(from, to, &edgeFlow, &cutSet);
	
	printf("\nMaxflow from %i to %i : %i \n", from, to, maxFlow);
	
	if (maxFlow){
		
		vector< pair<int, int> >::iterator it;
		
		for (it = edgeFlow.begin(); it != edgeFlow.end(); it++){
			printf("Edge: %i : Flow: %i \n", it->first, it->second);
		}
		
		printf("Cut set containing source: ");
		
		vector<int>::iterator itCut = cutSet.begin();
		
		while (itCut != cutSet.end()) {
			printf("%i ", *itCut);
			itCut++;
		}
		
		printf("\n");
	}
}



void bipartiteMatchingTest(){
	
	Graph g(10);
	
	g.addEdge(0, 1);
	g.addEdge(2, 3);
	g.addEdge(4, 5);
	g.addEdge(6, 7);
	g.addEdge(8, 9);
	
//	g.addEdge(0, 3);
//	g.addEdge(2, 3);
//	g.addEdge(4, 3);
//	g.addEdge(6, 9);
//	g.addEdge(4, 9);
	
	printf("\n");
	g.printGraph();
	
	vector<int> matching;
	
	int maxMatching = g.maxMatching(&matching);
	
	if (maxMatching){
		printf("maximum matching size: %i \nmatching: ", maxMatching);
		
		printVector(&matching);
	}
	
	printf("\n");
}



void oddCycleTest(){

	Graph g(10);

	
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 0);
	g.addEdge(0, 5);
	
	printf("\n");
	g.printGraph();
	
	vector<int> cycle;
	
	int numCycles = g.getOddCycle(&cycle);
	
	printf("\nodd cycle length: %i \nedges:", numCycles);
	
	printVector(&cycle);
	
	printf("\n");
}



void eulerianPathTest(){
	
	Graph g(5);
	
//	g.addEdge(0, 1);
//	g.addEdge(0, 2);
//	g.addEdge(0, 5);
//	g.addEdge(0, 6);
//	g.addEdge(1, 2);
//	g.addEdge(2, 3);
//	g.addEdge(2, 4);
//	g.addEdge(3, 4);
//	g.addEdge(4, 5);
//	g.addEdge(4, 6);
	
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 4);
	
	//g.addEdge(2, 3);
	
	printf("\n");
	g.printGraph();
	
	vector<int> path;
	
	bool isEulerian = g.eulerianPath(0, 0, &path);
	
	if (isEulerian){
		printf("\nEulerian path in the order: ");
		printVector(&path);
	}else{
		printf("\nNot Eulerian");
	}
	
	printf("\n");
	
}



void bridgeTest(){
	
	Graph g(13);
	
	g.addEdge(0, 1);
	g.addEdge(0, 5);
	g.addEdge(0, 6);
	g.addEdge(1, 2);
	g.addEdge(2, 6);
	g.addEdge(3, 4);
	g.addEdge(3, 5);
	g.addEdge(4, 9);
	g.addEdge(4, 11);
	g.addEdge(4, 5);
	g.addEdge(6, 7);
	g.addEdge(7, 8);
	g.addEdge(7, 10);
	g.addEdge(8, 10);
	g.addEdge(9, 11);
	g.addEdge(11, 12);
	
	//g.addEdge(0, 3);
	
	printf("\n");
	g.printGraph();
	
	vector<int> bridges;
	
	int numBridges = g.getBridges(&bridges);
	
	if (numBridges){
		printf("\nBridges: ");
		printVector(&bridges);
	}else{
		printf("\nNo Bridge");
	}
	
	printf("\n");
}



void pruferEncodeTest(){
	
	Graph g(7);
	
	g.addEdge(0, 3);
	g.addEdge(1, 3);
	g.addEdge(2, 3);
	g.addEdge(4, 3);
	g.addEdge(4, 5);
	g.addEdge(6, 5);
	
	//g.removeNode(0);
	
	printf("\n");
	g.printGraph();
	
	vector<int> code;
	map<int, int> label;
	
	int hasPruferCode = g.getPruferCode(&code, &label);
	
	if (hasPruferCode){
		printf("\nPrufer Code: ");
		printVector(&code);
	}else{
		printf("\nDoes not have Prufer Code\n");
	}
}



void pruferDecodeTest(){
	
	Graph g;
	
	vector<int> code(0);
	
	code.push_back(4);
	code.push_back(4);
	code.push_back(4);
	code.push_back(5);
	code.push_back(5);
	code.push_back(5);
	code.push_back(5);
	code.push_back(7);
	
	g.buildFromPruferCode(&code);
	
	printf("\nGraph with code: ");
	printVector(&code);
	printf("\n");
	
	g.printGraph();
	
	vector<int> codeB;
	map<int, int> label;
	
	int hasPruferCode = g.getPruferCode(&codeB, &label);
	
	if (hasPruferCode){
		printf("\nPrufer Code: ");
		printVector(&codeB);
	}else{
		printf("\nDoes not have Prufer Code\n");
	}
}



void scTest(){
	
//	DiGraph g(13);
//	
//	g.addEdge(0,2);
//	g.addEdge(1,0);
//	g.addEdge(2,3);
//	g.addEdge(2,4);
//	g.addEdge(3,2);
//	g.addEdge(3,4);
//	g.addEdge(4,5);
//	g.addEdge(4,6);
//	g.addEdge(5,0);
//	g.addEdge(5,3);
//	g.addEdge(6,0);
//	g.addEdge(6,7);
//	g.addEdge(7,8);
//	g.addEdge(8,7);
//	g.addEdge(9,6);
//	g.addEdge(9,8);
//	g.addEdge(9,12);
//	g.addEdge(10,9);
//	g.addEdge(11,4);
//	g.addEdge(11,9);
//	g.addEdge(12,10);
//	g.addEdge(12,11);
	
	DiGraph g(8);
	
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 0);
	g.addEdge(2, 4);
	g.addEdge(4, 5);
	g.addEdge(5, 6);
	g.addEdge(6, 4);
	g.addEdge(6, 7);
	
	printf("\n");
	g.printGraph();
	
	map<int, int> sc;
	
	int scCount = g.getSCs(&sc);
	
	printf("\n%i SCs\n", scCount);
	
	map<int, int>::iterator it = sc.begin();
	while (it != sc.end()) {
		printf("Node %i is in SC %i \n", it->first, it->second);
		it++;
	}
}



void allPairSPTest(){
	
	Graph g(11);
	
	g.addEdge(1, 2);
	g.addEdge(1, 5);
	g.addEdge(1, 7);
	g.addEdge(1, 10);
	g.addEdge(2, 8);
	g.addEdge(2, 9);
	g.addEdge(3, 10);
	g.addEdge(4, 6);
	g.addEdge(4, 8);
	g.addEdge(5, 6);
	g.addEdge(5, 7);
	g.addEdge(6, 10);
	g.addEdge(1, 5);
	g.addEdge(7, 8);
	g.addEdge(1, 5);
	g.addEdge(8, 10);
	g.addEdge(9, 10);	
	
	printf("\n");
	g.printGraph();
	
	map<pair<int, int>, int> path;
	map<pair<int, int>, int> dist;
	
	g.allPairSP(&path, &dist);
	
	map<pair<int, int>, int>::iterator it = dist.begin();
	while (it != dist.end()) {
		printf("d(%i,%i) = %i\n", it->first.first, it->first.second, it->second);
		it++;
	}
}



void graphicSequenceTest(){
	
	Graph g;
	
	vector<int> s;
	
//	s.push_back(3);
//	s.push_back(3);
//	s.push_back(3);
//	s.push_back(3);
//	s.push_back(3);
//	s.push_back(2);
//	s.push_back(2);
	s.push_back(1);
	s.push_back(1);
	s.push_back(1);
	s.push_back(1);
	s.push_back(1);
	
	int isGraphic = g.buildFromSequence(&s);
	
	if (isGraphic){
		printf("\n");
		g.printGraph();
	}else{
		printf("\nNot Graphic : %i\n", isGraphic);
	}
}



int main(){
	
//	shortestPathTest();
//	
//	mstTest();
//	
//	bipartiteTest();
//	
//	maxFlowTest();
//	
//	bipartiteMatchingTest();
//	
//	oddCycleTest();
//
//	eulerianPathTest();
//	
//	bridgeTest();
//	
//	pruferEncodeTest();
//
//	pruferDecodeTest();
//	
//	scTest();
//
//	allPairSPTest();
//
	graphicSequenceTest();
	
	return 0;
}









