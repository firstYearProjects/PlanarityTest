#include "Graph.h"
#include"BrutePlanarityTest.h"
//using namespace std;

int main()
{
	Graph g(10);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 0);
	g.addEdge(3, 1);
	g.addEdge(2, 0);

	BrutePlanarityTest m(g);
	m.printAllCycles();

	system("pause");
	return 0;
}