#include <stdio.h>
#include <vector>

#include "Graph.h"

using namespace std;

void shortestPathTest();
void mstTest();

int main(){

	shortestPathTest();

	mstTest();
	
	return 0;
}

void shortestPathTest(){
	Graph g(8,1);
	
	printf("%i ", g.addEdge(1,2,2));
	printf("%i ", g.addEdge(1,4,1));
	printf("%i ", g.addEdge(2,4,3));
	printf("%i ", g.addEdge(2,5,10));
	printf("%i ", g.addEdge(3,1,4));
	printf("%i ", g.addEdge(3,6,5));
	printf("%i ", g.addEdge(4,3,2));
	printf("%i ", g.addEdge(4,5,2));
	printf("%i ", g.addEdge(4,6,8));
	printf("%i ", g.addEdge(4,7,4));
	printf("%i ", g.addEdge(5,7,6));
	printf("%i ", g.addEdge(7,6,1));
	
	g.printGraph();
    
    vector<int> * path = new vector<int>();
	vector<int> * mstEdges = new vector<int>();
    
	printf("\n%i \n", g.shortestPath(1,7, path));
}

void mstTest(){
	
	Graph g(8,0);
	
	printf("%i ", g.addEdge(1,2,2));
	printf("%i ", g.addEdge(1,4,1));
	printf("%i ", g.addEdge(2,4,3));
	printf("%i ", g.addEdge(2,5,10));
	printf("%i ", g.addEdge(3,1,4));
	printf("%i ", g.addEdge(3,6,5));
	printf("%i ", g.addEdge(4,3,2));
	printf("%i ", g.addEdge(4,5,7));
	printf("%i ", g.addEdge(4,6,8));
	printf("%i ", g.addEdge(4,7,4));
	printf("%i ", g.addEdge(5,7,6));
	printf("%i ", g.addEdge(7,6,1));
	
	g.printGraph();
	
	vector<int> * mstEdges = new vector<int>();
	
	printf("\ntotal weight: %i \n", g.MST(mstEdges, 1));
	
	for (int i = 0; i < mstEdges->size(); i++){
		printf("%i ", mstEdges->at(i));
	}
	
	printf("\n");
}
