#include <stdio.h>
#include <vector>

#include "Graph.h"

using namespace std;

int main(){

	Graph g(5,0);

	printf("%i ", g.addEdge(1,2));
	printf("%i ", g.addEdge(1,3));
	printf("%i ", g.addEdge(1,4));
	printf("%i ", g.addEdge(2,3));
	printf("%i \n", g.addEdge(0,4));

	g.printGraph();
    
    vector<int> * path = new vector<int>();
    
	printf("\n%i \n", g.shortestPath(1,2,path));

	return 0;
}
