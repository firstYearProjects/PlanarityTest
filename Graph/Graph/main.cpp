#include "Graph.h"
#include"BrutePlanarityTest.h"
#include <iostream>
#include <string>
using namespace std;


void Test(const Graph& g, string name, bool expected)
{
	BrutePlanarityTest m(g);
	cout << name << '\n';
	bool res = m.checkPlanarity();
	cout << (res ? "planar : " : "not planar : ");
	cout << ((res == expected) ? "correct" : "wrong") << '\n';
}



int main()
{
	{
		// K5
		Graph g(5);
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
		
		Test(g, "K5", 0);
	}

	{
		// K33
		Graph r(6);
		r.addEdge(0, 3);
		r.addEdge(0, 4);
		r.addEdge(0, 5);

		r.addEdge(1, 3);
		r.addEdge(1, 4);
		r.addEdge(1, 5);

		r.addEdge(2, 3);
		r.addEdge(2, 4);
		r.addEdge(2, 5);

		Test(r, "K33", 0);
	}

	{
		// almost K33
		Graph r(6);
		r.addEdge(0, 3);
		//r.addEdge(0, 4);
		r.addEdge(0, 5);

		r.addEdge(1, 3);
		//r.addEdge(1, 4);
		r.addEdge(1, 5);

		r.addEdge(2, 3);
		r.addEdge(2, 4);
		r.addEdge(2, 5);

		Test(r, "almost K33", 1);
	}

	{
		// K5 with odd
		Graph g(8);
		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(0, 3);
		g.addEdge(0, 4);

		g.addEdge(1, 2);
		g.addEdge(1, 3);
		g.addEdge(1, 4);

		g.addEdge(2, 5);
		g.addEdge(5, 3);
		g.addEdge(2, 4);

		g.addEdge(3, 4);

		g.addEdge(5, 6);
		g.addEdge(6, 2);
		//g.addEdge(5, 7);
		//g.addEdge(6, 7);

		Test(g, "K5 with odd", 0);
	}


	system("pause");
	return 0;
}