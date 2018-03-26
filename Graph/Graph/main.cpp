#include "Graph.h"

//using namespace std;

int main()
{
	Graph g(10);
	g.addEdge(1, 2);
	g.addEdge(2, 1);
	while (/*can find a cycle*/)
	{
		// find cycle lenght 6
		IsK33graph(/*cycle*/);
		// find cycle lenght 5
		IsK5graph(/*cycle*/);
	}
}