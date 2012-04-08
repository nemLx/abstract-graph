#include <stdio.h>
#include <vector>

#include "include/Graphs/AbstractGraph.h"
#include "include/Graphs/Graph.h"

using namespace std;

void shortestPathTest();
void mstTest();

int main(){

	shortestPathTest();

	mstTest();
	
	return 0;
}

void shortestPathTest(){
	
	Graph g(8);
	
	g.addEdge(1,1,1);
	g.removeEdge(0);
	
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
	
//	printf("\n");
//	g.printGraph();
//    
//    vector<int> * path = new vector<int>();
//	
//	int from = 1;
//	int to = 7;
//    
//	printf("\nshortest path from %i to %i: \ndistance: %i \npath: ", from, to, g.shortestPath(from,to, path));
//	
//	int size = path->size();
//	for (int i = 0; i < size; i++){
//		printf("%i ", path->at(size-i-1));
//	}
//	
//	printf("\n");
//	
//	delete path;
}

void mstTest(){
	
	Graph g(8);
	
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
	g.addEdge(5,7,6);
	g.addEdge(7,6,1);
	
//	printf("\n");
//	g.printGraph();
//	
//	vector<int> * mstEdges = new vector<int>();
//	
//	printf("\nMST: \ntotal weight: %i \ntree edges: ", g.MST(mstEdges, 1));
//	
//	for (int i = 0; i < mstEdges->size(); i++){
//		printf("%i ", mstEdges->at(i));
//	}
//	
//	printf("\n");
//	
//	delete mstEdges;
}
