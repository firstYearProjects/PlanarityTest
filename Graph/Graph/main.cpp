#include "Graph.h"
#include"BrutePlanarityTest.h"
//using namespace std;

int main()
{
	// K5
	Graph g(6);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(0, 3);
	g.addEdge(0, 4);

	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);

	g.addEdge(2, 3);
	g.addEdge(2, 4);

	g.addEdge(3, 4);
	
	// odd with
	g.addEdge(0, 5);

	BrutePlanarityTest m(g);
	//m.printAllCycles();
	cout << "\n" << m.checkPlanarity() << " " << m.BruteCheck();

	system("pause");
	return 0;
}